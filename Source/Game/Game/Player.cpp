#include "Player.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "../../Audio/AudioSystem.h"
#include "Weapon.h"
#include "Renderer/ModelManager.h"

void Player::Update(float dt)
{

	//turn
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	//thrust
	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	//wrap
	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_Renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_Renderer.GetWidth());

	//fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};

		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 50, transform, kiko::g_manager.Get("weapon.txt"));
		weapon->m_tag = "playerweapon";
		m_scene->Add(std::move(weapon));

		kiko::g_audiosystem.PlayOneShot("explode");
	}

}

void Player::OnCollision(Actor* actor)
{
	if (actor->m_tag != "playerweapon") {
		m_health -= 1.0f;
		if (m_health <= 0.0f) {
			m_destroyed = true;
		}
	}
}
