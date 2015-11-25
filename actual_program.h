//
// Created by xiodine on 11/24/15.
//

#ifndef GEOMCOMP_ACTUAL_PROGRAM_H
#define GEOMCOMP_ACTUAL_PROGRAM_H

#include <vector>
#include "point.h"

class actual_program {

    std::vector<point> puncte;

    int isInsideVal;

    int sign_det(point a, point b, point c);

    void isInsideCalc();

public:
    actual_program();

    int isInside();

};


#endif //GEOMCOMP_ACTUAL_PROGRAM_H
