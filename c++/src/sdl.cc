SDL SDL::instance;

SDL &SDL::getInstance() {
	return instance;
}

/*
 * Initialize SDL and the main surface. The surface will either be full screen or a specific size depending on the settings in the configuration file.
 */
void SDL::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	if(FULLSCREEN == true) {
		screen = SDL_SetVideoMode(0, 0, 32, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_FULLSCREEN);

		// Retrieve the size of the screen
		const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
		SCREEN_WIDTH = videoInfo->current_w;
		SCREEN_HEIGHT = videoInfo->current_h;
	}
	else {
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_ANYFORMAT | SDL_HWSURFACE);
	}

	if(screen == NULL) {
		cout << "Error initializing the screen" << endl;;
	}

	// Initialize SDL_TTF
	if(TTF_Init() == -1) {
		cout << "Error initializing SDL_TTF" << endl;
	}
	
	SDL_WM_SetCaption("Stochastic Diffusion Search", NULL);

	font = TTF_OpenFont("../Existence-Light.ttf", 20);

	SDL_Flip(screen);
}

/*
 * Draw a pixel of a given RGB color on the main SDL screen
 * This function maps the rgb values to an SDL formatted integer and passes it to the other version of the drawPixel function.
 */
void SDL::drawPixel(int x, int y, int r, int g, int b) {
	drawPixel(x, y, SDL_MapRGB(SDL::getInstance().screen->format, r, g, b));
}

/*
 * Draw a colormapped pixel to the main SDL screen
 *
 * int color - SDL colormapped color
 */
void SDL::drawPixel(int x, int y, int color) {
	int *p = (int *)SDL::getInstance().screen->pixels + y * SDL::getInstance().screen->pitch/4 + x;
	*p = color; // If you get a segmentation fault here, it is probably because you are trying to write to out of bound coordinates.
}

void SDL::drawFilledRect(int x, int y, int w, int h, int color) {
	SDL_Rect pixel;
	pixel.x = x;
	pixel.y = y;
	pixel.w = w;
	pixel.h = h;

	SDL_FillRect(screen, &pixel, color);
}

void SDL::drawRect(int x, int y, int w, int h, int border_width, int color) {
	for(int i = 0; i < border_width; i++) {
		drawFilledRect(x + i, y + i, w - i, 1, color); // Upper horizontal
		drawFilledRect(x + i, y + i, 1, h - i, color); // Left vertical
		drawFilledRect(x + i, y + h - i, w - i, 1, color); // Lower horizontal
		drawFilledRect(x + w - i, y + i, 1, h - i, color); // Right vertical
	}
}

void SDL::update() {
	SDL_Flip(screen);
}

void SDL::quit() {
	SDL_FreeSurface(screen);
	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();
}

void SDL::applySurface(SDL_Surface *surface, int x, int y) {
	SDL_Rect destRect = {x, y, 0, 0};
	SDL_BlitSurface(surface, NULL, screen, &destRect);
}
