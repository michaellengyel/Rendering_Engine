#include "Renderer.h"

#include <GL/glew.h>

void Renderer::clear() const {

    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {

    shader.bind();      // Set shader
    vertexArray.bind(); // Set vertex array
    indexBuffer.bind(); // Bind index buffer

    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}