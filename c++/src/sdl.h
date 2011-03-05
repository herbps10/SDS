// Provides global access to SDL and the main SDL surface

class SDL {
	public:
		SDL_Surface* screen;
		TTF_Font* font; 
		static SDL &getInstance();
		void init();
		void drawPixel(int x, int y, int r, int g, int b);
		void drawPixel(int x, int y, int color);
		void drawFilledRect(int x, int y, int w, int h, int color);
		void drawRect(int x, int y, int w, int h, int border_width, int color);
		void update();
		void quit();
		void applySurface(SDL_Surface *surface, int x, int y);

	private:
		static SDL instance;
};
