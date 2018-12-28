intrinsic_calib: intrinsic_calib.cpp CalibUtils.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete an executalbe file
	rm $@.out

capture_image: capture_image.cpp CalibUtils.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

detect_corners_multiimg: detect_corners_multiimg.cpp CalibUtils.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete an executable file
	rm $@.out

pg: pg.cpp CalibUtils.cpp
	# build
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete an executable file
	rm $@.out
