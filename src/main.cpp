#define GLEW_STATIC

#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>
#include <cstdint>
#include <ctime>
#include <random>

#include "TimerEventService.h"
#include "Game.h"


//Remove console (only works in Visual Studio)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char **argv) {
    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Uint32 flag = SDL_WINDOW_OPENGL;

    SDL_Window *window = SDL_CreateWindow("", 100, 100, 800, 600, flag);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        std::cin.get();
        return -1;
    }

    bool close = false;
    //StopWatch stopWatch;

    Game game;
    game.init();
    //SDL_SetWindowGrab(window, SDL_TRUE);
    TimerEventService timerService;
    int event_type = UPDATE_EVENT;
    timerService.startEvents(event_type);

    SDL_Event event;
    while (!close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    game.changeBplay();
                    close = true;
                    break;
                case SDL_KEYDOWN:
                //case SDL_KEYUP:
                    game.onKeyPressed(event.key);
                    break;
                case SDL_MOUSEMOTION:
                    game.onMousMove(event.motion);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    game.onMouseButtonDown(event.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    game.onMouseButtonUp(event.button);
                    break;
                case SDL_USEREVENT:
                    game.onUserEvent(event.user);
                    break;
            }

        }
        game.render();
        SDL_GL_SwapWindow(window);

    }

    return 0;
}



