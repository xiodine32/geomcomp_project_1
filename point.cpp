//
// Created by xiodine on 11/25/15.
//

#include "point.h"


double &point::operator[](int index) noexcept {
    return index == 0 ? x_ : (index == 1 ? y_ : z_);
}
