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

		void Draw(Renderer& renderer);

	private:
		std::vector<vec2> m_points;
	};
}