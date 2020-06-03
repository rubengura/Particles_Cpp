#include <iostream>
#include "SDL.h"
#include <cmath>
#include "Screen.h"
#include "Swarm.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace particle;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Screen screen;
	if (screen.init() == false)
	{
		cout << "Error initializing screen." << endl;
	}
	
	Swarm swarm;

	while (true)
	{
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char green = (unsigned char)((1 + cos(elapsed * 0.0001) * 128));
		unsigned char red = (unsigned char)((1 + cos(elapsed * 0.0001) * 128));
		unsigned char blue = (unsigned char)((1 + cos(elapsed * 0.0001) * 128));

		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		screen.update();

		if (screen.processEvents() == false)
		{
			break;
		}
	}
	
	screen.close();

	return 0;
}