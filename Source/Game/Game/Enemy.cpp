#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "../../Audio/AudioSystem.h"

void Enemy::Update(float dt)
{

	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
	}

	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_Renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_Renderer.GetHeight());

	if(m_fireTimer <= 0){
		m_fireTimer = m_fireRate;

		kiko::Transform transform{ m_transform.position, m_transform.rotation, .5};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(50, transform, kiko::g_manager.Get("weapon.txt"));
		weapon->m_tag = "enemyweapon";
		m_scene->Add(std::move(weapon));
		kiko::g_audiosystem.PlayOneShot("explode");
	}
	else {
		m_fireTimer -= kiko::g_time.GetDeltaTime();
	}
	

}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->m_tag != "enemyweapon") {
		m_destroyed = true;
	}
}
