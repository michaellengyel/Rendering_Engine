#include "StateClearColor.h"

#include <GL/glew.h>
#include <imgui/imgui.h>

namespace sm {

StateClearColor::StateClearColor() : m_clearColor{ 0.2f, 0.4f, 0.9f, 1.0f } {

}

StateClearColor::~StateClearColor() {

}

void StateClearColor::update(float deltaTime) {

    // Animate stuff here
}

void StateClearColor::render() {

    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void StateClearColor::guiRender() {

    ImGui::ColorEdit4("Clear Color", m_clearColor);
}

} // End namespace sm