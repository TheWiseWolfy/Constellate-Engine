/*
File: Event.h

TODO: Implement propper key pooling in order to capture key presses sincroniusly

The base even for all the events in CSL Engine. 

Credit for the dispach fuction and clever macros: https://github.com/TheCherno/Hazel
*/


#pragma once

#include "cslpch.h"
#include "Core/Core.h"

namespace csl {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		CustomEvent1, CustomEvent2, CustomEvent3, CustomEvent4, CustomEvent5
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		EventCategoryCustom1 = BIT(5)
	};

	//Macro for avoiding extra code
	//_______________________________________________________
	#define EVENT_TYPE_FUCTIONS(type) static EventType GetStaticType() {return EventType::type; } \
									  virtual EventType GetEventType() const override { return GetStaticType();  }\
	//_______________________________________________________

								 
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

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
		
		virtual bool IsHandled() const { return _handled; }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		//An event dispacher is created to handle the generic engine event 
		EngineEvent& _event;

	public:
		//A dispacher is created every single time an event is being handled.
		EventDispatcher(EngineEvent& event) :_event(event) {
			 
		}

		//We compare:
		//the event type of the event that created the dispacher in the first place
		//the event type required by a specific call of Dispach (Ex: Dispach<WindowsCloseEvent>( std::bind(callbackForWindowClose) )
		template<typename T>
		bool Dispach(EventFn<T> func) {
			if (_event.GetEventType() == T::GetStaticType()) {
				//_event._handled = func(*(T*)   &_event);    //to see later
				_event._handled = func( *static_cast<T*>(& _event) );    

				return true;
			}
			return false;
		}

	};
}