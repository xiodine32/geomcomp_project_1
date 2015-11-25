//
// Created by xiodine on 11/24/15.
//

#include <fstream>
#include "actual_program.h"
#include "algqueue.h"

using namespace std;

actual_program::actual_program() {

    ifstream input("input.txt");

    int n;
    input >> n;

    for (int i = 0; i < n; i++) {
        double x, y;
        input >> x >> y;
        point punct(x, y, point::POINT_TYPE::POLYGON);
        algqueue::singleton().push(action(action::ADD_POINT, punct));
        puncte.push_back(std::move(punct));
    }
    double x, y;
    input >> x >> y;
    isInsideVal=0;
    point punct(x, y, point::POINT_TYPE::VIEWPOINT);
    algqueue::singleton().push(action(action::ADD_POINT, punct));\
    puncte.push_back(std::move(punct));
    isInsideCalc();
    return;
}

