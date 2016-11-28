#include "stdafx.h"
#include "GzRender.h"
#include <cmath>

GzRender::GzRender() : p_display(nullptr), p_camera(nullptr), p_light_arr(nullptr), n_lights(0), p_scene(nullptr), options(0), p_AA(nullptr)
{
}

GzRender::GzRender(GzDisplay * p_disp) : p_display(p_disp), p_camera(nullptr), p_light_arr(nullptr), n_lights(0), p_scene(nullptr), options(0)
{
    //GzVector3 *uniKer = new GzVector3(0.0f, 0.0f, 1.0f);
    this->p_AA = new GzAASetting(1);
}

GzRender::~GzRender()
{
    delete p_camera;
    for (int i = 0; i < n_lights; ++i)
    {
        delete p_light_arr[i];
    }
    delete[] p_light_arr;
    delete p_scene;
    delete p_AA;
}

int GzRender::putCamera(GzCamera *p_cam)
{
    this->p_camera = p_cam;
    return GZ_SUCCESS;
}

int GzRender::putLights(GzLight **p_li_arr, int num_lights)
{
    this->p_light_arr = p_li_arr;
    //for (int i = 0; i < num_lights; ++i)
    //{
        //this->p_light_arr[i] = p_li_arr[i];
    //}
    this->n_lights = num_lights;
    return GZ_SUCCESS;
}

int GzRender::putScene(GzGeometry *p_sce)
{
    this->p_scene = p_sce;
    return GZ_SUCCESS;
}

int GzRender::putAASetting(GzAASetting *p_aa)
{
    this->p_AA = p_aa;
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
            GzColor pixelColor(0.0f, 0.0f, 0.0f);
            //for (int k = 0; k < this->p_AASetting->nSample; ++k)
            for (int k = 0; k < this->p_AA->kernelSize; ++k)
            {
                float yj = j + 0.5f + this->p_AA->ker[k].y; // Add 0.5 for the center of the pixel
                float xi = i + 0.5f + this->p_AA->ker[k].x;
                float ndcx = xi * 2.0f / this->p_display->xres - 1;
                float ndcy = -(yj * 2.0f / this->p_display->yres - 1);
                GzRay rForPixel = this->p_camera->generateRay(ndcx, ndcy);
                IntersectResult inter = this->p_scene->intersect(rForPixel);
                if (inter.p_geometry)
                {
                    pixelColor = pixelColor + this->p_AA->ker[k].z * this->shade(inter, rForPixel, 1.0f);
                    //this->p_display->putDisplay(i, j, shade(inter, rForPixel, this->p_scene, this->p_light_arr, this->n_lights));
                }
                else
                {
                    pixelColor = pixelColor + this->p_AA->ker[k].z * this->p_display->bgColor;
                }
            }
            this->p_display->putDisplay(i, j, pixelColor);
            //float yj = j + 0.5f; // Add 0.5 for the center of the pixel
            //float xi = i + 0.5f;
            //float ndcx = xi * 2.0f / this->p_display->xres - 1;
            //float ndcy = -(yj * 2.0f / this->p_display->yres - 1);
            //GzRay rForPixel = this->p_camera->generateRay(ndcx, ndcy);
            //IntersectResult inter = this->p_scene->intersect(rForPixel);
            //if (inter.p_geometry)
            //{
                //this->p_display->putDisplay(i, j, shade(inter, rForPixel, this->p_scene, this->p_light_arr, this->n_lights));
            //}
        }
    }
    return status;
}

GzColor GzRender::shade(const IntersectResult &inter, const GzRay &incRay, float bar)
{
    if (bar < EPSILON0 || inter.p_geometry == nullptr)
    {
        return GzColor::BLACK;
    }
    //if (inter.p_geometry == nullptr)
    //{
        //return this->p_display->bgColor;
    //}
    //GzColor computedColor(0.0f, 0.0f, 0.0f);
    //GzColor specularPart = inter.p_geometry->material.reflectiveness * specularLight(inter, *p_li_arr);
    GzColor reflectPart(0.0f, 0.0f, 0.0f);
    GzColor diffusePart(0.0f, 0.0f, 0.0f);
    GzVector3 incDir = incRay.direction.flip();
    float nDotRay = incDir.dotMultiply(inter.normal);
    GzVector3 reflectDir = 2.0f * nDotRay * inter.normal - incDir;
    GzRay reflectRay(inter.position, reflectDir);
    GzTexture tex = inter.p_geometry->material.texture;
    for (int i = 0; i < this->n_lights; ++i)
    {
        GzVector3 lightDir;
        if (this->p_light_arr[i]->type == DIR_LIGHT)
        {
            lightDir = p_light_arr[i]->position;
            GzRay shadowRay(inter.position, lightDir);
            if (this->p_scene->intersect(shadowRay).p_geometry)
            {
                continue;
            }
        }
        else if (p_light_arr[i]->type == POINT_LIGHT)
        {
            lightDir = (p_light_arr[i]->position - inter.position).normalize();
            GzRay shadowRay(inter.position, lightDir);
            if (p_scene->intersect(shadowRay).distance <= (p_light_arr[i]->position - inter.position).length())
            {
                continue;
            }
        }
        // Common part for dir light and point light
        float nDotL = lightDir.dotMultiply(inter.normal);
        
        if (nDotL * nDotRay > 0.0f)
        {
            //GzVector3 flipN = inter.normal;
            if (nDotL < 0.0f)
            {
                //flipN = inter.normal.flip();
                nDotL = -nDotL;
            }
            //GzVector3 reflecDir = 2 * nDotL * flipN - lightDir;
            float lDotR = (lightDir.dotMultiply(reflectDir) < 0.0f ? 0.0f : lightDir.dotMultiply(reflectDir));
            reflectPart = reflectPart + p_light_arr[i]->color * std::pow(lDotR, inter.p_geometry->material.s);

            if (tex.hasTexture())
            {
                diffusePart = diffusePart + p_light_arr[i]->color.modulate(tex.tex_map(inter.u, inter.v)) * nDotL;
            }
            else
            {
                diffusePart = diffusePart + p_light_arr[i]->color.modulate(inter.p_geometry->material.Kd) * nDotL;
            }
        }
    }
    //TODO
    GzColor reflectLight = this->shade((this->p_scene->intersect(reflectRay)), reflectRay, inter.p_geometry->material.r * bar);
    reflectPart = reflectPart + reflectLight;
    if (tex.hasTexture())
    {
        diffusePart = diffusePart + reflectLight.modulate(tex.tex_map(inter.u, inter.v)) * inter.normal.dotMultiply(reflectDir);
    }
    else
    {
        diffusePart = diffusePart + reflectLight.modulate(inter.p_geometry->material.Kd) * inter.normal.dotMultiply(reflectDir);
    }
    reflectPart = reflectPart.exposure();
    diffusePart = diffusePart.exposure();
    return inter.p_geometry->material.r * reflectPart + (1.0f - inter.p_geometry->material.r) * diffusePart;
}

//GzColor GzRender::specularLight(const IntersectResult &inter, const GzLight *p_li_arr)
//{
    
//}
