//
// Created by xiodine on 11/24/15.
//

#include <utility>
#include "algqueue.h"

constexpr action::action(action::TYPE type, point point) noexcept : type_(type), point_(std::move(point)) {

}

constexpr action::TYPE action::getType() const noexcept {
    return type_;
}

constexpr const point &action::getPoint() const noexcept {
    return point_;
}
