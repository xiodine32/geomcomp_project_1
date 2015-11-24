//
// Created by xiodine on 11/24/15.
//

#include "point.h"

constexpr double point::getX() const noexcept {
    return x_;
}

constexpr double point::getY() const noexcept {
    return y_;
}

constexpr double point::getZ() const noexcept {
    return z_;
}

constexpr point::point(double x, double y, double z) noexcept : x_(x), y_(y), z_(z) { }

constexpr point::point(double x, double y, point::POINT_TYPE type) noexcept : x_(x), y_(y), z_(
        type == POINT_TYPE::POLYGON ? 0 : (type == POINT_TYPE::VIEWPOINT ? 1 :
                                           type == POINT_TYPE::TRIANGULATION ? 2 : 3)
) { }