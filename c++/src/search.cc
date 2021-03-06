Search Search::instance;

Search &Search::getInstance() {
	return instance;
}

void Search::init(string haystack_path, string needle_path) {
	needle = new Image();
	needle->loadPath(needle_path);

	haystack = new Image();
	haystack->loadPath(haystack_path);
	
	// Calculate which part of the image this node should look at
	node_width = haystack->width() / MyMPI::getInstance().ncol;
	node_height = haystack->height() / MyMPI::getInstance().nrow;
	node_x = MyMPI::getInstance().col * node_width;
	node_y = MyMPI::getInstance().row * node_height;

	PIXEL_SIZE = SCREEN_WIDTH / node_width;

	// Save the average color of the needle image
	needle_average = needle->average();

	// Calculate area of the needl image
	area = needle->width() * needle->height();

	// The max pixel distance is the theoretical farthest one pixel's color can differ from another
	//max_pixel_distance = 3 * PIXEL_COLOR_MAX;
	max_pixel_distance = sqrt((double)3 * pow(PIXEL_COLOR_MAX, 2.0)); // This is the one for euclidian

	// The max distance is the theoretical farthest that the needle image can differ from another image
	max_distance = area * max_pixel_distance;
}

int Search::distance(int x, int y, int width, int height) {
	int distance = 0;

	int new_width = width;
	int new_height = height;

	if(x + width - 1 > haystack->width()) {
		new_width = haystack->width() - x;
		distance += (width - new_width) * height * max_pixel_distance + OFF_SCREEN_DISTANCE_PENALTY;
	}

	if(x < 0) {
		new_width = x + width;
		distance += (width - new_width) * height * max_pixel_distance + OFF_SCREEN_DISTANCE_PENALTY;
	}

	if(y + height - 1 > haystack->height()) {
		new_height = haystack->height() - y;
		distance += (height - new_height) * width * max_pixel_distance + OFF_SCREEN_DISTANCE_PENALTY;
	}

	if(y < 0) {
		new_height = y + height;
		distance += (height - new_height) * width * max_pixel_distance + OFF_SCREEN_DISTANCE_PENALTY;
	}

	width = new_width;
	height = new_height;

	for(int c = x; c < x + width; c++) {
		for(int r = y; r < y + height; r++) {
			int* color = haystack->colorAtXY(c, r);
			distance += rgb_distance_euclidian(haystack->colorAtXY(c, r), needle->colorAtXY(c - x, r - y));
			/*
			int d = rgb_distance_euclidian(haystack->colorAtXY(c, r), needle->colorAtXY(c - x, r - y));
			if(d < 20) {
				SDL::getInstance().drawPixel(BORDER_X + c, BORDER_Y + r, SDL_MapRGB(SDL::getInstance().screen->format, 255-d, 0, 0));
			}
			*/
		}
	}

	return distance;
}

int Search::fitness(int x, int y, int width, int height) {
	int distance_percent = (100 * distance(x, y, width, height))/max_distance;

	int *average = haystack->average(x, y, width, height);
	int color_average_percent = (100 * rgb_distance_euclidian(needle_average, average))/max_pixel_distance;

	// Weighted average
	int fitness = (color_average_percent + distance_percent * 4) / 5;

	return fitness;
}

int Search::rgb_distance_euclidian(int* color1, int* color2) {
	int distance = 0;
	for(int i = 0; i < 3; i++) {
		distance += pow((double)*(color1 + i) - (double)*(color2 + i), 2);
	}

	distance = sqrt(distance);
	
	return distance;
}

int Search::rgb_distance_sum(int* color1, int* color2) {
	int distance = 0;
	for(int i = 0; i < 3; i++) {
		distance += abs((*color1 + i) - *(color2 + i));
	}

	return distance;
}

void Search::draw() {
	haystack->drawRect(node_x, node_y, node_width, node_height);
}

int Search::haystack_width() {
	return haystack->width();
}

int Search::haystack_height() {
	return haystack->height();
}

int Search::needle_width() {
	return needle->width();
}

int Search::needle_height() {
	return needle->height();
}

int Search::get_max_distance() {
	return max_distance;
}
