intrinsic_calib: intrinsic_calib.cpp CalibUtils.cpp
	# -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out

capture_image: capture_image.cpp
	# # -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out

detect_corners_multiimg: detect_corners_multiimg.cpp ../utils/CalibUtils.cpp
	# # -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out

pg: pg.cpp ../utils/CalibUtils.cpp
	# # -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out
