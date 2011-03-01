Agent::Agent() {
	x = 0;
	y = 0;
	width = 10; // Todo: make these realistic default values
	height = 10;

	active = false;
}

Agent::Agent(int newx, int newy, int newwidth, int newheight) {
	x = newx;
	y = newy;

	width = newwidth;
	height = newheight;

	active = false;
}

int Agent::fitness() {
	return Search::getInstance().fitness(x, y, width, height);
}

void Agent::update_state() {
	int percentage = fitness();

	//if(percentage <= Agents::getInstance().get_best_percentage()) {
	if(percentage < 15) {
		Agents::getInstance().new_percentage(percentage);
		active = true;

		if(rand() % 10 == 0) {
			active = false;
		}
	}
	else {
		active = false;
	}
}

void Agent::update() {
	if(active == true) {
		if(rand() % 10 == 0) {
			move_vicinity();
		}
	}
	else {
		Agent random_agent = Agents::getInstance().random_agent();

		if(random_agent.is_active()) {
			x = random_agent.get_x();
			y = random_agent.get_y();
		}
		else {
			if(rand() % 2 == 0) {
				randomize();
			}
			else {
				move_vicinity();
			}
		}
	}
}

void Agent::randomize() {
	x = rand() % Search::getInstance().haystack_width();
	y = rand() % Search::getInstance().haystack_height();
}

void Agent::move_vicinity() {
	x  += (rand() % 21) - 10;
	y += (rand() % 21) - 10;
}

void Agent::draw() {
	int color = SDL_MapRGB(SDL::getInstance().screen->format, 255, 0, 0);
	if(active == true) {
		color = SDL_MapRGB(SDL::getInstance().screen->format, 0, 255, 0);
	}

	// Draw in the fitness percentage
	SDL_Color textColor = { 255, 255, 255};
	SDL_Surface *text = TTF_RenderText_Solid(SDL::getInstance().font, intToString(fitness()), textColor);

	SDL::getInstance().applySurface(text, BORDER_X + (x * PIXEL_SIZE), (BORDER_Y) + (y * PIXEL_SIZE));

	SDL::getInstance().drawRect(BORDER_X + (x * PIXEL_SIZE), BORDER_Y + (y * PIXEL_SIZE), width * PIXEL_SIZE, height * PIXEL_SIZE, 1, color);
}

bool Agent::is_active() {
	return active;
}

int Agent::get_x() {
	return x;
}

int Agent::get_y() {
	return y;
}
