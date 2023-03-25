#pragma once

#include "cslpch.h"

#include "Renderer/Geometry/RenderBuffer.h"
#include "Component.h"

namespace csl {

    class GraphicsComponent : public Component {
    private:
        std::unique_ptr<VertexArray> _vertexArray;
        glm::vec3 _position;
        glm::vec3 _scale;

    public:

        GraphicsComponent(std::unique_ptr<VertexArray> vertexArray, glm::vec3 position, glm::vec3 scale) :
            _vertexArray(std::move(vertexArray)),
            _position(position),
            _scale(scale)
        {

        }

        void update(float mFT) override
        {
        }
        void draw() override
        {
        }

        std::unique_ptr<VertexArray>& GetVertexArray() {
            return _vertexArray;
        }

        glm::vec3 GetPosition() {
            return _position;
        }

        glm::vec3 GetScale() {
            return _scale;
        }
    };

}