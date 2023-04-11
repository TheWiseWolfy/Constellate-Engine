#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace csl {
	class Entity;
	class AssetImporter {
	private:
	public:

		static const aiScene* LoadModel(std::string path) {

			//This is what they call a pro
			static Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
			}

			return scene;
		};
	};


}