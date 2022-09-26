//
// Created by hawk on 16.05.21.
//
#include "LemmingsException.h"
#include "TimerEventService.h"
#include "UserEvent.h"

Uint32 TimerEventService::_interval = 0;



TimerEventService::TimerEventService(Uint32 delay) {
    if(delay <= 1 ) {
        delay = DELAY;
    }
    _timer_id = SDL_AddTimer(delay, TimerCallback, (void*) &delay);
    if(_timer_id == 0) {
        throw LemmingsException("Cannot start timer.");
    }
}

TimerEventService::~TimerEventService() {
    stopEvents();
}

SDL_TimerID TimerEventService::startEvents(Uint32 delay) {
    stopEvents();

    if(delay <= 1 ) {
        delay = DELAY;
    }
    _timer_id = SDL_AddTimer(delay, TimerCallback, (void*) &delay);
    return _timer_id;
}

bool TimerEventService::stopEvents() {

    if(_timer_id != 0) {
        SDL_bool result = SDL_RemoveTimer(_timer_id);
        if(result != SDL_TRUE) {
            return false;
        }
        _timer_id = 0;
    }
    return true;
}

/* with the same code as before: */
Uint32 TimerEventService::TimerCallback(Uint32 interval, void *param)
{
    TimerEventService::_interval = interval;
    if( !UserEvent<UPDATE_EVENT, Uint32> ::sendEvent(&_interval) ) {
        throw LemmingsException("Cannot start UPDATE_EVENT.");
    }
    return interval;
}

