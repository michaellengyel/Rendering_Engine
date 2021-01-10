//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

//============================================================================================================
// Class Trivia
//============================================================================================================

namespace sm {

class State {
public:

    State() {}

    virtual ~State() {}

    virtual void update(float deltaTime) {};

    virtual void render() {};

    virtual void guiRender() {};

};

class StateMenu : public State {
public:

    StateMenu(State*& currentStatePointer);

    void guiRender() override;

    template<typename T>
    void addState(const std::string& name) {
         
        std::cout << "Adding State: " << name << std::endl;
        
        m_states.push_back(std::make_pair(name, []() { return new T(); }));
    }

private:

    State*& m_currentStatePointer;
    std::vector<std::pair<std::string, std::function<State*()>>> m_states;

};

} // End namespace sm