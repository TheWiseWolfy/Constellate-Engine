#pragma once

#include <glm/glm.hpp>

namespace csl {

    struct Triangle {
        glm::vec3 vertices[3];
        glm::vec3 normal;
    };

    struct Plane {
        //Note: we only need the normal and the distance of the plane to do the projections
        Plane(float x, float y, float z, float distance) {
            normal = glm::vec3(x, y, z);
            this->distance = distance;
        }

        glm::vec3 normal;
        float distance;
    };
}