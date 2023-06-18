/*
File:KeyEvent.h

This file contains EngineEvents meant to deal with keyboard presses. Those events are created by the Windows class (at time of
writing taken directly as is from a GLFW callback fuction).



Relevant documentation:
Keyboard keys: https://www.glfw.org/docs/3.3/group__keys.html

*/
#pragma once

#include "cslpch.h"

#include "KeyCodes.h"
#include "Event.h"

namespace csl {

	class KeyEvent : public EngineEvent {
	protected:
		int _keyCode; //For now the key codes are taken from GLFW as is.
	public:
		int GetKeyCode() { return _keyCode; }

		KeyEvent(int keycode) : _keyCode(keycode) {}

		const char* GetName() const override {
			return "KeyEvent";
		}
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard || EventCategoryInput)
	};

	class KeyPressedEvent : public KeyEvent{
	private:
		int _repeatCount;
	public:

		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {
		}

		std::string ToString()  const override {
			std::stringstream sstream;
			sstream << "We pressed key " << _keyCode << "(" << _repeatCount << "repeats)";
			return sstream.str();
		}

		EVENT_TYPE_FUCTIONS(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent {
	private:

	public:

		KeyReleasedEvent(int keycode, int repeatCount) : KeyEvent(keycode) {
		}

		std::string ToString()  const override {
			std::stringstream sstream;
			sstream << "We reseased key" << _keyCode;
			return sstream.str();
		}

		EVENT_TYPE_FUCTIONS(KeyPressed)
	};
	
	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << _keyCode;
			return ss.str();
		}

		EVENT_TYPE_FUCTIONS(KeyTyped)
	};

}