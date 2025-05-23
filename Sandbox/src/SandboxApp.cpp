#include <Aurora.h>

#include "imgui/imgui.h"
class ExampleLayer : public Aurora::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(Aurora::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Aurora::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Aurora::VertexBuffer::Create(vertices, sizeof(vertices)));

		Aurora::BufferLayout layout = {
			{ Aurora::ShaderDataType::Float3, "a_Position" },
			{ Aurora::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Aurora::IndexBuffer> indexBuffer;
		indexBuffer.reset(Aurora::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Aurora::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f,  0.0f,
			 0.75f, -0.75f,  0.0f,
			 0.75f,  0.75f,  0.0f,
			-0.75f,  0.75f,  0.0f
		};

		std::shared_ptr<Aurora::VertexBuffer> squareVB;
		squareVB.reset(Aurora::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Aurora::BufferLayout squareLayout = {
			{ Aurora::ShaderDataType::Float3, "a_Position" }
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Aurora::IndexBuffer> squareIB;
		squareIB.reset(Aurora::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Aurora::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Aurora::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	virtual void OnUpdate(Aurora::Timestep ts) override
	{
		AR_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Aurora::Input::IsKeyPressed(AR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		
		else if (Aurora::Input::IsKeyPressed(AR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Aurora::Input::IsKeyPressed(AR_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		
		else if (Aurora::Input::IsKeyPressed(AR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Aurora::Input::IsKeyPressed(AR_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Aurora::Input::IsKeyPressed(AR_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Aurora::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Aurora::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Aurora::Renderer::BeginScene(m_Camera);

		Aurora::Renderer::Submit(m_BlueShader, m_SquareVA);
		Aurora::Renderer::Submit(m_Shader, m_VertexArray);

		Aurora::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Aurora::Event& e) override
	{
	}
private:
	std::shared_ptr<Aurora::VertexArray> m_VertexArray;
	std::shared_ptr<Aurora::Shader> m_Shader;

	std::shared_ptr<Aurora::Shader> m_BlueShader;
	std::shared_ptr<Aurora::VertexArray> m_SquareVA;

	Aurora::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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