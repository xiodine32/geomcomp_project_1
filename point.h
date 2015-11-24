//
// Created by xiodine on 11/24/15.
//

#ifndef GEOMCOMP_POINT_H
#define GEOMCOMP_POINT_H


class point {
private:
    double x_;
    double y_;
    double z_;
public:
    enum class POINT_TYPE {
        POLYGON,
        VIEWPOINT,
        TRIANGULATION
    };

    constexpr point(double x, double y, double z) noexcept;
    constexpr point(double x, double y, POINT_TYPE type = POINT_TYPE::POLYGON) noexcept;

    constexpr double getX() const noexcept;
    constexpr double getY() const noexcept;
    constexpr double getZ() const noexcept;
};


#endif //GEOMCOMP_POINT_H
