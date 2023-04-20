#pragma once

#include "cslpch.h"

#include "Entity-Component/Entity.h"
#include "Entity-Component/Components/GraphicsComponent.h"
#include <assimp/scene.h>


namespace csl {
	class Entity;
	class EntityFactory {
	private:
		static void processNode(aiNode* node, const aiScene* scene, Entity* root, bool wireframe, std::string shader)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

				//Here we do the magic bit
				Entity* meshEntity = root->createChildEntity();

				aiVector3D aiPosition;
				aiVector3D aiScale;
				aiVector3D aiRotation;

				node->mTransformation.Decompose(aiScale, aiRotation, aiPosition);

				meshEntity->setTransform(Transform(
					{ aiPosition.x, aiPosition.y, aiPosition.z },
					{ aiScale.x, aiScale.y, aiScale.z },
					{ aiRotation.x, aiRotation.y, aiRotation.z }
				));


				GraphicsComponent& component = meshEntity->addComponent<GraphicsComponent>(mesh);
				component.SetIsWireframe(wireframe);

				component.setShader(shader);
			}

			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene, root, wireframe, shader);
			}
		}
	public:
		static Entity* SceneToEntityHierachy(const aiScene* scene, Entity* root, bool wireframe = false, std::string shader = "shader1") {

			processNode(scene->mRootNode, scene, root, wireframe, shader);

			return root;
		}
	};


}