#pragma once

#include "Core.h"

namespace Aurora 
{
	class AURORA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be Defined in client
	Application* CreateApplication();
}

