#ifndef __sdl_event_dispatcher__
#define __sdl_event_dispatcher__

#include "SDL_types.h"
#include "SDL.h"

#include "IEventHandler.h"

class SDLEventDispatcher {
public:
    SDLEventDispatcher();
    void pollEvents();
    void setEventHandler(IEventHandler *handler) {
        eventHandler = handler;
    }
private:
    IEventHandler *eventHandler;
    void keyDownEvent(SDLKey key);
};

#endif

