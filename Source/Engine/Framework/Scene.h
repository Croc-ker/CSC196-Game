#pragma once
#include <list>
#include "Actor.h"
namespace kiko
{

	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();


		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};


	template<typename T>
	T* Scene::GetActor()
	{
		for (const auto& actor : m_actors)
		{
			if (typeid(*actor) == typeid(T))
			{
				return static_cast<T*>(actor.get());
			}
		}
		return nullptr;
	}
}