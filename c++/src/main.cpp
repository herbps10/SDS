#include <string>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "CImg.h"

#include "mpi.h"

using namespace cimg_library;
using namespace std;

#include "config.h"

#include "main.h"
#include "sdl.h"
#include "image.h"
#include "search.h"
#include "agent.h"
#include "agents.h"

#include "sdl.cc"
#include "image.cc"
#include "search.cc"
#include "agent.cc"
#include "agents.cc"

bool quitEvent() {
	bool quit = false;

	SDL_Event event;
	SDL_PollEvent(&event);

	if(event.type == SDL_QUIT) {
		quit = true;
	}
	else if(event.type == SDL_KEYDOWN) {
		char keyName = event.key.keysym.sym;
		if(keyName == 'q' || keyName == 'Q') {
			quit = true;
		}
	}

	return quit;
}

void sds() {
	// Initialize the agents
	for(int i = 0; i < NUM_AGENTS; i++) {
		Agent* a = new Agent(0, 0, Search::getInstance().needle_width(), Search::getInstance().needle_height());
		a->randomize();

		Agents::getInstance().add(i, *a);
	}

	int frame = 0;
	while(quitEvent() == false) {
		SDL_FillRect(SDL::getInstance().screen, NULL, SDL_MapRGB(SDL::getInstance().screen->format, 0, 0, 0));

		Search::getInstance().draw();

		Agents::getInstance().update_state();

		if(quitEvent() == true) break;

		Agents::getInstance().update();

		if(quitEvent() == true) break;

		Agents::getInstance().draw();

		if(quitEvent() == true) break;

		SDL::getInstance().update();

		frame++;
	}
}

int main(int argc, char* args[]) {
	srand(time(NULL));

	SDL::getInstance().init();

	Search::getInstance().init("/home/herb/git/SDS/images/people.png", "/home/herb/git/SDS/images/nick.png");

	Agents::getInstance().init();

	sds();

	/*
	Search::getInstance().draw();

	Agent* a = new Agent(160, 20, Search::getInstance().needle_width(), Search::getInstance().needle_height());
	cout << a->fitness() << endl;
	a->draw();

	cout << endl << endl;

	Agent* a2 = new Agent(490, 130, Search::getInstance().needle_width(), Search::getInstance().needle_height());
	cout << a2->fitness() << endl;
	a2->draw();

	cout << endl << endl;

	Agent* a3 = new Agent(800, 50, Search::getInstance().needle_width(), Search::getInstance().needle_height());
	cout << a3->fitness() << endl;
	a3->draw();

	SDL::getInstance().update();

	while(quitEvent() == false);
	*/

	SDL::getInstance().quit();

	return 0;
}

const char* intToString(int i) {
	stringstream out;
	out << i;
	return out.str().c_str();
}
