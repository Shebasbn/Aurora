#include "arpch.h"

namespace Aurora
{	
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("AURORA");
		s_CoreLogger->set_level(spdlog::level::trace);
		AR_CORE_WARN("Initialized Core Log!");

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
		int a = 5;
		AR_INFO("Initialized Client Log! Var={0}", a);
	}
}