#include "StateTexture.h"

#include <GL/glew.h>
#include <imgui/imgui.h>

namespace sm {

StateTexture::StateTexture() {

}

StateTexture::~StateTexture() {

}

void StateTexture::update(float deltaTime) {

}

void StateTexture::render() {

    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void StateTexture::guiRender() {

    ImGui::ColorEdit4("Clear Color", m_clearColor);
}

} // End namespace sm