// Provides global access to SDL and the main SDL surface

class MyMPI {
	public:
		static MyMPI &getInstance();
		void init(int argc, char** args);
		void quit();
		int size, rank, col, row, ncol, nrow;

	private:
		static MyMPI instance;
};
