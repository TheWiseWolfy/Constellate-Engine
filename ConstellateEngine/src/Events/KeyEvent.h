#pragma once

#include "cslpch.h"

#include "Event.h"

namespace csl {


	class KeyEvent : public EngineEvent {
	protected:
		int _keyCode; 
		int GetKeyCOde() { return _keyCode; }
	public:
		KeyEvent(int keycode) : _keyCode(keycode) {}

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
	
}