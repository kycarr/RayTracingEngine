#ifndef GZGEOMETRY_H
#define GZGEOMETRY_H

#include "GzConstants.h"
#include "GzVector3.h"
#include "GzRay.h"
#include "GzMaterial.h"

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
    IntersectResult(const GzGeometry *a_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor, float a_u, float a_v);
    IntersectResult(const GzGeometry *a_geo, float a_dis, const GzVector3 &a_pos, const GzVector3 &a_nor);
    IntersectResult(); // Default constructor. Build a NOHIT object.

    const static IntersectResult NOHIT;
};

class GzGeometry // Base class
{
public:
    GzMaterial material;
    GzGeometry(const GzMaterial &a_mater);
    GzGeometry(); // Default constructor. Builds with default material.
    virtual IntersectResult intersect(const GzRay &ray) const = 0;
    virtual float getIntersectDistance(const GzRay &ray) const = 0;
	//virtual float getIntersectDistance(const GzRay &ray) const = 0;
    //virtual void transform(const GzMatrix &mat) = 0; // This method modifies the geometry according to a general transformation matrix.
};

class Plane: public GzGeometry
{
public:
// attributes
    GzVector3 base;
    GzVector3 bX;
    GzVector3 bY;
// constructors
    Plane(const GzVector3 &n, float dToOrigin,
            const GzVector3 &u_axe,
            const GzMaterial &a_mat = GzMaterial::DEFAULT);
    Plane(); // Default constructor. Build a plane at (0,0,0) normal as (0, 1, 0).
// methods
    virtual IntersectResult intersect(const GzRay &ray) const;
	virtual float getIntersectDistance(const GzRay &ray) const;
};




class Sphere: public GzGeometry
{
public:
// attributes
    GzVector3 center;
    GzVector3 arctic; // Arctic point, theta = 0, phi = any
    GzVector3 long_x; // Point for longitute calculation, theta = 90, phi = 0
    GzVector3 long_y; // Point for longitute calculation, theta = 90, phi = 90
// constructors
    Sphere(const GzVector3 &c, float radius,
            const GzMaterial &a_mat = GzMaterial::DEFAULT,
            const GzVector3 &x_axe = GzVector3(0.0f, 0.0f, 1.0f),
            const GzVector3 &y_axe = GzVector3(1.0f, 0.0f, 0.0f),
            const GzVector3 &z_axe = GzVector3(0.0f, 1.0f, 0.0f));
    Sphere();
// methods
    virtual IntersectResult intersect(const GzRay &ray) const;
	virtual float getIntersectDistance(const GzRay &ray) const;
//protected:
// static methods
    //static float getRayDistance(const GzVector3 &c, float r, const GzRay &ray);
};

class Ellipsoid : public GzGeometry
{
public:
	// attributes
	GzVector3 center;
	GzVector3 arctic; // Arctic point, theta = 0, phi = any
	GzVector3 long_x; // Point for longitute calculation, theta = 90, phi = 0
	GzVector3 long_y; // Point for longitute calculation, theta = 90, phi = 90
					  // constructors
	Ellipsoid(const GzVector3 &c= GzVector3(0.0f, 0.0f, 0.0f),
		const GzMaterial &a_mat = GzMaterial::DEFAULT,
		const GzVector3 &x_axe = GzVector3(1.0f, 0.0f, 0.0f),
		const GzVector3 &y_axe = GzVector3(0.0f, 1.0f, 0.0f),
		const GzVector3 &z_axe = GzVector3(0.0f, 0.0f, 1.0f));

	
	// methods
	virtual IntersectResult intersect(const GzRay &ray) const;
	virtual float getIntersectDistance(const GzRay &ray) const;
	//protected:
	// static methods
	//static float getRayDistance(const GzVector3 &c, float r, const GzRay &ray);
};


//class Ellipsoid: public Sphere
//{
//};


class Union: public GzGeometry
{
public:
// attributes
    int num;
    GzGeometry ** gArray;
// constructors
    Union(int g_num, GzGeometry ** g_p_arr);
    Union();
// destructor
    ~Union();
// methods
    virtual IntersectResult intersect(const GzRay &ray) const;
	virtual float getIntersectDistance(const GzRay &ray) const;
};


class Rec : public GzGeometry
{
public:
	// attributes
	GzVector3 base;
	GzVector3 bX;
	GzVector3 bY;
	// constructors
	
	Rec(); // Default constructor. Build a plane at (0,0,0) normal as (0, 1, 0).
		   // methods

	Rec::Rec(const GzVector3 &ori, const GzVector3 &x,
		const GzVector3 &y, const GzMaterial &a_mat = GzMaterial::DEFAULT);


	virtual IntersectResult intersect(const GzRay &ray) const;
	virtual float getIntersectDistance(const GzRay &ray) const;
};

#endif

