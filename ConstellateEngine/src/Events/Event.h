#pragma once

#include "cslpch.h"

#include "Core/Core.h"

namespace csl {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

		//Macro for avoiding extra code
		//Good ol reliable macro trick
	#define EVENT_TYPE_FUCTIONS(type) static EventType GetStaticType() {return EventType::type; } \
									  virtual EventType GetEventType() const override { return GetStaticType();  }
								 
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() override { return category; }

	class EngineEvent
	{
	private:
		friend class EventDispatcher;
	protected:
		bool _handled = false;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		

	};


	//Event dispacher scary stuffs
	class EventDispacher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		EngineEvent& _event;

	public:
		EventDispacher(EngineEvent& event) :_event(event) {
			 
		}

		template<typename T>
		bool Dispach(EventFn<T> func) {
			if (_event.GetEventType() == T::GetStaticType()) {
				_event._handled = func(*(T*)&_event);    //to see later
				return true;
			}
			return false;
		}

	};
}