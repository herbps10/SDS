MyMPI MyMPI::instance;

MyMPI &MyMPI::getInstance() {
	return instance;
}

void MyMPI::init(int argc, char** args) {
	MPI::Init(argc, args);

	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();

	ncol = 4;
	nrow = 4;

	// Calculate row and column
	row = rank/4;
	col = rank % 4;
}

void MyMPI::quit() {
	MPI::Finalize();
}
