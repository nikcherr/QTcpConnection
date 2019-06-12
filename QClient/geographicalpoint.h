#ifndef GEOGRAPHICALPOINT_H
#define GEOGRAPHICALPOINT_H

class Coordinate{
public:
    Coordinate(int degree, int minute, int second)
        : degree_(degree), minute_(minute), second_(second){}

    float getPoint() const {
        int sign = -1;
        degree_ < 0 ? degree_ *= -1 : sign = 1;
        return sign * ((float)degree_ + (float)minute_ / 60 + (float)second_ / 3600);
    }
private:
    mutable int degree_ = 0;
    int minute_ = 0;
    int second_ = 0;
};

class GeographicalPoint
{
public:
    GeographicalPoint();
    GeographicalPoint(const float& latitude, const float& longitude);
    GeographicalPoint(const Coordinate& latitude, const Coordinate& longitude);

    float getLatitude() const;
    float getLongitude() const;

    void changeLatitude(const Coordinate& latitude);
    void changeLongitude(const Coordinate& longitude);
private:
    float latitude_, longitude_;

};

#endif // GEOGRAPHICALPOINT_H
