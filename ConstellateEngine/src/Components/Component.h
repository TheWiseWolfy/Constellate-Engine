#pragma once



class Component
{
private:
    bool alive = true;

public:
    virtual void init() {}
    virtual void update(float mFT) {}
    virtual void draw() {}
};


