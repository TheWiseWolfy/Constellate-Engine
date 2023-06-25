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
        bool _isWireframe = { false } ;
        bool _isTextured = { false };
        int _textureID = -1;
        std::string _shader;

    public:

        GraphicsComponent(std::unique_ptr<VertexArray> vertexArray) : _vertexArray(std::move(vertexArray)) {}

        GraphicsComponent(aiMesh* mesh) : _vertexArray(std::move(VertexArray::Create()))
        {
            std::vector<float> vertices;
            std::vector<unsigned int> indices;


            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);

                vertices.push_back(mesh->mNormals[i].x);
                vertices.push_back(mesh->mNormals[i].y);
                vertices.push_back(mesh->mNormals[i].z);

                vertices.push_back(0.4);
                vertices.push_back(0.4);
                vertices.push_back(0.4);
                vertices.push_back(1.0);

                // Extract UV coordinates
                if (mesh->HasTextureCoords(0)){
                    vertices.push_back(1- mesh->mTextureCoords[0][i].x); // X is reverted for some reason
                    vertices.push_back(mesh->mTextureCoords[0][i].y);
                }
                else {
                    vertices.push_back(0.0f);
                    vertices.push_back(0.0f);
                }
            }

            std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::VertexBufferOf(&vertices[0], vertices.size()* sizeof(float)  ));

            BufferLayout layout = {
                                    { OpenGLDataType::Float3, "a_Position" },
                                    { OpenGLDataType::Float3, "a_Normals" },
                                    { OpenGLDataType::Float4, "a_Color" },
                                    { OpenGLDataType::Float2, "a_vertexUV" }
            };

            vertexBuffer->SetLayout(layout);

            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
                {
                    indices.push_back(mesh->mFaces[i].mIndices[j]);
                }
            }

            std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::IndexBufferOf(&indices[0], indices.size() ));

            _vertexArray->AddVertexBuffer(std::move(vertexBuffer));
            _vertexArray->SetIndexBuffer(std::move(indexBuffer));
        }

        bool isWireframe() {
            return _isWireframe;
        }

        void SetIsWireframe(bool isWireframe) {
            _isWireframe = isWireframe;
        }

        std::string getShader() {
            return _shader;
        }

        void setShader(std::string shader) {
            _shader = shader;
        }

        void SetIsTextured(bool isTextured) {
            _isTextured = isTextured;
        }

        bool IsTextured() {
            return _isTextured;
        }

        void SetTextureID(int id) {
            _textureID = id;
        }

        int GetTextureID() {
            return _textureID;
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

        ComponentType GetComponentType() override {
            return ComponentType::GraphicsComponentType;
        }
    };

}