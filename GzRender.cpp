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
    GzColor refractPart(0.0f, 0.0f, 0.0f);
    bool hasRefra(inter.p_geometry->material.f > 0.0f);
    bool hasOpaque(inter.p_geometry->material.f < 1.0f);
    GzVector3 incDir = incRay.direction.flip();
    GzVector3 flipN = inter.normal;
    float nDotRay = incDir.dotMultiply(flipN); // This is cos(i) or -cos(i)
    float nRelative = inter.p_geometry->material.n;
    bool backSide(nDotRay < 0.0f);
    if (backSide)
    {
        flipN = inter.normal.flip();
        nDotRay = -nDotRay;
        nRelative = 1.0f / nRelative;
    }
    // Now flipN is the normal vector at incident ray side
    // incDir is eye vector
    // nRelative is the ratio of n_this_side/n_that_side
    if (hasRefra)
    {
        GzVector3 refractDir = incRay.direction;
        if (nDotRay != 0.0f && nDotRay != 1.0f)
        {
            GzVector3 tangentDir = (incDir - nDotRay * flipN).normalize();
            float sin_i = std::sqrt(1.0f - nDotRay * nDotRay);
            float sin_r = sin_i / nRelative;
            if (sin_r < 1.0f)
            {
                float cos_r = std::sqrt(1.0f - sin_r * sin_r);
                refractDir = (flipN.flip() * cos_r + tangentDir.flip() * sin_r).normalize();
                GzRay refractRay(inter.position, refractDir);
                GzColor refractLight = this->shade((this->p_scene->intersect(refractRay)), refractRay, inter.p_geometry->material.f * bar);
                refractPart = refractPart + refractLight;
            }
            else
            {
                hasRefra = false;
            }
        }
    }
    // End of refraction part. Only need to deal with mixing later.
    if (hasOpaque)
    {
        GzVector3 reflectDir = 2.0f * nDotRay * flipN - incDir;
        GzRay reflectRay(inter.position, reflectDir);
        GzColor reflectLight = this->shade((this->p_scene->intersect(reflectRay)), reflectRay, inter.p_geometry->material.r * bar);
        reflectPart = reflectPart + reflectLight;
        GzTexture tex = inter.p_geometry->material.texture;
        for (int i = 0; i < this->n_lights; ++i)
        {
            // Could use this part as a function and call multiple times if type==AREA_LIGHT
            // < For each single light, this part should be identical >
            // void shadeNonRecurSingleLight(const IntersectResult &inter, const GzRay &incRay, GzColor &reflectPart, GzColor &diffusePart)
            // input: this, inter, incRay, reflectPart, diffusePart
            // output: reflectPart, diffusePart (alter inside)
            GzVector3 lightDir;
            if (this->p_light_arr[i]->type == DIR_LIGHT)
            {
                lightDir = p_light_arr[i]->position;
            }
            else if (p_light_arr[i]->type == POINT_LIGHT)
            {
                lightDir = (p_light_arr[i]->position - inter.position).normalize();
            }
            float lightCoeff = 1.0f;
            lightCoeff = getLightCoeff(inter.position, p_light_arr[i]);
            // Should return a coefficient for this light, in how big a portion this light should be used
            if (lightCoeff == 0.0f)
            {
                continue; // skip this light
            }
            //if (this->p_light_arr[i]->type == DIR_LIGHT)
            //{
                //lightDir = p_light_arr[i]->position;
                //GzRay shadowRay(inter.position, lightDir);
                //if (this->p_scene->intersect(shadowRay).p_geometry && this->p_scene->intersect(shadowRay).p_geometry->material.f == 0.0f)
                //{
                    //continue;
                //}
            //}
            //else if (p_light_arr[i]->type == POINT_LIGHT)
            //{
                //lightDir = (p_light_arr[i]->position - inter.position).normalize();
                //GzRay shadowRay(inter.position, lightDir);
                //if (this->p_scene->intersect(shadowRay).distance <= (p_light_arr[i]->position - inter.position).length()
                        //&& this->p_scene->intersect(shadowRay).p_geometry->material.f == 0.0f)
                //{
                    //continue;
                //}
            //}
            // Common part for dir light and point light
            // flipN
            float nDotL = lightDir.dotMultiply(inter.normal);
            
            if (nDotL * nDotRay > 0.0f)
            {
                //GzVector3 flipN = inter.normal;
                //if (nDotL < 0.0f)
                //{
                    //flipN = inter.normal.flip();
                    //nDotL = -nDotL;
                //}
                //GzVector3 reflecDir = 2 * nDotL * flipN - lightDir;
                float lDotR = (lightDir.dotMultiply(reflectDir) < 0.0f ? 0.0f : lightDir.dotMultiply(reflectDir));
                //reflectPart = reflectPart + p_light_arr[i]->color * std::pow(lDotR, inter.p_geometry->material.s);
                reflectPart = reflectPart + p_light_arr[i]->color * std::pow(lDotR, inter.p_geometry->material.s) * lightCoeff;

                if (tex.hasTexture())
                {
                    diffusePart = diffusePart + p_light_arr[i]->color.modulate(tex.tex_map(inter.u, inter.v)) * nDotL * lightCoeff;
                }
                else
                {
                    diffusePart = diffusePart + p_light_arr[i]->color.modulate(inter.p_geometry->material.Kd) * nDotL * lightCoeff;
                }
            }
        } // </ For each light, this part should be identical >
        //TODO This correspond with radiosity/diffuse interreflection
        //if (tex.hasTexture())
        //{
            //diffusePart = diffusePart + reflectLight.modulate(tex.tex_map(inter.u, inter.v)) * inter.normal.dotMultiply(reflectDir);
        //}
        //else
        //{
            //diffusePart = diffusePart + reflectLight.modulate(inter.p_geometry->material.Kd) * inter.normal.dotMultiply(reflectDir);
        //}
        reflectPart = reflectPart.exposure();
        diffusePart = diffusePart.exposure();
    }
    if (hasRefra)
    {
        return inter.p_geometry->material.r * reflectPart + inter.p_geometry->material.f * refractPart + (1.0f - inter.p_geometry->material.r - inter.p_geometry->material.f) * diffusePart;
    }
    return (inter.p_geometry->material.r + inter.p_geometry->material.f) * reflectPart + (1.0f - inter.p_geometry->material.r - inter.p_geometry->material.f) * diffusePart;
}

float GzRender::getLightCoeff(const GzVector3 &interPos, const GzLight *p_light)
{
    float coeff(1.0f);
    if (p_light->type == DIR_LIGHT)
    {
        GzVector3 lightDir(p_light->position);
        GzRay shadowRay(interPos, lightDir);
        IntersectResult firstInter(this->p_scene->intersect(shadowRay));
        if (firstInter.p_geometry)
        {
            if(firstInter.p_geometry->material.f == 0.0f)
            {
                return 0.0f;
            }
            else
            {
                return firstInter.p_geometry->material.f * getLightCoeff(firstInter.position, p_light);
            }
        }
    }
    else if (p_light->type == POINT_LIGHT)
    {
        GzVector3 lightDir((p_light->position - interPos).normalize());
        GzRay shadowRay(interPos, lightDir);
        IntersectResult firstInter(this->p_scene->intersect(shadowRay));
        if (firstInter.distance <= (p_light->position - interPos).length())
        {
            if (firstInter.p_geometry->material.f == 0.0f)
            {
                return 0.0f;
            }
            else
            {
                return firstInter.p_geometry->material.f * getLightCoeff(firstInter.position, p_light);
            }
        }
    }
    return coeff;
}
