#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
using namespace std;



//void func()
//{
//	int* p = new int[1000000];
//}

int main(int argc, char* argv[])
{
	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196-Game",800,600);

	while (true) {
		renderer.SetColor(0, 0, 0, 255);
		renderer.BeginFrame();
		//draw
		for (int i = 0; i < 9999; i++) {
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		}
		renderer.EndFrame();
	}

	return 0;
}