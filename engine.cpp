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

        SDL_Delay(FPS / 2);
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
    gluPerspective(45.0, (double) WIDTH / HEIGHT, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(3);
}

void engine::initScreen() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Rect r;
    if (!SDL_GetDisplayBounds(0, &r)) {
        WIDTH = r.w;
        HEIGHT = r.h;
    }

    window = SDL_CreateWindow("Neagu Rares, Bucur Radu, Vlad Bulete - Proiect 4",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    SDL_GL_CreateContext(window);

    SDL_SetRelativeMouseMode(SDL_TRUE);
}

engine::engine() : camera_(new camera(0, 0, 10)), keystate_() {
    if (singleInstance)
        throw "cannot run multiple instances";
    singleInstance = true;
}

bool engine::singleInstance = false;
bool engine::running = false;
int engine::WIDTH = 800;
int engine::HEIGHT = 600;

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
    static GLuint displayList = 0;
    if (displayList == 0) {
        displayList = glGenLists(1);
        glNewList(displayList, GL_COMPILE);
        glBegin(GL_QUADS);
        int index = 0;
        for (double i = -50; i < 50; i += 0.5) {
            index = (index + 1) % 2;
            for (double j = -50; j < 50; j += 0.5) {
                index = (index + 1) % 2;
                glColor3d(index, 0, index);
                glVertex3d(i + -0.25, j - 0.25, -10);
                glVertex3d(i + -0.25, j + 0.25, -10);
                glVertex3d(i + 0.25, j + 0.25, -10);
                glVertex3d(i + 0.25, j - 0.25, -10);
            }
        }
        glEnd();
        glEndList();
    }
    glCallList(displayList);

    glColor3d(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    static double colors[2][3] = {
            {0.8, 0.3, 0.3},
            {0.6, 0.7, 0.6},
    };
    int index = 0;
    for (const auto &elem : actions) {
        if (elem.getType() != action::ADD_POINT)
            continue;
        const auto &point = elem.getPoint();
        index = (index + 1) % 2;
        glColor3d(colors[index][0],
                  colors[index][1],
                  colors[index][2]);
        glVertex3d(point[point::X] + 0 * requestRandom(),
                   point[point::Y] + 0 * requestRandom(),
                   point[point::Z] + 0 * requestRandom());
    }
    glEnd();
}

void engine::tick() {
    camera_->tick(keystate_);
    engineTicks_++;
    if (engineTicks_ >= ENGINE_TICKS_ADD) {
        engineTicks_ = 0;
        tickAdd();
    }
}

void engine::tickAdd() {
    if (algqueue::singleton().empty())
        return;
    actions.push_back(algqueue::singleton().front());
    algqueue::singleton().pop();
}

double engine::requestRandom() {
    return (rand() / (double) RAND_MAX - 0.5) / 50.0;
}

