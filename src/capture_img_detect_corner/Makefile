intrinsic_calib: intrinsic_calib.cpp ../utils/CvUtil.cpp
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

detect_corners_multiimg: detect_corners_multiimg.cpp ../utils/CvUtil.cpp
	# # -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out

pg: pg.cpp ../utils/CvUtil.cpp
	# # -*- BUILD -*-
	g++ -std=c++14 $^ -o $@.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	# -*- EXECUTE -*-
	./$@.out
	# -*- DELETE EXE FILE -*-
	rm $@.out
