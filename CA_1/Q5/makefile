CC=g++

CFLAGS=-c -march=haswell

OPENCV='pkg-config --cflags --libs opencv2'

INCDIR=-I/usr/local/bin -I/usr/local/bin/opencv-4.x/include -I/usr/local/bin/opencv-4.x/modules/calib3d/include -I/usr/local/bin/opencv-4.x/modules/core/include -I/usr/local/bin/opencv-4.x/modules/dnn/include -I/usr/local/bin/opencv-4.x/modules/features2d/include -I/usr/local/bin/opencv-4.x/modules/flann/include -I/usr/local/bin/opencv-4.x/modules/gapi/include -I/usr/local/bin/opencv-4.x/modules/highgui/include -I/usr/local/bin/opencv-4.x/modules/imgcodecs/include -I/usr/local/bin/opencv-4.x/modules/imgproc/include -I/usr/local/bin/opencv-4.x/modules/ml/include -I/usr/local/bin/opencv-4.x/modules/objdetect/include -I/usr/local/bin/opencv-4.x/modules/photo/include -I/usr/local/bin/opencv-4.x/modules/stitching/include -I/usr/local/bin/opencv-4.x/modules/video/include -I/usr/local/bin/opencv-4.x/modules/videoio/include

LIBDIR=-L/usr/local/bin/bin

LIBFILE=-Lopencv_gapi -Lopencv_stitching -Lopencv_alphamat -Lopencv_aruco -Lopencv_bgsegm -Lopencv_bioinspired -Lopencv_ccalib -Lopencv_dnn_objdetect -Lopencv_dnn_superres -Lopencv_dpm -Lopencv_highgui -Lopencv_face -Lopencv_freetype -Lopencv_fuzzy -Lopencv_hfs -Lopencv_img_hash -Lopencv_intensity_transform -Lopencv_line_descriptor -Lopencv_mcc -Lopencv_quality -Lopencv_rapid -Lopencv_reg -Lopencv_rgbd -Lopencv_saliency -Lopencv_sfm -Lopencv_stereo -Lopencv_structured_light -Lopencv_phase_unwrapping -Lopencv_superres -Lopencv_optflow -Lopencv_surface_matching -Lopencv_tracking -Lopencv_datasets -Lopencv_text -Lopencv_dnn -Lopencv_plot -Lopencv_videostab -Lopencv_videoio -Lopencv_viz -Lopencv_xfeatures2d -Lopencv_shape -Lopencv_ml -Lopencv_ximgproc -Lopencv_video -Lopencv_xobjdetect -Lopencv_objdetect -Lopencv_calib3d -Lopencv_imgcodecs -Lopencv_features2d -Lopencv_flann -Lopencv_xphoto -Lopencv_photo -Lopencv_imgproc -Lopencv_core

CST11=-std=c++11

all: main

main: main.o 
	$(CC) $(LIBDIR) $(LIBFILE) $(CST11) main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCDIR) $(CST11) main.cpp

clean:
	rm -f *o main

