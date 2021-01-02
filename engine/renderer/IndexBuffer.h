//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

//============================================================================================================
// Class Trivia
//============================================================================================================

class IndexBuffer {

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getCount() const;

private:
    unsigned int mRendererId;
    unsigned int mCount;
};