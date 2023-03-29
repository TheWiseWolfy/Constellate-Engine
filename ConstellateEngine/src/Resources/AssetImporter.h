#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

namespace csl {

	static class AssetImporter {

		//static void weDoingThisBoys() {
		//	Assimp::Importer importer;
		//	std::string path = "C:\\Users\\Gabriel\\3D Objects\\Hidrant_hightPoly.fbx";

		//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);


		//}

  //      void processNode(aiNode* node, const aiScene* scene)
  //      {
  //          // process all the node's meshes (if any)
  //          for (unsigned int i = 0; i < node->mNumMeshes; i++)
  //          {
  //              aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
  //              meshes.push_back(processMesh(mesh, scene));
  //          }
  //          // then do the same for each of its children
  //          for (unsigned int i = 0; i < node->mNumChildren; i++)
  //          {
  //              processNode(node->mChildren[i], scene);
  //          }
  //      }
	};


}