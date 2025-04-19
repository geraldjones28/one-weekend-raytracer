//
// Created by Gerald Jones on 4/19/25.
//

#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {
    public:
      ray() {}
      ray(const vec3& a, const vec3& b) { A = a; B = b; }
      vec3 origin() const     { return A; }
      vec3 direction() const  { return B; }
      /* returns a point on the ray at paramenter t, used for tracing rays through
         a scene */
      vec3 point_at_parameter(float t) const { return A + (B * t); }

      vec3 A;
      vec3 B;
};

#endif //RAY_H
