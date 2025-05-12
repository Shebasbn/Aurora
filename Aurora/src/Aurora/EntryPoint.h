#pragma once

#ifdef AR_PLATFORM_WINDOWS

extern Aurora::Application* Aurora::CreateApplication(); 

int main(int argc, char** argv)
{
	Aurora::Log::Init();
	AR_CORE_WARN("Initialized Core Log!");
	int a = 5;
	AR_INFO("Initialized Client Log! Var={0}", a);

	auto app = Aurora::CreateApplication();
	app->Run(); 
	delete app;
}

#endif