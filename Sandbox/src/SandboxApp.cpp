#include <Aurora.h>

#include "imgui/imgui.h"
class ExampleLayer : public Aurora::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//AR_INFO("ExampleLayer::Update");

		if (Aurora::Input::IsKeyPressed(AR_KEY_TAB))
		{
			AR_INFO("Tab key is pressed!");
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Aurora::Event& e) override
	{
		//AR_TRACE("{0}", e.ToString());
	}
};

class Sandbox : public Aurora::Application 
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{

	}
};

Aurora::Application* Aurora::CreateApplication()
{
	return new Sandbox();
}