#pragma once 

#include <math.h>
#include <tuple>
#include <vector>
#include <iostream>


struct vec3d
{
    float x, y, z;

    inline vec3d operator+ (const vec3d v) const {
        return vec3d{x + v.x, y + v.y, z + v.z};
    }
    inline vec3d operator- (const vec3d v) const {
        return vec3d{x - v.x, y - v.y, z - v.z};
    }
    inline vec3d operator* (const vec3d v) const {
        return vec3d{x * v.x, y * v.y, z * v.z};
    }
    inline vec3d operator/ (const vec3d v) const {
        return vec3d{x / v.x, y / v.y, z / v.z};
    }
    inline vec3d operator* (const float a) const {
        return vec3d{x * a, y * a, z * a};
    }
    inline vec3d operator/ (const float a) const {
        return vec3d{x / a, y / a, z / a};
    }
    inline vec3d operator- (void) const {
        return vec3d{-x, -y, -z};
    }
    inline float length(void) const {
        return sqrt(x*x + y*y + z*z);
    }
    inline vec3d normalize(void) const {
        return *this / length();
    }

    friend std::ostream& operator<<(std::ostream& os, const vec3d& vec)
    {
        os << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
        return os;
    } 
};

struct triangle
{
    vec3d pts[3];
};

using vecIdx = std::tuple<int, int, int>;

struct mat44 
{
    mat44() {}
    mat44(vec3d a, vec3d b, vec3d c, vec3d d)
    {
        m[0][0] = a.x; m[1][0] = a.y; m[2][0] = a.z;
        m[0][1] = b.x; m[1][1] = b.y; m[2][1] = b.z;
        m[0][2] = c.x; m[1][2] = c.y; m[2][2] = c.z;
        m[0][3] = d.x; m[1][3] = d.y; m[2][3] = d.z;
    }

    float m[4][4] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    mat44 operator* (const mat44& mat) const
    {
        mat44 res;
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                for(int k=0; k<4; k++) {
                    res.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return res;
    }
    vec3d operator* (const vec3d& vec) const
    {
        vec3d res;
        res.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2] + m[0][3];
        res.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] + m[1][3];
        res.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2] + m[2][3];
        float w = vec.x * m[3][0] + vec.y * m[3][1] + vec.z * m[3][2] + m[3][3];
        if(w != 0.0f)
            res.x /= w; res.y /= w; res.z /= w;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const mat44& mat)
    {
        os << mat.m[0][0] << ' ' << mat.m[0][1] << ' ' << mat.m[0][2] << ' ' << mat.m[0][3] << std::endl;
        os << mat.m[1][0] << ' ' << mat.m[1][1] << ' ' << mat.m[1][2] << ' ' << mat.m[1][3] << std::endl;
        os << mat.m[2][0] << ' ' << mat.m[2][1] << ' ' << mat.m[2][2] << ' ' << mat.m[2][3] << std::endl;
        os << mat.m[3][0] << ' ' << mat.m[3][1] << ' ' << mat.m[3][2] << ' ' << mat.m[3][3] << std::endl;
        return os;
    } 

    static mat44 identical(void)
    {
        mat44 mat;
        mat.m[0][0] = 1;
        mat.m[1][1] = 1;
        mat.m[2][2] = 1;
        mat.m[3][3] = 1;
        return mat;
    }
};

using verIdx = std::tuple<uint, uint, uint>;

struct mesh
{
    mesh(std::vector<vec3d> vertexes, std::vector<verIdx> indices)
         : vertexes(vertexes), indices(indices) 
    {}

    const std::vector<vec3d> vertexes;
    const std::vector<verIdx> indices;
    std::vector<triangle> triangles(void) const
    {
        std::vector<triangle> tris;
        for(const verIdx& idx : indices) {
            tris.push_back(triangle{
                vertexes[std::get<0>(idx)], 
                vertexes[std::get<1>(idx)], 
                vertexes[std::get<2>(idx)]
            });
        }
        return tris;
    }
};

inline vec3d cross_product(const vec3d& v1, const vec3d& v2)
{
    vec3d norm {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    float unit = sqrtf(norm.x * norm.x + norm.y * norm.y + norm.y * norm.y);
    norm = norm / unit;
    return norm;
}