#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace csl {
	class Entity;
	class AssetImporter {
	private:
	public:
		static Entity* ModelToEntityHierachy(std::string path, Entity* root);
	};


}