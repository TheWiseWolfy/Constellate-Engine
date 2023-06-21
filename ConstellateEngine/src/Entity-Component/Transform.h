/*
File:Transform.h

Simple struct that makes it convenient to describe the complete position scale and rotation of an object.
Based on glm vectors
*/
#pragma once

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace csl {

    struct Transform {
        //Transform data
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::vec3 _rotation;

        Transform() {
            _position = { 0.0, 0.0, 0.0 };
            _scale = { 1.0,1.0,1.0 };
            _rotation = { 0.0,0.0,0.0 };
        }

        //Getters
        glm::vec3 getPosition() const { return _position; }
        glm::vec3 getScale() const { return _scale; }
        glm::vec3 getRotation() const { return _rotation; }

        //Setters
        void setPosition(const glm::vec3& position) { _position = position; }
        void setScale(const glm::vec3& scale) { _scale = scale; }
        void setRotation(const glm::vec3& rotation) { _rotation = rotation; }

        //Diractional vectors

        glm::vec3 GetFrontVector() {

            // Construct rotation matrices
            glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 R = Rz * Ry * Rx;

            glm::vec4 unitVector(0.0f, 0.0f, 1.0f, 0.0f);
            glm::vec4 result = R * unitVector;

            glm::vec3 rotatedUnitVector = glm::normalize(glm::vec3(result.x, result.y, result.z));
            return rotatedUnitVector;
        }





         // Calculate up vector
        glm::vec3 getUpVector() const {
  

            // Construct rotation matrices
            glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 R = Rz * Ry * Rx;

            glm::vec4 upVector(0.0f, 1.0f, 0.0f, 0.0f);
            glm::vec4 upResult = R * upVector;

            glm::vec3 rotatedUpVector = glm::normalize(glm::vec3(upResult.x, upResult.y, upResult.z));
            return rotatedUpVector;
        }

    };

}