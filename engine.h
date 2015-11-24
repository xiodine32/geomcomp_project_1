//
// Created by xiodine on 11/23/15.
//

#ifndef GEOMCOMP_ENGINE_H
#define GEOMCOMP_ENGINE_H

#include <SDL2/SDL.h>
#include "camera.h"
#include <memory>
#include <unordered_map>


class engine {


    void initOpenGL();

    void initScreen();

    static bool singleInstance;
    SDL_Window *window;

    std::unique_ptr<camera> camera_;

    std::unordered_map<int, bool> keystate_;

public:


    engine();

    ~engine();

    void run();

    static bool running;

    void events();

    void draw();

    void tick();

    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    static const int FPS = 1000 / 60;
    static constexpr double MOUSE_SMOOTHING = 100.0;
    static constexpr double KEY_SMOOTHING = 100.0;
};


#endif //GEOMCOMP_ENGINE_H
