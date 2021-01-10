#include "StateTexture.h"

#include <GL/glew.h>
#include <imgui/imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../renderer/Renderer.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include "../renderer/Shader.h"
#include "../renderer/VertexBufferLayout.h"
#include "../renderer/Texture.h"

namespace sm {

// Vertex data (buffer)
float m_positions[16] = {
    100.0f, 100.0f, 0.0f, 0.0f, // 0
    200.0f, 100.0f, 1.0f, 0.0f, // 1
    200.0f, 200.0f, 1.0f, 1.0f, // 2
    100.0f, 200.0f, 0.0f, 1.0f  // 3
};

// Index buffer
unsigned int m_indices[6] = {
    0, 1, 2,
    2, 3, 0
};

StateTexture::StateTexture() :  m_indexBuffer(m_indices, 6),
                                m_shader("../engine/res/shaders/texture.sh"),
                                m_texture("../engine/res/images/gray.png"),
                                m_vertexBuffer(m_positions, 4 * 4 * sizeof(float)),
                                m_projection(glm::ortho(0.0f, 940.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                                m_view(glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0))),
                                m_model(glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0))),
                                m_translationX(0.0f, 0.0f, 0.0f),
                                m_translationY(100.0f, 100.0f, 0.0f)
                                {

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(2); // First 2 floats of vertex
    vertexBufferLayout.push<float>(2); // Second 2 floats of vertex
    m_vertexArray.addBuffer(m_vertexBuffer, vertexBufferLayout);

    m_shader.bind();

    m_modelViewProjection = m_projection * m_view * m_model;

    // Saving location of uniforms from shader
    m_shader.setUniform4f("u_Color", 0.8f, 0.0f, 0.5f, 1.0f);
    m_shader.setUniformMat4f("u_ModelViewProjection", m_modelViewProjection);
    m_shader.setUniform1i("u_Texture", 0); // 0 stands for slot 0

    // Unbinding all buffers (rebind them before draw all)
    m_vertexArray.unBind();
    m_vertexBuffer.unbind();
    m_indexBuffer.unbind();
    m_shader.unBind();

}

StateTexture::~StateTexture() {

}

void StateTexture::update(float deltaTime) {

    // Animate stuff here
}

void StateTexture::render() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Instantiate renderer
    Renderer renderer;

    // Adding textures
    m_texture.bind();

    // Implementing Projection Matrix (counteract window distortion (only needs to be set once))
    m_projection = glm::ortho(0.0f, 940.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    // Implementing View Matrix
    m_view = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));

    // Rendering object 1
    {
        // Implementing Model Matrix
        m_model = glm::translate(glm::mat4(1.0f), m_translationX);
        // Calculating Model View Projection Matrix
        m_modelViewProjection = m_projection * m_view * m_model;
        // Saving location of uniforms from shader
        m_shader.bind();
        m_shader.setUniformMat4f("u_ModelViewProjection", m_modelViewProjection);
        renderer.draw(m_vertexArray, m_indexBuffer, m_shader);
    }

    // Rendering object 2
    {
        // Implementing Model Matrix
        m_model = glm::translate(glm::mat4(1.0f), m_translationY);
        // Calculating Model View Projection Matrix
        m_modelViewProjection = m_projection * m_view * m_model;
        // Saving location of uniforms from shader
        m_shader.bind();
        m_shader.setUniformMat4f("u_ModelViewProjection", m_modelViewProjection);
        renderer.draw(m_vertexArray, m_indexBuffer, m_shader);
    }

}

void StateTexture::guiRender() {

    ImGui::SliderFloat3("Translation X", &m_translationX.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Translation Y", &m_translationY.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // End namespace sm