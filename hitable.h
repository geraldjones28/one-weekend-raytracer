//
// Created by Gerald Jones on 4/20/25.
//

#ifndef HITABLEH_H
#define HITABLEH_H

#include "ray.h"

struct hit_record {
  float t; // The t value where the ray hits the object (how far along the ray)
  vec3 p; // The actual point of intersection
  vec3 normal; // The surface normal at that point - used for lighting and shading
};

class hitable {
  public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //HITABLEH_H
