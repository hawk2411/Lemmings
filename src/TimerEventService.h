//
// Created by hawk on 16.05.21.
//

#ifndef LEMMINGS_TIMEREVENTSERVICE_H
#define LEMMINGS_TIMEREVENTSERVICE_H

#include <SDL2/SDL.h>

class TimerEventService {
public:
    explicit TimerEventService(Uint32 delay);
    ~TimerEventService();
    SDL_TimerID startEvents(Uint32 delay);
    bool stopEvents();

    constexpr static Uint32 DELAY = 30;

private:
    static Uint32 TimerCallback(Uint32 interval, void *param);

    SDL_TimerID _timer_id;
    static Uint32 _interval;
};


#endif //LEMMINGS_TIMEREVENTSERVICE_H
