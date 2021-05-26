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
    void startEvents(Sint32 parameter, Uint32 delay = (33 / 10) * 10);
    void stopEvents();


private:
    static Uint32 TimerCallback(Uint32 interval, void *param);

    SDL_TimerID _timer_id;
    Sint32 _user_code;
    static Uint32 _interval;
};


#endif //LEMMINGS_TIMEREVENTSERVICE_H
