//
// Created by xiodine on 11/24/15.
//

#include <SDL2/SDL_opengl.h>
#include "camera.h"

camera::camera(double x, double y, double z, double pitch, double yaw) : x_(x), y_(y), z_(z), pitch_(pitch), yaw_(yaw) {

}

void camera::push() {
    glPushMatrix();
    glRotated(yaw_, 1, 0, 0);
    glRotated(pitch_, 0, 1, 0);
    glTranslated(-x_, -y_, -z_);
}

void camera::pop() {
    glPopMatrix();
}

void camera::deltaPosition(double x, double y, double z) {
    x_ += x;
    y_ += y;
    z_ += z;
}

void camera::deltaView(double pitch, double yaw) {
    pitch_ += pitch;
    yaw_ += yaw;

    if (pitch_ < 0)
        pitch_ += 360.0;
    if (pitch_ > 360.0)
        pitch_ -= 360.0;

    if (yaw_ < -90)
        yaw_ = -90;
    if (yaw_ > 90)
        yaw_ = 90;

}

double camera::getPitch() const {
    return pitch_;
}

