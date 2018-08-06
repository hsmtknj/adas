capture_image: capture_image.cpp
	# build
	g++ $< -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete execution file
	rm $@.out

detect_corners: detect_corners.cpp
	# build
	g++ $< -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# execute
	./$@.out
	# delete execution file
	rm $@.out
