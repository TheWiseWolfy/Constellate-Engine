#pragma once

#include "cslpch.h"

#include "Event.h"

namespace csl {


	class MouseMovedEvent : public EngineEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		const char* GetName() const override {
			return "MouseMovedEvent";
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse)
		EVENT_TYPE_FUCTIONS(MouseMoved)
	private:
		float m_MouseX, m_MouseY;
	};


	class MouseScrolledEvent : public EngineEvent
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_TYPE_FUCTIONS(MouseScrolled)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public EngineEvent
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		const char* GetName() const override {
			return "MouseButtonPressedEvent";
		}

		EVENT_TYPE_FUCTIONS(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		const char* GetName() const override {
			return "MouseButtonReleasedEvent";
		}

		EVENT_TYPE_FUCTIONS(MouseButtonReleased)
	};

}