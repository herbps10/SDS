Image::Image() {
	
}

void Image::loadPath(string path) {
	CImg<int> img(path.c_str());
	image = img;
}

void Image::loadCImg(cimg_library::CImg<int> img) {
	image = img;
}

/*
 * Finds the average color of a subset of the image
 */
int* Image::average(int x, int y, int w, int h) {
	int r = 0, b = 0, g = 0;
	int size = w * h;

	for(int i = x; i < x + w; i++) {
		for(int n = y; n < y + h; n++) {
			r += image.atXY(i, n, 0);
			g += image.atXY(i, n, 1);
			b += image.atXY(i, n, 2);
		}
	}

	r /= size;
	g /= size;
	b /= size;

	int *colors = new int[3];
	colors[0] = r;
	colors[1] = g;
	colors[2] = b;

	return colors;
}

/*
 * Find the color average of the whole image
 */
int* Image::average() {
	return average(0, 0, image.width(), image.height());
}

/*
 * Draws the image to the SDL screen at the given coordinates
 *
 */
void Image::drawImage() {
	Image::drawRect(0, 0, image.width(), image.height());
}

void Image::drawRect(int startx, int starty, int w, int h) {
	for(int x = startx; x < startx + w; x++) {
		for(int y = starty; y < starty + h; y++) {
			int color = SDL_MapRGB(SDL::getInstance().screen->format, image.atXY(x, y, 0), image.atXY(x, y, 1), image.atXY(x, y, 2));

			SDL::getInstance().drawFilledRect(
				BORDER_X + ((x-startx) * PIXEL_SIZE),
				BORDER_Y + ((y-starty) * PIXEL_SIZE),
				PIXEL_SIZE,
				PIXEL_SIZE,
				color
			);	
		}
	}
}

int* Image::colorAtXY(int x, int y) {
	int *colors = new int[3];
	//cout << "colorAtXY: ";
	for(int i = 0; i < 3; i++) {
		//cout << image.atXY(x, y, i) << " ";
		colors[i] = image.atXY(x, y, i);
	}

	//cout << endl;
	
	return colors;
}

int Image::width() {
	return image.width();
}

int Image::height() {
	return image.height();
}

void Image::addText(string str) {
	unsigned int black[] = {0, 0, 0};
	image.draw_text(5, 5, str.c_str(), black);
}
