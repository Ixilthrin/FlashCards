#ifndef __i_event_handler
#define __i_event_handler

#include "SDL_types.h"
#include "SDL.h"

class IEventHandler {
public:
    virtual void keyPressed(SDLKey key) = 0;
};

#endif
