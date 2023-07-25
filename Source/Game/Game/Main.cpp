#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Font.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include <chrono>
#include <vector>
#include <thread>
#include "../../../Audio/AudioSystem.h"
#include <Framework/Scene.h>
#include <Renderer/Text.h>

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

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::g_Renderer.Initialize();
	kiko::g_Renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audiosystem.Initialize();
	kiko::g_audiosystem.AddAudio("laser", "laser.wav");
	kiko::g_audiosystem.AddAudio("explode", "explosion.wav");

	kiko::Font fontsystem;

	// create font / text objects
	std::shared_ptr<kiko::Font> font = std::make_shared<kiko::Font>("Impact Label.ttf", 24);

	std::unique_ptr<kiko::Text> text = std::make_unique<kiko::Text>(font);
	text->Create(kiko::g_Renderer, "NEUMONT", kiko::Color{ 1, 1, 1, 1 });

	//kiko::Model model;
	//model.Load("ship.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(kiko::g_Renderer.GetWidth()), kiko::random(kiko::g_Renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	//adding entities
	kiko::Scene scene;;
	//player
	unique_ptr<Player> player = make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
	player->m_tag = "player";
	scene.Add(std::move(player));
	//enemies
	for (int i = 0; i < 1; i++) {
		unique_ptr<Enemy> enemy = make_unique<Enemy>(kiko::random(50, 150), kiko::Pi, kiko::Transform{ {kiko::random(300), kiko::random(300)}, kiko::randomf(kiko::RadiansToDegrees(kiko::TwoPi)), 6 }, kiko::g_manager.Get("enemy.txt"));
		enemy->m_tag = "enemy";
		scene.Add(std::move(enemy));
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{

		//Engine Update
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		

		// update
		scene.Update(kiko::g_time.GetDeltaTime());

		kiko::g_Renderer.SetColor(0, 0, 0, 0);
		kiko::g_Renderer.BeginFrame();
		
		kiko::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars) {
			star.Update(kiko::g_Renderer.GetWidth(), kiko::g_Renderer.GetHeight());
			kiko::g_Renderer.SetColor(255,255,255,255);
			star.Draw(kiko::g_Renderer);
		}

		//Draw
		scene.Draw(kiko::g_Renderer);
		text->Draw(kiko::g_Renderer, 400, 300);

		kiko::g_Renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}