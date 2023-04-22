#pragma once

#include <assimp/scene.h>

#include "cslpch.h"

#include "glm.hpp"
#include "Component.h"
#include "Physics/CollisionPrimitives.h"
#include "Entity-Component/Entity.h"

namespace csl {
    
    class ColliderComponent : public Component {
    private:
        std::vector<Triangle> triangles;
        std::vector<Plane> planes;

    public:

        ColliderComponent(const aiScene* scene) {

            aiMesh* mesh = scene->mMeshes[0]; // Assuming there is only one mesh in the scene

            for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
                aiFace face = mesh->mFaces[i];

                //This section calculates the triangles.
                Triangle triangle;
                triangle.vertices[0] = glm::vec3(
                    mesh->mVertices[face.mIndices[0]].x, 
                    mesh->mVertices[face.mIndices[0]].y, 
                    mesh->mVertices[face.mIndices[0]].z
                );

                triangle.vertices[1] = glm::vec3(
                    mesh->mVertices[face.mIndices[1]].x,
                    mesh->mVertices[face.mIndices[1]].y, 
                    mesh->mVertices[face.mIndices[1]].z
                );

                triangle.vertices[2] = glm::vec3(
                    mesh->mVertices[face.mIndices[2]].x,
                    mesh->mVertices[face.mIndices[2]].y,
                    mesh->mVertices[face.mIndices[2]].z
                );
                triangle.normal = glm::vec3(mesh->mNormals[face.mIndices[0]].x, mesh->mNormals[face.mIndices[0]].y, mesh->mNormals[face.mIndices[0]].z);

                triangles.push_back(triangle);

                //And this section the planes 

                aiVector3D v1 = mesh->mVertices[face.mIndices[0]];
                aiVector3D v2 = mesh->mVertices[face.mIndices[1]];
                aiVector3D v3 = mesh->mVertices[face.mIndices[2]];

                aiVector3D normal1 = mesh->mNormals[face.mIndices[0]];
                aiVector3D normal2 = mesh->mNormals[face.mIndices[1]];
                aiVector3D normal3 = mesh->mNormals[face.mIndices[2]];

                aiVector3D faceNormal = (normal1 + normal2 + normal3) / 3.0f;
                faceNormal.Normalize();

                float distance = faceNormal.x * v1.x + faceNormal.y * v1.y + faceNormal.z * v1.z;

                Plane plane(faceNormal.x, faceNormal.y, faceNormal.z, distance);
                planes.push_back(plane);
            }
        }

        const std::vector<Triangle> GetTriangles() {
            std::vector<Triangle> transformedTriangles;
            transformedTriangles.reserve(triangles.size());

            glm::vec3 position  = this->getEntity()->getAbsolutePosition();

            for (const auto& triangle : triangles) {
                Triangle transformedTriangle;

                transformedTriangle.vertices[0] = triangle.vertices[0] + position;
                transformedTriangle.vertices[1] = triangle.vertices[1] + position;
                transformedTriangle.vertices[2] = triangle.vertices[2] + position;
                transformedTriangles.push_back(transformedTriangle);
            }

            return transformedTriangles;
        }

        const std::vector<Plane> GetPlanes() {
            return planes;

        }

        void update(float mFT) override
        {
        }
        void draw() override
        {
        }



        ComponentType GetComponentType() override {
            return ComponentType::ColliderComponentType;
        }
    };

}