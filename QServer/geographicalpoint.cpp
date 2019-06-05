#include "geographicalpoint.h"

GeographicalPoint::GeographicalPoint(const float& latitude, const float& longitude)
    : latitude_(latitude), longitude_(longitude)
{

}

GeographicalPoint::GeographicalPoint(const Coordinate& latitude, const Coordinate& longitude)
{
    latitude_ = latitude.getPoint();
    longitude_ = longitude.getPoint();
}

float GeographicalPoint::calculateAzimuth(const GeographicalPoint& otherPoint)
{
    float lat_rhs = otherPoint.getRadLatitude();
    float long_rhs = otherPoint.getRadLongitude();
    float lat_lhs = this->getRadLatitude();
    float long_lhs = this->getRadLongitude();
    float q = atan2(cosf(lat_lhs) * sinf(lat_rhs) - sinf(lat_lhs) * cosf(lat_rhs) * cosf(long_rhs - long_lhs), sin(long_rhs - long_lhs) * cos(lat_rhs));
    q = q * 180 / 3.14;
    q += 360;
    int mod = q / 360;
    return q - 360 * mod;
}

float GeographicalPoint::getRadLatitude() const
{
    return latitude_ * pi / 180;
}

float GeographicalPoint::getRadLongitude() const
{
    return longitude_ * pi / 180;
}

float GeographicalPoint::getLongitude() const
{
    return longitude_;
}

float GeographicalPoint::getLatitude() const
{
    return latitude_;
}

float Distance(const GeographicalPoint& rhs, const GeographicalPoint& lhs)
{
    float lat_rhs = rhs.getRadLatitude();
    float long_rhs = rhs.getRadLongitude();
    float lat_lhs = lhs.getRadLatitude();
    float long_lhs = lhs.getRadLongitude();
    float delta = long_rhs - long_lhs;
    return R * (acosf(sinf(lat_rhs) * sinf(lat_lhs) + cosf(lat_rhs) * cosf(lat_lhs) * cosf(delta)));

}
