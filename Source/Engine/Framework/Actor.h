#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Core/Memory.h"
namespace kiko
{
    class Actor
    {
    public:
        Actor() = default;
        Actor(const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
            m_transform{ transform },
            m_model{ model }
        {}

        virtual void Update(float dt);

        virtual void Draw(kiko::Renderer& renderer);

        float GetRadius() { return m_model->GetRadius() * m_transform.scale; }
        virtual void OnCollision(Actor* other) {};

        class Scene* m_scene = nullptr;
        friend class Scene;

        kiko::Transform m_transform;
        std::string m_tag;
        
    protected:
        bool m_destroyed = false;
        float m_lifespan = -1.0f;

        std::shared_ptr<Model> m_model;
    };
}