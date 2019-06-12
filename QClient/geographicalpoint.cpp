#include "geographicalpoint.h"

GeographicalPoint::GeographicalPoint(){}

GeographicalPoint::GeographicalPoint(const float& latitude, const float& longitude)
    : latitude_(latitude), longitude_(longitude)
{

}

GeographicalPoint::GeographicalPoint(const Coordinate& latitude, const Coordinate& longitude)
{
    latitude_ = latitude.getPoint();
    longitude_ = longitude.getPoint();
}

float GeographicalPoint::getLatitude() const
{
    return latitude_;
}

float GeographicalPoint::getLongitude() const
{
    return longitude_;
}

void GeographicalPoint::changeLatitude(const Coordinate &latitude)
{
    latitude_ = latitude.getPoint();
}

void GeographicalPoint::changeLongitude(const Coordinate &longitude)
{
    longitude_ = longitude.getPoint();
}
