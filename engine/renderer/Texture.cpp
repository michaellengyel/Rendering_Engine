#include "Texture.h"

#include "../vendor/stb_image/stb_image.h"

#include <GL/glew.h>

Texture::Texture(const std::string& filePath)
    : mRendererId(0), mFilePath(filePath), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBitPerPixel(0) {
    
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mBitPerPixel, 4);

    glGenTextures(1, &mRendererId);
    glBindTexture(GL_TEXTURE_2D, mRendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(mLocalBuffer) {
        stbi_image_free(mLocalBuffer);
    }
}

Texture::~Texture() {

    glDeleteTextures(1, &mRendererId);
}

void Texture::bind(unsigned int slot) const {

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mRendererId);
}

void Texture::unBind() const {

    glBindTexture(GL_TEXTURE_2D, 0);
}