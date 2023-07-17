#include "Actor.h"

void Actor::Update(float dt)
{
}

void Actor::Draw(kiko::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform.position, m_transform.rotation, m_transform.scale);

}
