#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include <chrono>
#include <vector>
#include <thread>
#include "../../../Audio/AudioSystem.h"

using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x > width) {
			m_pos.x = 0;
		}
		if (m_pos.y > height) {
			m_pos.y = 0;
		}
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};


int main(int argc, char* argv[])
{
	auto m1 = kiko::Max(4.0f, 3.0f);
	auto m2 = kiko::Max(4, 3);


	constexpr float a = kiko::DegreesToRadians(180.0f);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");


	kiko::g_Renderer.Initialize();
	kiko::g_Renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audiosystem.Initialize();
	kiko::g_audiosystem.AddAudio("laser", "laser.wav");
	kiko::g_audiosystem.AddAudio("explode", "explosion.wav");

	//std::vector<kiko::vec2> points{{-10, 5}, { 10,5 }, { 0,-5 }, { -10, 5 }};
	kiko::Model model;
	model.Load("ship.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(kiko::g_Renderer.GetWidth()), kiko::random(kiko::g_Renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}



	kiko::vec2 position{500, 400};
	kiko::Transform transform{{400, 300}, 0, 3};
	float speed = 200;
	constexpr float turnRate = kiko::DegreesToRadians(180);

	Player player{ 400, kiko::Pi, { {800, 500}, 0, 6 }, model };

	std::vector<Enemy> enemies;
	for (int i = 0; i < 5; i++) {
		Enemy newEnemy{ 300, kiko::Pi, { {kiko::random(300), kiko::random(300)}, kiko::randomf(kiko::RadiansToDegrees(kiko::TwoPi)), 6}, model};
		enemies.push_back(newEnemy);
	}
	


	//main game loop
	bool quit = false;
	while (!quit)
	{
		//transform.rotation += 1.0f;
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audiosystem.PlayOneShot("explode");
		} 

		// UPDATE///////////////////////////////////
		player.Update(kiko::g_time.GetDeltaTime());
		for (auto& enemy : enemies)enemy.Update(kiko::g_time.GetDeltaTime());

		kiko::g_Renderer.SetColor(0, 0, 0, 0);
		kiko::g_Renderer.BeginFrame();
		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars) {
			star.Update(kiko::g_Renderer.GetWidth(), kiko::g_Renderer.GetHeight());
			kiko::g_Renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_Renderer);
		}

		player.Draw(kiko::g_Renderer);

		for (Enemy enemy : enemies) {
			enemy.Draw(kiko::g_Renderer); 
		}


		kiko::g_Renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}