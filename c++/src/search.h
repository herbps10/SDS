class Search {
	public:
		static Search &getInstance();
		void init(string haystack_path, string needle_path);
		int distance(int x, int y, int width, int height); // Determines how close the given rectangle is to the needle
		int fitness(int x, int y, int width, int height); 
		int rgb_distance_euclidian(int* color1, int* color2);
		int rgb_distance_sum(int* color1, int* color2);
		void draw();

		int haystack_width();
		int haystack_height();
		int needle_width();
		int needle_height();

		int get_max_distance();

		static Search instance;

	private:
		Image* needle;
		Image* haystack;
		int max_distance;
		int max_pixel_distance;
		int area;
		int *needle_average;
};
