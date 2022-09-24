#pragma once

#include "cslpch.h"

#include "Event.h"


namespace csl {
	class WindowResizeEvent : public EngineEvent {
	private:
		unsigned int _width, _height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {}

		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }

		const char* GetName() const override {
			return "WindowResizeEvent";
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}


		EVENT_TYPE_FUCTIONS(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	


	class WindowCloseEvent : public EngineEvent
	{
	public:
		WindowCloseEvent() = default;

		const char* GetName() const override {
			return "WindowCloseEvent";
		}

		EVENT_TYPE_FUCTIONS(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


}