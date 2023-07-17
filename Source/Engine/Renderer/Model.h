#pragma once
#include "Core/Core.h"
#include <vector>
#include "Renderer/Renderer.h"

namespace kiko
{
	class Model
	{
	public:
		Model() = default;
		Model(std::vector<vec2> points) : m_points{ points } {}

		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

	private:
		std::vector<vec2> m_points;
	};
}