#include "FlashCardApp.h"
#include "TempBackground.h"
#include "CardReader.h"

#include <algorithm>
#include <math.h>
#include <time.h>

FlashCardApp::FlashCardApp()
{
    currentStringIndex = 0;
    windowManager = new GL_SDL_WindowManager();
    eventDispatcher = new SDLEventDispatcher();
    eventDispatcher->setEventHandler(this);
    screenWidth = 800;
    screenHeight = 600;
    frustum = new Frustum(screenWidth, screenHeight, .45, 1, 5000);
    userQuit = false;
}

void FlashCardApp::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FlashCardApp::addTextBox(string s, unsigned char red, unsigned char green, unsigned char blue)
{
    strings.push_back(s);

    TextModel *textModel = new TextModel(s.c_str(), 20, red, green, blue);
    textModel->setPosition(0, 0);
    textModels.push_back(textModel);
}

void FlashCardApp::keyPressed(SDLKey key)
{
    if (key == SDLK_ESCAPE)
        userQuit = true;
        
    if (key != SDLK_RIGHT)
        return;

    currentStringIndex++;
    strings.clear();
    textModels.clear();
    if (currentStringIndex < cardValues.size()) 
    {
        string s = cardValues[currentStringIndex];
        int currentPosition = 0;
        int totalLength = s.size();
        int maxLength = 60;

        while (totalLength - currentPosition > maxLength)
        {
            int subLength = maxLength;
            while (subLength > 0 && s[currentPosition + subLength] != ' ')
                subLength--;
            if (subLength == 0)
                subLength = maxLength;
            addTextBox(s.substr(currentPosition, subLength), 0, 0, 0);
            currentPosition += subLength;
        }
        while (s[currentPosition] == ' ' && currentPosition < totalLength)
            currentPosition++;
        addTextBox(s.substr(currentPosition, totalLength - currentPosition), 0, 0, 0);
    }
}

void FlashCardApp::run()
{
    srand(time(0));

    string cardFile;
    cout << "file?\n";
    cin >> cardFile;

    CardReader reader(cardFile);
    reader.getFileContents();
    reader.sendStringsToApp(this);

    vector<int> indices;
    while (indices.size() < cardValues.size())
    {
        int choice = rand() % cardValues.size();
        int randomIndex = 2 * (int)(choice / 2);
        if (find(indices.begin(), indices.end(), randomIndex) == indices.end())
        {
            indices.push_back(randomIndex);
            indices.push_back(randomIndex + 1);
        }
    }

    vector<string> randomValues;
    for (int i = 0; i < indices.size(); ++i)
       randomValues.push_back(cardValues[indices[i]]);

    cardValues.clear();
    for (int i = 0; i < randomValues.size(); ++i)
       cardValues.push_back(randomValues[i]);

    windowManager->createWindow(screenWidth, screenHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);

    vector<float> values = frustum->getProjectionMatrix();

    init_background();

    addTextBox(cardValues[currentStringIndex], 0, 0, 0);

    //ProjectManager projects;
    //projects.fetchProjects(this);

    float matrix[16];
    std::copy(values.begin(), values.end(), matrix);
    glMultMatrixf(matrix);

    long previousTickCount = 0;

    while (1) {
        if (userQuit)
            break;

        long currentTickCount = SDL_GetTicks();
        long ticksSinceLastFrame = currentTickCount - previousTickCount;
        previousTickCount = currentTickCount;

        int framesPerSecons = 1000L / ticksSinceLastFrame;

        eventDispatcher->pollEvents();

        if (currentStringIndex >= cardValues.size())
            break;

        clearScreen();

        draw_background();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float x = -.50;
        float y = .30;

        for (int i = 0; i < strings.size(); ++i)
        {
            TextModel *textModel = textModels[i];
            textModel->setPosition(x, y);
            y -= .04;
            textModel->draw();
        }

        windowManager->swapBuffers();
    }

    SDL_Quit();
}

// END OF FILE
