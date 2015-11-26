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
    isInsideVal = 0;
    point punct(x, y, point::POINT_TYPE::VIEWPOINT);
    algqueue::singleton().push(action(action::ADD_POINT, punct));
    puncte.push_back(std::move(punct));
    isInsideCalc();
    algqueue::singleton().push(action(action::ADD_RESULT, point(isInsideVal, 0, 0)));
}

int actual_program::sign_det(point a, point b, point c) {
    double det = a[0] * b[1] - a[0] * c[1] - a[1] * b[0] + a[1] * c[0] + b[0] * c[1] - b[1] * c[0];

    if (det < 0)
        return -1;
    else if (det > 0)
        return 1;
    else
        return 0;
}

void actual_program::isInsideCalc() {
    int zeros = 0;
    int insides = 0;
    int outsides = 0;
    for (std::size_t i = 2; i < puncte.size() - 1; i++) {
        // avem 0 ca punct fix
        // avem i - 1, i ca latura mobila
        int status = sign_tri(puncte[0], puncte[i - 1], puncte[i], puncte[puncte.size() - 1]);
        if (status == 0)
            zeros++;
        else if (status > 0)
            insides++;
        else
            outsides++;
    }

    if (zeros != 0 && (insides == 0 || outsides == 0)) {
        isInsideVal = 0;
    }
    else if (zeros == 0 && (insides == 0 || outsides == 0)) {
        isInsideVal = -1;
    }
    else
        isInsideVal = 1;
}

int actual_program::sign_tri(point a, point b, point c, point m) {
    int zeros = 0, insides = 0, outsides = 0;
    int status = sign_det(a, b, m);
    if (status == 0)
        zeros++;
    else if (status > 0)
        insides++;
    else
        outsides++;

    status = sign_det(b, c, m);
    if (status == 0)
        zeros++;
    else if (status > 0)
        insides++;
    else
        outsides++;

    status = sign_det(c, a, m);
    if (status == 0)
        zeros++;
    else if (status > 0)
        insides++;
    else
        outsides++;

    if (zeros != 0 && (insides == 0 || outsides == 0)) {
        return 0;
    }
    else if (zeros == 0 && (insides == 0 || outsides == 0)) {
        return 1;
    }
    else
        return -1;
}
