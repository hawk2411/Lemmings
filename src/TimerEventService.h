//
// Created by hawk on 16.05.21.
//

#ifndef LEMMINGS_TIMEREVENTSERVICE_H
#define LEMMINGS_TIMEREVENTSERVICE_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

class TimerEventService {
public:
    explicit TimerEventService();
    void startEvents(Uint32 parameter, Uint32 delay = (33 / 10) * 10);
    void stopEvents();
private:
    SDL_TimerID _timer_id;

    static Uint32 TimerCallback(Uint32 interval, void *param);
    static const Sint32 EVENT_CODE = 1;
};


#endif //LEMMINGS_TIMEREVENTSERVICE_H
