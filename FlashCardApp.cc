#include "FlashCardApp.h"
#include "TempBackground.h"

FlashCardApp::FlashCardApp()
{
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

void FlashCardApp::addString(string s, unsigned char red, unsigned char green, unsigned char blue)
{
    strings.push_back(s);

    TextModel *textModel = new TextModel(s.c_str(), 30, red, green, blue);
    textModel->setPosition(0, 0);
    textModels.push_back(textModel);
}

void FlashCardApp::keyPressed()
{
    userQuit = true;
}

void FlashCardApp::run()
{
    string cardFile;
    cout << "file?\n";
    cin >> cardFile;

    windowManager->createWindow(screenWidth, screenHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);

    vector<float> values = frustum->getProjectionMatrix();

    init_background();

    addString("Hit <ENTER> to begin", 0, 0, 0);

    //ProjectManager projects;
    //projects.fetchProjects(this);

    float matrix[16];
    std::copy(values.begin(), values.end(), matrix);
    glMultMatrixf(matrix);

    long previousTickCount = 0;

    while (1) {
        long currentTickCount = SDL_GetTicks();
        long ticksSinceLastFrame = currentTickCount - previousTickCount;
        previousTickCount = currentTickCount;

        int framesPerSecons = 1000L / ticksSinceLastFrame;

        eventDispatcher->pollEvents();

        if (userQuit)
            break;

        clearScreen();

        draw_background();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float x = -.58;
        float y = .44;

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
