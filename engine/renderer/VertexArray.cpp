#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray() {

    glGenVertexArrays(1, &mRendererId);
}

VertexArray::~VertexArray() {
    
    glDeleteVertexArrays(1, &mRendererId);
}

void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout) {

    // Bind vertex array
    bind();

    // Bind vertex buffer
    vertexBuffer.bind();

    // Setup buffer layout
    const auto& elements = vertexBufferLayout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, vertexBufferLayout.getStride(), (const void*)offset); // Links buffer with vao
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }

}

void VertexArray::bind() const {

    glBindVertexArray(mRendererId);
}

void VertexArray::unBind() const {

    glBindVertexArray(0);
}