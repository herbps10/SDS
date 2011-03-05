CC 	= g++ -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -pthread -L/usr/lib/openmpi/lib -lmpi_cxx -lmpi -lopen-rte -lopen-pal -ldl -Wl,--export-dynamic -lnsl -lutil -lm -ldl

mosaic: src/main.cpp
	$(CC) -o sds -lSDL -lSDL_image -lSDL_ttf -lX11 src/main.cpp
