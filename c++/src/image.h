using namespace std;

class Image {
	private:
	cimg_library::CImg<int> image;

	public:
	Image();
	void loadPath(string path);
	void loadCImg(cimg_library::CImg<int> img);
	int* average();
	int* average(int x, int y, int w, int h);
	void drawRect(int startx, int starty, int w, int h);
	void drawImage();
	int width();
	int height();
	void addText(string str);
	int* colorAtXY(int x, int y);
};
