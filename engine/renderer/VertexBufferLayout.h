//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include <vector>
#include <GL/glew.h>

//============================================================================================================
// Class Trivia
//============================================================================================================

struct VertexBufferElement {

    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(unsigned int type) {

        switch(type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
        }
        return 0;
    }

};

class VertexBufferLayout {

public:

    VertexBufferLayout() : mStride(0) {

    }

    template<typename T>
    inline void push(unsigned int count) {
        // static_assert(false) // TODO: fix assert to work on linux
    }

    inline const std::vector<VertexBufferElement>& getElements() const {
        return mElements;
    }

    inline unsigned int getStride() const {
        return mStride;
    }

private:

    std::vector<VertexBufferElement> mElements;
    unsigned int mStride;

};

template<>
inline void VertexBufferLayout::push<float>(unsigned int count) {
    mElements.push_back({GL_FLOAT, count, GL_FALSE});
    mStride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    mStride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    mStride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}