capture_image: capture_image.cpp CalibUtils.cpp
	# build
	g++ $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

detect_corners_multiimg: detect_corners_multiimg.cpp CalibUtils.cpp
	# build
	g++ $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

pg: pg.cpp CalibUtils.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv` -I /usr/local/Cellar/eigen/3.3.5/include/eigen3
	# execute
	./$@.out
	# delete an executable file
	rm $@.out
