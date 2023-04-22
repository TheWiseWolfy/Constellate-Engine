#pragma once

#include <glm/glm.hpp>

namespace csl {


    struct CollisionDetails {
        glm::vec3 pointA;
        glm::vec3 pointB;

        glm::vec3 normal; // B - A normalized
        float depth; // lenght of B-A
        
        CollisionDetails() {
            pointA = glm::vec3(0, 0, 0);
            pointB = glm::vec3(0, 0, 0);
            normal = glm::vec3(0, 0, 0);
            depth = 0;
        }
    };


    //struct Triangle {
    //    glm::vec3 vertices[3];
    //    glm::vec3 normal;
    //};

    //struct Plane {
    //    //Note: we only need the normal and the distance of the plane to do the projections
    //    Plane(float x, float y, float z, float distance) {
    //        normal = glm::vec3(x, y, z);
    //        this->distance = distance;
    //    }

    //    glm::vec3 normal;
    //    float distance;
    //};
}