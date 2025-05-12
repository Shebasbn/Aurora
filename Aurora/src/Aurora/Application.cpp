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
		AR_TRACE(e.ToString());
		while (true)
		{

		}
	}
}
