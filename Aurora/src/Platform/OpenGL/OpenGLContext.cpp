#include "arpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Aurora
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		AR_CORE_ASSERT(windowHandle, "Handle is null!");
	}
	void OpenGLContext::Init()
	{
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AR_CORE_ASSERT(status, "Failed to initialize Glad!");

		AR_CORE_INFO("OpenGL Info:");
		AR_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		AR_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		AR_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}