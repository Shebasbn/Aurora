#include "arpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Aurora
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) 
		{ 
			AR_TRACE(e.ToString()); 
		}
		if (e.IsInCategory(EventCategoryInput)) 
		{ 
			AR_TRACE(e.ToString()); 
		}
		while (true)
		{

		}
	}
}
