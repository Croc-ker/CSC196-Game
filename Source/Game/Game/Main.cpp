#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
using namespace std;


int main()
{

	cout << kiko::getFilePath() << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(10, 20) << endl;
	}
}