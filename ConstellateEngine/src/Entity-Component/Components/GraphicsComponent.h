#pragma once

#include "cslpch.h"

#include "Renderer/Geometry/RenderBuffer.h"
#include "Renderer/Geometry/VertexArray.h"

#include "Component.h"
#include <assimp/scene.h>

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

        GraphicsComponent(aiMesh* mesh) : _vertexArray(std::move(VertexArray::Create()))
        {
            std::vector<float> vertices;
            

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);

                vertices.push_back(0.7);
                vertices.push_back(0.7);
                vertices.push_back(0.7);
                vertices.push_back(1.0);

            }

            std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::VertexBufferOf(&vertices[0], vertices.size()* sizeof(float)  ));

            BufferLayout layout = {
                                    { OpenGLDataType::Float3, "a_Position" },
                                    { OpenGLDataType::Float4, "a_Color" }
            };
            vertexBuffer->SetLayout(layout);

            std::vector<unsigned int> indices;


            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
                {
                    indices.push_back(mesh->mFaces[i].mIndices[j]);
   
                }
            }
            std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::IndexBufferOf(&indices[0], indices.size() *sizeof(int)));


            _vertexArray->AddVertexBuffer(std::move(vertexBuffer));
            _vertexArray->SetIndexBuffer(std::move(indexBuffer));

            _position = glm::vec3(1, -1, 0);
            _scale = glm::vec3(0.7, 0.7, 0.7);

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