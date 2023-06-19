/*
File: ImputManager.h

This is a input manager singleton that makes it easy to read input from anywhere in the codebase.

Reference: https://github.dev/TheCherno/Hazel/tree/9b75670ced984969806658a736c0709801ee3f1d
*/


#pragma once

#include "cslpch.h"
#include "KeyCodes.h"


namespace csl {

    class InputManager {
    private:
        static InputManager* instance;

        InputManager() {}
    public:
        static InputManager* getInstance() {
            if (!instance) {
                instance = new InputManager(); 
            }
            return instance;
        }

        bool isKeyPressed(int keyCode);

    protected:
       // virtual bool isKeyPressedImpl(int keyCode) = 0;
    };


}