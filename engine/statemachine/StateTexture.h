//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include "State.h"

//============================================================================================================
// Class Trivia
//============================================================================================================

namespace sm {

class StateTexture : public State {
public:

    StateTexture();

    ~StateTexture() override;

    void update(float deltaTime) override;

    void render() override;

    void guiRender() override;

private:

};

} // End namespace sm