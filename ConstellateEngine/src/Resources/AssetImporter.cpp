#include "AssetImporter.h"
#include "cslpch.h"

#include "Entity-Component/Entity.h"
#include "Entity-Component/Components/GraphicsComponent.h"


namespace csl {
	void processNode(aiNode* node, const aiScene* scene, Entity* root);


	Entity* AssetImporter::ModelToEntityHierachy(std::string path) {
		Assimp::Importer importer;
		//std::string path = "C:\\Users\\Gabriel\\3D Objects\\Hidrant_hightPoly.fbx";
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
		}
		//directory = path.substr(0, path.find_last_of('/'));

		Entity* root = new Entity();
		processNode(scene->mRootNode, scene, root);

		return root;
	}

	void processNode(aiNode* node, const aiScene* scene, Entity* root)
	{
		//This will be the root of out new mesh object

		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			//Here we do the magic bit
			Entity* meshEntity = root->addEntity();
			meshEntity->addComponent<GraphicsComponent>(mesh);

			//meshes.push_back(processMesh(mesh, scene));
		}

		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, root);
		}
	}
}