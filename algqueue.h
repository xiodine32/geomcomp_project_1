//
// Created by xiodine on 11/24/15.
//

#ifndef GEOMCOMP_ALGQUEUE_H
#define GEOMCOMP_ALGQUEUE_H

#include "point.h"
#include <queue>

class action {
    enum TYPE {
        ADD_POINT
    };

    TYPE type_;
    point point_;
public:
    constexpr action(TYPE type, point point) noexcept;

    constexpr TYPE getType() const noexcept;

    constexpr const point &getPoint() const noexcept;

    // default constructors
    constexpr action(const action &action) noexcept = default;

    constexpr action(action &&action) noexcept = default;

    // default operators
    action &operator=(const action &action) noexcept = default;

    action &operator=(action &&action) noexcept = default;

};

class algqueue {

};


#endif //GEOMCOMP_ALGQUEUE_H
