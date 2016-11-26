#ifndef GZRENDER_H
#define GZRENDER_H

#include "GzConstants.h"
#include "GzCamera.h"
#include "GzGeometry.h"
#include "GzLight.h"
#include "GzDisplay.h"

class GzRender
{
private:
    GzDisplay *p_display;
    GzCamera *p_camera;
    GzLight **p_light_arr; // Array of pointers
    int n_lights;
    GzGeometry *p_scene; // Union geometry object. Not an array
    int options;

private:
    GzRender(); // Default constructor. Disabled by using private.
public:
    GzRender(GzDisplay *p_disp);
    ~GzRender();
    int putCamera(GzCamera *p_cam);
    int putLights(GzLight **p_li_arr, int num_lights);
    int putScene(GzGeometry *p_sce);
    //int putAASetting(const GzAASetting *p_AASet);
    int putAttribute(int attribute);
    //bool isReady() const;
    int renderToDisplay();


//static function
    static GzColor shade(const IntersectResult &inter, const GzRay &incRay, const GzGeometry *p_global, GzLight *p_li_arr[], int num_lights);
};

#endif

