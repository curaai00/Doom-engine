#pragma once 

#include "mesh.h"
#include "util_mat.h"

#include <SDL2/SDL.h>
#include <math.h>

inline void draw_triangle(SDL_Renderer* rend, triangle tri)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    SDL_RenderDrawLine(rend, (int)tri.pts[0].x, (int)tri.pts[0].y, (int)tri.pts[1].x, (int)tri.pts[1].y);
    SDL_RenderDrawLine(rend, (int)tri.pts[1].x, (int)tri.pts[1].y, (int)tri.pts[2].x, (int)tri.pts[2].y);
    SDL_RenderDrawLine(rend, (int)tri.pts[2].x, (int)tri.pts[2].y, (int)tri.pts[0].x, (int)tri.pts[0].y);

    SDL_SetRenderDrawColor(rend,0,0,0,255);
}

class Drawable
{
public:
    Drawable(const mesh& _mesh)
        : obj(_mesh)
    {
        rotateMat = mat44::identical();
        translateMat = mat44::identical();
        scaleMat = mat44::identical();
    }
    ~Drawable(){}

    std::vector<triangle> getConverted(const mat44& mat){
        std::vector<triangle> cvtTris; 
        for(const auto& tri : obj.trig) {
            triangle newTri;
            newTri.pts[0] = mat * tri.pts[0];
            newTri.pts[1] = mat * tri.pts[1];
            newTri.pts[2] = mat * tri.pts[2];
            cvtTris.push_back(newTri);
        }
        return cvtTris;
    }

    const mat44 world_matrix(void)
    {
        return rotateMat * scaleMat * translateMat;
    }

    void setTranslate(float x, float y, float z)
    {
        translateMat = util::mat::getTranslationMat(vec3d {x, y, z});
    }
    void setScale(float x, float y, float z)
    {
        scaleMat = util::mat::getScaleMat(vec3d {x, y, z});
    }
    void setRotate(float x, float y, float z)
    {
        rotateMat = util::mat::getRotationMat(vec3d {x, y, z});
    }

private:
    const mesh obj;
    mat44 translateMat, scaleMat, rotateMat;
};