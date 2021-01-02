//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include <string>

//============================================================================================================
// Class Trivia
//============================================================================================================

class Texture {
public:

    Texture(const std::string& filePath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unBind() const;

    inline int getWidth() const {
        return mWidth;
    }

    inline int getHeight() const {
        return mHeight;
    }

private:

    unsigned int mRendererId;
    std::string mFilePath;
    unsigned char* mLocalBuffer;
    int mWidth, mHeight, mBitPerPixel;

};