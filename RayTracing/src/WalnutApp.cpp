#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"
#include "Renderer.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last Render: %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render")) {
			Render();
		}

		auto sphereColor = m_Renderer.GetSphereColor();
		if (sphereColor)
		{
			ImGui::SliderFloat("Red", &sphereColor->r, 0.0f, 1.0f, "%.2f", 0);
			ImGui::SliderFloat("Green", &sphereColor->g, 0.0f, 1.0f, "%.2f", 0);
			ImGui::SliderFloat("Blue", &sphereColor->b, 0.0f, 1.0f, "%.2f", 0);
		}

		auto lightDir = m_Renderer.GetLightDir();
		if (lightDir)
		{
			ImGui::SliderFloat("Light X", &lightDir->x, -1.0f, 1.0f, "%.2f", 0);
			ImGui::SliderFloat("Light Y", &lightDir->y, -1.0f, 1.0f, "%.2f", 0);
			ImGui::SliderFloat("Light Z", &lightDir->z, -1.0f, 1.0f, "%.2f", 0);
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		auto image = m_Renderer.GetFinalImage();
		if (image) {
			ImGui::Image(image->GetDescriptorSet(), {(float)image->GetWidth(), (float)image->GetHeight()},
				ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		Timer timer;

		// Renderer resize;
		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		// Renderer render;
		m_Renderer.Render();

		m_LastRenderTime = timer.ElapsedMillis();
	}

private:
	Renderer m_Renderer;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	float m_LastRenderTime = 0.0f;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}