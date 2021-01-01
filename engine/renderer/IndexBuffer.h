//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "Renderer.h"

//============================================================================================================
// Class Trivia
//============================================================================================================

class IndexBuffer {

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int mRendererId;
    unsigned int mCount;
};