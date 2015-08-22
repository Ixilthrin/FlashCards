#ifndef __flashcardapp_h__
#define __flashcardapp_h__

#include "IProgram.h"
#include "IEventHandler.h"

#include "GL_SDL_WindowManager.h"
#include "SDLEventDispatcher.h"
#include "SDLTextSurface.h"
#include "TextureUtil.h"
#include "TextModel.h"
#include "frustum.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class FlashCardApp : public IProgram, public IEventHandler
{
public:
    FlashCardApp();
    virtual void run();
    void clearScreen();
    void addTextBox(string s, unsigned char red, unsigned char green, unsigned char blue);
    virtual void keyPressed();
    void addCardValue(string s) { cardValues.push_back(s); }
private:
    GL_SDL_WindowManager *windowManager;
    SDLEventDispatcher *eventDispatcher;
    Frustum *frustum;
    float screenWidth;
    float screenHeight;
    vector<string> strings;
    vector<TextModel *> textModels;
    string uname;
    string pword;
    bool userQuit;
    vector<string> cardValues;
    int currentStringIndex;
};


#endif
