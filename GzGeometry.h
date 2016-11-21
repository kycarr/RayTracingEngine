#ifndef GZGEOMETRY_H
#define GZGEOMETRY_H

#include "GzVector3.h"
#include "GzRay.h"
#include <limits>
#include <cmath>

class GzGeometry;

class IntersectResult
{
public:
    const GzGeometry *const p_geometry;
    const float distance;
    const GzVector3 position;
    const GzVector3 normal;
    const float u, v;

    // Pre: a_nor is a normalized vector. No checking inside.
    IntersectResult(const GzGeometry &a_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor, float a_u, float a_v);
    IntersectResult();

    const static IntersectResult NOHIT;
};

IntersectResult::IntersectResult(const GzGeometry &a_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor, float a_u, float a_v) :
    p_geometry(&a_geo), distance(a_dis), position(a_pos), normal(a_nor), u(a_v), v(a_v)
{
}

IntersectResult::IntersectResult() : p_geometry(nullptr), distance(std::numeric_limits<float>::infinity()), position(GzVector3(0.0f, 0.0f, 0.0f)), normal(GzVector3(0.0f, 1.0f, 0.0f), u(0.0f), v(0.0f))
{
}

const IntersectResult IntersectResult::NOHIT(nullptr, std::numeric_limits<float>::infinity(), GzVector3(0.0f, 0.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);

class GzGeometry // Base class
{
public:
    GzMaterial material;
    GzGeometry(const GzMaterial &a_mater);
    GzGeometry();
    virtual IntersectResult intersect(const GzRay &ray) const = 0;
};

GzGeometry::GzGeometry(const GzMaterial &a_mater) : material(a_mater)
{
}

GzGeometry::GzGeometry() : material(GzMaterial::DEFAULT)
{
}

class Sphere: public GzGeometry
{
public:
    GzVector3 center;
    GzVector3 arctic; // Arctic point, theta = 0, phi = any
    GzVector3 long_x; // Point for longitute calculation, theta = 90, phi = 0
    GzVector3 long_y; // Point for longitute calculation, theta = 90, phi = 90

    Sphere();
    Sphere(const GzVector3 &c, float radius,
            const GzVector3 &x_axe = GzVector3(1.0f, 0.0f, 0.0f),
            const GzVector3 &y_axe = GzVector3(0.0f, 1.0f, 0.0f),
            const GzVector3 &z_axe = GzVector3(0.0f, 0.0f, 1.0f));
protected:
    static float getDistance(const GzVector3 &c, float r, const GzRay &r);
};

Sphere::Sphere(const GzVector3 &c, float radius,
    const GzVector3 &x_axe = GzVector3(1.0f, 0.0f, 0.0f),
    const GzVector3 &y_axe = GzVector3(0.0f, 1.0f, 0.0f),
    const GzVector3 &z_axe = GzVector3(0.0f, 0.0f, 1.0f)) :
    center(c), arctic(c + radius * z_axe.normalize()),
    long_x(c + radius * x_axe.normalize()),
    long_y(c + radius * y_axe.normalize())
{
}

float Sphere::getDistance(const GzVector3 &c, float r, const GzRay &r)
{
    GzVector3 v(r.origin - c);
    float dDotV = r.direction.dotMultiply(v);
    if (dDotV <= 0) {
        float delta = dDotV * dDotV - v.lengthSqr() + r * r;
        if (delta >= 0) {
            return -dDotV - std::sqrt(delta);
            //position = r.getPoint(-dDotV - std::sqrt(delta));
            //GzVector normal = position.subtract(this->center).normalize();
            //return new IntersectResult((GzObject *)this, distance, position, normal);
        }
    }
    return -1.0f;
}

class Ellipsoid: public Sphere
{
};
#endif

