#include "stdafx.h"
#include "GzRender.h"
#include <cmath>

GzRender::GzRender() : p_display(nullptr), p_camera(nullptr), p_light_arr(nullptr), p_scene(nullptr), options(0)
{
}

GzRender::GzRender(GzDisplay * p_disp) : p_display(p_disp), p_camera(nullptr), p_light_arr(nullptr), p_scene(nullptr), options(0)
{
}

int GzRender::putCamera(GzCamera *p_cam)
{
    this->p_camera = p_cam;
    return GZ_SUCCESS;
}

int GzRender::putLights(GzLight *p_li_arr[], int num_lights)
{
    this->p_light_arr = new GzLight*[num_lights];
    for (int i = 0; i < num_lights; ++i)
    {
        this->p_light_arr[i] = p_li_arr[i];
    }
    this->n_lights = num_lights;
    return GZ_SUCCESS;
}

int GzRender::putScene(GzGeometry *p_sce)
{
    this->p_scene = p_sce;
    return GZ_SUCCESS;
}

int GzRender::putAttribute(int attribute)
{
    this->options |= attribute;
    return GZ_SUCCESS;
}

int GzRender::renderToDisplay()
{
    int status(GZ_SUCCESS);
    for (int j = 0; j < this->p_display->yres; ++j)
    {
        for (int i = 0; i < this->p_display->xres; ++i)
        {
            //for (int k = 0; k < this->p_AASetting->nSample; ++k)
            float yj = j + 0.5f; // Add 0.5 for the center of the pixel
            float xi = i + 0.5f;
            float ndcx = xi * 2.0f / this->p_display->xres - 1;
            float ndcy = -(yj * 2.0f / this->p_display->yres - 1);
            GzRay rForPixel = this->p_camera->generateRay(ndcx, ndcy);
            IntersectResult inter = this->p_scene->intersect(rForPixel);
            if (inter.p_geometry)
            {
                this->p_display->putDisplay(i, j, shade(inter, rForPixel, this->p_scene, this->p_light_arr, this->n_lights));
            }
        }
    }
    return status;
}

GzColor GzRender::shade(const IntersectResult &inter, const GzRay &incRay, const GzGeometry *p_global, GzLight *p_li_arr[], int num_lights)
{
    //GzColor computedColor(0.0f, 0.0f, 0.0f);
    //GzColor specularPart = inter.p_geometry->material.reflectiveness * specularLight(inter, *p_li_arr);
    GzColor reflectPart(0.0f, 0.0f, 0.0f);
    GzColor diffusePart(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < num_lights; ++i)
    {
        if (p_li_arr[i]->type == 0)
        {
            //if light source visible
            GzVector3 incDir = incRay.direction.flip();
            GzVector3 lightDir = p_li_arr[i]->position;
            float nDotL = lightDir.dotMultiply(inter.normal);
            float nDotRay = incDir.dotMultiply(inter.normal);
            if (nDotL * nDotRay > 0.0f)
            {
                GzVector3 flipN = inter.normal;
                if (nDotL < 0.0f)
                {
                    flipN = inter.normal.flip();
                    nDotL = -nDotL;
                }
                GzVector3 reflecDir = 2 * nDotL * flipN - lightDir;
                float eDotR = (incDir.dotMultiply(lightDir) < 0.0f ? 0.0f : incDir.dotMultiply(lightDir));
                reflectPart = reflectPart + p_li_arr[i]->color * std::pow(eDotR, inter.p_geometry->material.s);
                diffusePart = diffusePart + p_li_arr[i]->color.modulate(inter.p_geometry->material.Kd) * nDotL;
            }
        }
        else if (p_li_arr[i]->type == 1)
        {
            GzVector3 lightDir = (p_li_arr[i]->position - inter.position).normalize();
        }
        //reflectPart = reflectPart + p_li_arr[i]->color * std::pow(eDotR, inter.p_geometry->material.s);
    }
    reflectPart = reflectPart.exposure();
    diffusePart = diffusePart.exposure();
    return inter.p_geometry->material.r * reflectPart + (1.0f - inter.p_geometry->material.r) * diffusePart;
}

//GzColor GzRender::specularLight(const IntersectResult &inter, const GzLight *p_li_arr)
//{
    
//}
