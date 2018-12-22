capture_image: capture_image.cpp
	# build
	g++ $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

detect_corners: detect_corners.cpp
	# build
	g++ $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

pg: pg.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out
