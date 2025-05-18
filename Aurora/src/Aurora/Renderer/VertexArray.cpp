#include "arpch.h"
#include "VertexArray.h"
#include "Aurora/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Aurora
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:   AR_CORE_ASSERT(false, "RendererAPI: None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		AR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
