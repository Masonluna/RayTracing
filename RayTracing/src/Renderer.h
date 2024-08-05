#pragma once

#include "Walnut/Image.h"
#include <memory>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer() = default;
	
	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
	std::shared_ptr<glm::vec3> GetSphereColor() const { return m_SphereColor; }
	std::shared_ptr<glm::vec3> GetLightDir() const { return m_LightDir; }
private:
	glm::vec4 PerPixel(glm::vec2 coord);
public:
private:
	std::shared_ptr<glm::vec3> m_SphereColor = std::make_shared<glm::vec3>(1.0f, 1.0f, 1.0f);
	std::shared_ptr<glm::vec3> m_LightDir = std::make_shared<glm::vec3>(-1.0f, -1.0f, -1.0f);
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;

};