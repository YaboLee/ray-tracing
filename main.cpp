#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
// Remember to change bool to float;
float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    // a, b, c are parameters of a function(equation);
    float a = dot(r.direction(), r.direction() );
    float b = 2.0*dot(oc, r.direction() );
    float c = dot(oc, oc) - radius*radius;
    // Check the intersection;
    float discriminant = b*b -4*a*c;

    if (discriminant < 0) { // if  less than 0, no intersection;
        return -1.0;
    }
    else { // else, return the coordinate;
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}

vec3 color(const ray& r) {
    // This is the sphere;
    float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        // Get the normal of the shpere: hit_point - center
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1) );
        return 0.5*vec3(N.x()+1.0, N.y()+1.0, N.z()+1.0);
    }
    // This is the background;
    vec3 unit_direction = unit_vector(r.direction() );
    t = 0.5*(unit_direction.y() + 1.0);
    // (1-t)*white + t*blue;
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);

}



int main() {
    std::ofstream myfile;
    myfile.open("output.ppm");

    int nx = 200;
    int ny = 100;
    myfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++){
            // float r = float(i) / float(nx);
            // float g = float(j) / float(ny);
            // float b = 0.2;

            // vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);

            int ir = int(255.99*col[0] );
            int ig = int(255.99*col[1] );
            int ib = int(255.99*col[2] );
            myfile<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }

}
