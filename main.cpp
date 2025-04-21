#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"
#include "material.h"

using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3(0,0,0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    // Window size
    int nx = 800;
    int ny = 400;
    // Number of random rays
    int ns = 100;

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable *list[5];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3))); // Middle Sphere
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0))); //Ground
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3)); //Right Sphere
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5)); //Left Sphere
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5)); //Bubble effect in left sphere
    hitable *world = new hitable_list(list,5);

    camera cam;

    // Core Ray Tracing Loop
    for (int j = ny-1; j >= 0; j--) { // Top to Bottom
        for (int i = 0; i < nx; i++) { // Left to Right
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) { // Anti-Aliasing: shooting ns random rays per pixel
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);

                ray r = cam.get_ray(u,v); // Firing a ray into world

                // vec3 p = r.point_at_parameter(2.0);
                col += color(r, world,0); // Recursive color computation
            }
            col /= float(ns); // Average the color over all samples
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) ); // Gamma correction, improves lighting
            // Writing image data VV
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}