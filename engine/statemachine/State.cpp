#include "State.h"

#include <imgui/imgui.h>

namespace sm {

StateMenu::StateMenu(State*& currentStatePointer) : m_currentStatePointer(currentStatePointer) {

}

void StateMenu::guiRender() {

    for(auto& state : m_states) {

        if(ImGui::Button(state.first.c_str())) {
            
            m_currentStatePointer = state.second();
        }
    }

}

} // End namespace sm