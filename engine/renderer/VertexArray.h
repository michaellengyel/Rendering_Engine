//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "VertexBufferLayout.h"


//============================================================================================================
// Class Trivia
//============================================================================================================

class VertexArray {
public:

    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);

    void bind() const;
    void unBind() const;

private:

    unsigned int mRendererId;

};