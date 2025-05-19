#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Core/Timestep.h"

namespace Aurora
{
	class AURORA_API Layer
	{
	public:
		Layer(std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}
