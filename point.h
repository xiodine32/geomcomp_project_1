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
    enum INDEX {
        X, Y, Z
    };

    constexpr point(double x, double y, double z) noexcept : x_(x), y_(y), z_(z) { }

    constexpr point(double x, double y, POINT_TYPE type = POINT_TYPE::POLYGON) noexcept : x_(x), y_(y), z_(
            type == POINT_TYPE::POLYGON ? 0 : (type == POINT_TYPE::VIEWPOINT ? 1 :
                                               type == POINT_TYPE::TRIANGULATION ? 2 : 3)
    ) { }

    constexpr double operator[](int index) const noexcept {
        return index == 0 ? x_ : (index == 1 ? y_ : z_);
    }


    // default constructors
    constexpr point(const point &point) noexcept = default;

    constexpr point(point &&point) noexcept = default;

    // default operators
    point &operator=(const point &point) noexcept = default;

    point &operator=(point &&point) noexcept = default;


};


#endif //GEOMCOMP_POINT_H
