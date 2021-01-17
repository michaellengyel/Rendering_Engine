//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "State.h"

#include "../renderer/VertexBufferLayout.h"
#include "../renderer/Texture.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/VertexArray.h"
#include "../renderer/Shader.h"
#include "../renderer/IndexBuffer.h"

//============================================================================================================
// Class Trivia
//============================================================================================================

namespace sm {

class StateBatchRender : public State {
public:

    StateBatchRender();

    ~StateBatchRender() override;

    void update(float deltaTime) override;

    void render() override;

    void guiRender() override;

private:

    VertexArray m_vertexArray;
    IndexBuffer m_indexBuffer;
    Shader m_shader;
    Texture m_texture;
    VertexBuffer m_vertexBuffer;


    /// Implementing Projection Matrix (counteract window distortion (only needs to be set once))
    glm::mat4 m_projection;
    // Implementing View Matrix
    glm::mat4 m_view;
    // Implementing Model Matrix
    glm::mat4 m_model;
    // Calculating Model View Projection Matrix
    glm::mat4 m_modelViewProjection;

    glm::vec3 m_translationX;
    glm::vec3 m_translationY;

};

} // End namespace sm