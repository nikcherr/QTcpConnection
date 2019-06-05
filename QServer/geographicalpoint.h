#ifndef GEOGRAPHICALPOINT_H
#define GEOGRAPHICALPOINT_H
#include "math.h"

float const pi = 3.14;
int const R = 6371;

class Coordinate{
public:
    Coordinate(int degree, int minute, int second)
        : degree_(degree), minute_(minute), second_(second){}
    float getPoint() const {
        return (float)degree_ + (float)minute_ / 60 + (float)second_ / 3600;
    }
private:
    int degree_ = 0;
    int minute_ = 0;
    int second_ = 0;
};

class GeographicalPoint
{
public:
    GeographicalPoint(const float& latitude, const float& longitude);
    GeographicalPoint(const Coordinate& latitude, const Coordinate& longitude);

    float calculateAzimuth(const GeographicalPoint& otherPoint);
    float getRadLatitude() const;
    float getRadLongitude() const;
    float getLatitude() const;
    float getLongitude() const;

private:
    float latitude_, longitude_;

};

float Distance(const GeographicalPoint& rhs, const GeographicalPoint& lhs);
#endif // GEOGRAPHICALPOINT_H
