#pragma once

#include "cslpch.h"
#include "Renderer/Shader.h"

namespace csl {

    class ShaderLoader {
    private:
        //Here we are forced to use move semantics because we are representing an shared resouce and we must never call the contructor (also owned by openGL)
        std::map<std::string, std::unique_ptr<Shader>> _shaderMap;

        ShaderLoader() {}

    public:
        static ShaderLoader& getInstance() {
            static ShaderLoader instance;
            return instance;
        }

        void loadShader(std::string name, std::string vertexPathString, std::string fragmentPathString) {

            std::filesystem::path fragmenPath(fragmentPathString);
            std::filesystem::path vertexPath(vertexPathString);

            if (!std::filesystem::exists(fragmentPathString) || !std::filesystem::exists(vertexPathString) ) {
                throw std::runtime_error("The shader files were not found.");
            }

            std::ifstream fileStreamVertex(vertexPath);
            std::ifstream fileStreamFragment(fragmenPath);
            
            if (!fileStreamFragment.is_open() || !fileStreamVertex.is_open())
            {
                throw std::runtime_error("Failed to open file fragment shader or vertex shader file.");
            }

            std::string vertexSource;
            std::string fragmentSource;

            std::string line;
            while (std::getline(fileStreamVertex, line))
            {
                vertexSource += line + '\n';
            }

            while (std::getline(fileStreamFragment, line))
            {
                fragmentSource += line + '\n';
            }

            _shaderMap.emplace(name, std::make_unique<Shader>(vertexSource, fragmentSource));
        }

        Shader& getShader(const std::string& name) {
            try {
                return *_shaderMap.at(name);
            }
            catch (const std::out_of_range& e) {
                throw std::runtime_error("Shader not found: " + name);
            }
        }

        ShaderLoader(const ShaderLoader&) = delete;
        ShaderLoader& operator=(const ShaderLoader&) = delete;
    };


}