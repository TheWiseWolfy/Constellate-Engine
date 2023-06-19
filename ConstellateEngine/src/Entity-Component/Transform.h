/*
File:Transform.h

Simple struct that makes it convenient to describe the complete position scale and rotation of an object.
Based on glm vectors
*/
#pragma once

#include "glm.hpp"

namespace csl {

    struct Transform {
        //Transform data
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::vec3 _rotation;

        Transform() {
            _position = { 0.0, 0.0, 0.0 };
            _scale = { 1.0,1.0,1.0 };
            _rotation = { 1.0,1.0,1.0 };
        }

        Transform(glm::vec3 pozition) {
            _position = pozition;
            _scale = { 1.0,1.0,1.0 };
            _rotation = { 1.0,1.0,1.0 };

        }

        Transform(glm::vec3 pozition, glm::vec3 scale) {
            _position = pozition;
            _scale = scale;
            _rotation = { 1.0,1.0,1.0 };

        }

        Transform(glm::vec3 pozition, glm::vec3 scale, glm::vec3 rotation) {
            _position = pozition;
            _scale = scale;
            _rotation = rotation;

        }

        //Getters
        glm::vec3 getPosition() const { return _position; }
        glm::vec3 getScale() const { return _scale; }
        glm::vec3 getRotation() const { return _rotation; }

        //Setters
        void setPosition(const glm::vec3& position) { _position = position; }
        void setScale(const glm::vec3& scale) { _scale = scale; }
        void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
    };

}