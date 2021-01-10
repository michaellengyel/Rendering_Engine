//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "State.h"

//============================================================================================================
// Class Trivia
//============================================================================================================

namespace sm {

class StateClearColor : public State {
public:

    StateClearColor();

    ~StateClearColor() override;

    void update(float deltaTime) override;

    void render() override;

    void guiRender() override;

private:

    float m_clearColor[4];

};

} // End namespace sm