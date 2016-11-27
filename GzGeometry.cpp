#include "stdafx.h"
#include "GzGeometry.h"
#include <limits>
#include <cmath>

// Encapsulate u and v?
IntersectResult::IntersectResult(const GzGeometry *p_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor, float a_u, float a_v) :
    p_geometry(p_geo), distance(a_dis), position(a_pos), normal(a_nor), u(a_u), v(a_v)
{
}

IntersectResult::IntersectResult(const GzGeometry *p_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor) :
    p_geometry(p_geo), distance(a_dis), position(a_pos), normal(a_nor), u(-1), v(-1)
{
}

//IntersectResult::IntersectResult() : IntersectResult(nullptr, std::numeric_limits<float>::infinity(), GzVector3(0.0f, 0.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f)
IntersectResult::IntersectResult() : IntersectResult(nullptr, std::numeric_limits<float>::infinity(), GzVector3(0.0f, 0.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f))
{
}

//const IntersectResult IntersectResult::NOHIT(nullptr, std::numeric_limits<float>::infinity(), GzVector3(0.0f, 0.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
const IntersectResult IntersectResult::NOHIT(nullptr, std::numeric_limits<float>::infinity(), GzVector3(0.0f, 0.0f, 0.0f), GzVector3(0.0f, 1.0f, 0.0f));

GzGeometry::GzGeometry(const GzMaterial &a_mater) : material(a_mater)
{
}

GzGeometry::GzGeometry() : material(GzMaterial::DEFAULT)
{
}

Sphere::Sphere(const GzVector3 &c, float radius, const GzMaterial &a_mat,
    const GzVector3 &x_axe, const GzVector3 &y_axe, const GzVector3 &z_axe) : GzGeometry(a_mat),
    center(c), arctic(c + radius * z_axe.normalize()), 
    long_x(c + radius * x_axe.normalize()),
    long_y(c + radius * y_axe.normalize())
{
}

Sphere::Sphere() : Sphere(GzVector3(0.0f, 0.0f, 0.0f), 1.0f)
{
}

IntersectResult Sphere::intersect(const GzRay &ray) const
{
    float radius((this->arctic - this->center).length());
    float distance(Sphere::getRayDistance(this->center, radius, ray));
    if (distance > 0.0f)
    {
        GzVector3 interPos(ray.getPoint(distance));
        GzVector3 relative(interPos - center);
        GzVector3 n(relative.normalize());
        float theta = std::acos(n.dotMultiply((this->arctic - this->center).normalize()));
        float v = static_cast<float>(theta / PI);
        float u = 0.0f;
        if (v != 0.0f && v != 1.0f)
        {
            float cosPhiL = n.dotMultiply(this->long_x - this->center);
            float sinPhiL = n.dotMultiply(this->long_y - this->center);
            float phi = std::atan2(sinPhiL, cosPhiL);
            u = static_cast<float>(phi / (2*PI) + 0.5);
        }
        return IntersectResult(this, distance, interPos, (interPos - this->center).normalize(), u, v);
        //float o2c((this->center - ray.origin).length());
        //if (o2c < radius)
        //{
            // origin of ray inside the sphere. Normal points towards the center
            //return IntersectResult(this, distance, interPos, (interPos - this->center).normalize());
        //}
        //else
        //{
            // origin of ray outside. Most common case.
            //return IntersectResult(this, distance, interPos, (this->center - interPos).normalize());
        //}
    }
    else
    {
        // getRayDistance returns -1, which indicates no hit. If hit, getRayDistance always returns a positive number.
        return IntersectResult::NOHIT;
    }
}

float Sphere::getRayDistance(const GzVector3 &c, float r, const GzRay &ray)
{
    GzVector3 v(c - ray.origin);
    float dDotV = ray.direction.dotMultiply(v);
    float delta = dDotV * dDotV - v.lengthSqr() + r * r;
    // If no hit, return -1. Tangent line? Need to check more
    if (delta >= 0) {
        float deltaSqrt = std::sqrt(delta);
        // The two roots are dDotV +- deltaSqrt
        // For deltaSqrt == 0, tangent line case, only need to return when distance > 0.
        // For two separate roots, if one + and one -, return positive one;
        // if two +, return smaller one; if two -, return -1;
        // if there are 0 in the two roots, only return the greater one if it is +. This also covers two 0 case.
        if ((std::abs(dDotV) < deltaSqrt) || (std::abs(dDotV) == deltaSqrt && dDotV + deltaSqrt > 0.0f))
        // std::abs(dDotV) < deltaSqrt covers one + and one -
        // std::abs(dDotV) == deltaSqrt covers one 0 / two 0
        {
            return dDotV + deltaSqrt;
        }
        else if (std::abs(dDotV) > deltaSqrt && dDotV > 0.0f)
        {
            return dDotV - deltaSqrt;
        }
    }
    return -1.0f; // Indicates no hit
}
