//
// Created by Gerald Jones on 4/20/25.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class material;

class sphere: public hitable {
  public:
    sphere() {}
    sphere(vec3 cen, float r, material* mat_ptr) : center(cen), radius(r), mat_ptr(mat_ptr) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 center;
    float radius;
    material* mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 oc = r.origin() - center; // Vector from the sphere's center to the ray's origin
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - a*c;
  if (discriminant > 0) {
    float temp = (-b - sqrt(b*b-a*c)) / a; // Nearer intersection point
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }
    temp = (-b + sqrt(b*b-a*c)) / a; // Further intersection point
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }
  }
  return false;
}

#endif //SPHERE_H
