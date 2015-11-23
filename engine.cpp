//
// Created by xiodine on 11/23/15.
//

#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include "engine.h"


void engine::run() {

    initScreen();
    initOpenGL();

    running = true;
    long lTick = SDL_GetTicks();
    while (running) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        events();

        while (SDL_GetTicks() - lTick > FPS) {
            lTick += FPS;
            tick();
        }

        camera_->push();

        draw();

        camera_->pop();

        SDL_GL_SwapWindow(window);


    }
}

engine::~engine() {
    singleInstance = false;
    SDL_Quit();
}

void engine::initOpenGL() {

    glClearDepth(1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    // depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluPerspective(45.0, (double) WIDTH / HEIGHT, 0.1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void engine::initScreen() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer *displayRenderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &displayRenderer);
    SDL_SetWindowTitle(window, "Neagu Rares, Bucur Radu, Vlad Bulete - Proiect 9");

    SDL_SetRelativeMouseMode(SDL_TRUE);
}

engine::engine() : camera_(new camera(0, 0, 0)), keystate_{0} {
    if (singleInstance)
        throw "cannot run multiple instances";
    singleInstance = true;
}

bool engine::singleInstance = false;
bool engine::running = false;

void engine::events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            running = false;

        if (event.type == SDL_MOUSEMOTION)
            camera_->deltaView(event.motion.xrel / MOUSE_SMOOTHING, event.motion.yrel / MOUSE_SMOOTHING);

        if (event.type == SDL_KEYDOWN)
            keystate_[event.key.keysym.sym] = true;
        if (event.type == SDL_KEYUP)
            keystate_[event.key.keysym.sym] = false;
    }
}

void engine::draw() {
    glBegin(GL_QUADS);
    glColor3d(1, 0, 0);

    glVertex3d(-0.25, -0.25, -1);
    glVertex3d(-0.25, 0.25, -1);
    glVertex3d(0.25, 0.25, -1);
    glVertex3d(0.25, -0.25, -1);

    glEnd();
}

void engine::tick() {
    static double PI = 3.14159265;
    static double DEG2RAD = PI / 180.0;
    double xDelta = 0, yDelta = 0, zDelta = 0;
    if (keystate_[SDLK_w]) {
        xDelta += sin(camera_->getPitch() * DEG2RAD);
        zDelta -= cos(camera_->getPitch() * DEG2RAD);
    }

    if (keystate_[SDLK_s]) {
        xDelta -= sin(camera_->getPitch() * DEG2RAD);
        zDelta += cos(camera_->getPitch() * DEG2RAD);

    }
    if (keystate_[SDLK_a]) {
        xDelta += sin(camera_->getPitch() * DEG2RAD - PI / 2.0);
        zDelta -= cos(camera_->getPitch() * DEG2RAD - PI / 2.0);
    }
    if (keystate_[SDLK_d]) {
        xDelta -= sin(camera_->getPitch() * DEG2RAD - PI / 2.0);
        zDelta += cos(camera_->getPitch() * DEG2RAD - PI / 2.0);
    }
    if (keystate_[SDLK_q])
        yDelta++;
    if (keystate_[SDLK_e])
        yDelta--;

    camera_->deltaPosition(xDelta / KEY_SMOOTHING, yDelta / KEY_SMOOTHING, zDelta / KEY_SMOOTHING);

}
