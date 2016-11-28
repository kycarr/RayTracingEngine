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

Plane::Plane(const GzVector3 &n, float dToOrigin,
        const GzVector3 &u_axe, const GzMaterial &a_mat) :
        GzGeometry(a_mat), base(n.normalize() * dToOrigin), 
        bX(u_axe.normalize() + base),
        bY(n.normalize().crossMultiply(u_axe.normalize()) + base)
{
}

Plane::Plane() : Plane(GzVector3(0.0f, 1.0f, 0.0f), 0.0f, GzVector3(0.0f, 0.0f, 1.0f))
{
}

float Plane:: getIntersectDistance(const GzRay &ray) const
{
	GzVector3 xUnit(this->bX - this->base);
	GzVector3 yUnit(this->bY - this->base);
	GzVector3 normal(xUnit.crossMultiply(yUnit).normalize());
	float dToO(this->base.dotMultiply(normal));
	float dDotN(ray.direction.dotMultiply(normal));
	if (dDotN == 0.0f)
	{
		return std::numeric_limits<float>::infinity();
	}
	float distance((dToO - ray.origin.dotMultiply(normal)) / dDotN);
	if (distance <= EPSILON0)
	{
		return std::numeric_limits<float>::infinity();
	}
	return distance;
}


IntersectResult Plane::intersect(const GzRay &ray) const
{
    float distance(getIntersectDistance(ray));
    if (distance >= std::numeric_limits<float>::infinity())
    {
        return IntersectResult::NOHIT;
    }
    GzVector3 interPos(ray.getPoint(distance));
    // For immediate result, I don't consider general case. Just assume xUnit and yUnit are orthogonal.
    GzVector3 xUnit(this->bX - this->base);
    GzVector3 yUnit(this->bY - this->base);
    GzVector3 normal(xUnit.crossMultiply(yUnit).normalize());
    float u((interPos - this->base).dotMultiply(xUnit));
    float v((interPos - this->base).dotMultiply(yUnit));
    return IntersectResult(this, distance, interPos, normal, u, v);
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
    float distance(Sphere::getIntersectDistance(ray));
    if (distance > 0.0f)
    {
        GzVector3 interPos(ray.getPoint(distance));
        GzVector3 normal = (interPos - this->center).normalize();
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

        return IntersectResult(this, distance, interPos, normal, u, v);
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
        return IntersectResult::NOHIT;
    }
}

float Sphere::getIntersectDistance(const GzRay &ray) const
{
    GzVector3 v(this->center - ray.origin);
    float r((this->arctic - this->center).length());
    float dDotV = ray.direction.dotMultiply(v);
    float delta = dDotV * dDotV - v.lengthSqr() + r * r;
    // If no hit, return inf. Tangent line? Need to check more
    if (delta >= 0.0f)
    {
        float deltaSqrt = std::sqrt(delta);
        if (dDotV <= 0.0f)
        {
            if (dDotV + deltaSqrt > EPSILON0)
            {
                return dDotV + deltaSqrt;
            }
            else
            {
                return std::numeric_limits<float>::infinity(); // no hit
            }
        }
        else
        {
            if (dDotV - deltaSqrt > EPSILON0)
            {
                return dDotV - deltaSqrt;
            }
            else
            {
                return dDotV + deltaSqrt;
            }
        }
        // The two roots are dDotV +- deltaSqrt
        // For deltaSqrt == 0, tangent line case, only need to return when distance > 0.
        // For two separate roots, if one + and one -, return positive one;
        // if two +, return smaller one; if two -, return -1;
        // if there are 0 in the two roots, only return the greater one if it is +. This also covers two 0 case.
        //if ((deltaSqrt - std::abs(dDotV) > 0.005f) || (std::abs(dDotV) == deltaSqrt && dDotV + deltaSqrt > 0.005f))
        // std::abs(dDotV) < deltaSqrt covers one + and one -
        // std::abs(dDotV) == deltaSqrt covers one 0 / two 0
        //{
            //return dDotV + deltaSqrt;
        //}
        //else if (std::abs(dDotV) - deltaSqrt > 0.005f && dDotV > 0.0f)
        //{
            //return dDotV - deltaSqrt;
        //}
    }
    return std::numeric_limits<float>::infinity(); // Indicates no hit
}

Union::Union(int g_num, GzGeometry ** g_p_arr) :
    num(g_num), gArray(g_p_arr)
{
}

Union::Union() : Union(0, nullptr)
{
}

Union::~Union()
{
    for (int i = 0; i < this->num; ++i)
    {
        delete this->gArray[i];
    }
    delete[] this->gArray;
}

float Union::getIntersectDistance(const GzRay &ray) const
{
    if (this->num < 1)
    {
        return std::numeric_limits<float>::infinity();
    }
	float nearestDistance = std::numeric_limits<float>::infinity();
    int nearestIndex = -1;
    for (int i = 0; i < this->num; ++i)
    {
       float tempResult(this->gArray[i]->getIntersectDistance(ray));
        if (tempResult < nearestDistance)
        {
            nearestIndex = i;
            nearestDistance = tempResult;
        }
    }
    return nearestDistance;
}

IntersectResult Union::intersect(const GzRay &ray) const
{
    if (this->num < 1)
    {
        return IntersectResult::NOHIT;
    }
	float nearestDistance = std::numeric_limits<float>::infinity();
    int nearestIndex = -1;
    for (int i = 0; i < this->num; ++i)
    {
       float tempResult(this->gArray[i]->getIntersectDistance(ray));
        if (tempResult < nearestDistance)
        {
            nearestIndex = i;
            nearestDistance = tempResult;
        }
    }
    if (nearestIndex >= 0)
    {
        return this->gArray[nearestIndex]->intersect(ray);
    }
    return IntersectResult::NOHIT;
}

