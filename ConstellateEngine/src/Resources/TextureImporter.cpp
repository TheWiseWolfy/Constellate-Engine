#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "Core/Log.h"

namespace csl {
    unsigned int TextureImporter::loadImageFromFile(const std::string& filePath) {
        int width, height, channels;

        unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (!imageData)
        {
            CSL_CORE_ERROR("Failed to load texture at {0}", filePath);

            return 0;
        }

        // Create an OpenGL texture and upload the image data
        unsigned int textureId = 0; // Initialize the texture ID

        // Generate texture and bind it
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Set texture parameters (adjust as needed)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload the image data to the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        // Generate mipmaps if desired
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the loaded image data
        stbi_image_free(imageData);

        return textureId;
    }
}