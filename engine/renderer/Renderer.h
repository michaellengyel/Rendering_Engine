//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//============================================================================================================
// Class Trivia
//============================================================================================================

class Renderer {
public:

    void clear() const;

    void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;

};