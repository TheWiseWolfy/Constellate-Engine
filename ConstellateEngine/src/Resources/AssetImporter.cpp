#include "AssetImporter.h"
#include "cslpch.h"

#include "Entity-Component/Entity.h"
#include "Entity-Component/Components/GraphicsComponent.h"


namespace csl {
	void processNode(aiNode* node, const aiScene* scene, Entity* root);


	Entity* AssetImporter::ModelToEntityHierachy(std::string path, Entity* root) {

		Assimp::Importer importer;
		//std::string path = "C:\\Users\\Gabriel\\3D Objects\\Hidrant_hightPoly.fbx";
		//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate );

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
		}

		processNode(scene->mRootNode, scene, root);

		return root;
	}

	void processNode(aiNode* node, const aiScene* scene, Entity* root)
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

			meshEntity->setTransform( Transform(
					{aiPosition.x, aiPosition.y, aiPosition.z},
					{aiScale.x, aiScale.y, aiScale.z},
					{aiRotation.x, aiRotation.y, aiRotation.z}
			));

			meshEntity->addComponent<GraphicsComponent>(mesh);
		}

		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, root);
		}
	}
}