CC=g++

CFLAGS=-c

OPENCV='pkg-config opencv --cflags --libs'

INCDIR=-I/usr/local/bin -I/usr/local/bin/opencv-4.x -I/usr/local/bin/opencv-4.x/include -I/usr/local/bin/opencv-4.x/modules/calib3d/include -I/usr/local/bin/opencv-4.x/modules/core/include -I/usr/local/bin/opencv-4.x/modules/dnn/include -I/usr/local/bin/opencv-4.x/modules/features2d/include -I/usr/local/bin/opencv-4.x/modules/flann/include -I/usr/local/bin/opencv-4.x/modules/gapi/include -I/usr/local/bin/opencv-4.x/modules/highgui/include -I/usr/local/bin/opencv-4.x/modules/imgproc/include -I/usr/local/bin/opencv-4.x/modules/ml/include -I/usr/local/bin/opencv-4.x/modules/objdetect/include -I/usr/local/bin/opencv-4.x/modules/photo/include -I/usr/local/bin/opencv-4.x/modules/stitching/include -I/usr/local/bin/opencv-4.x/modules/video/include -I/usr/local/bin/opencv-4.x/modules/videoio/include -I/usr/local/bin/opencv-4.x/modules/imgcodecs/include

LIBDIR=-L/usr/local/bin/bin

LIBFILE=-Lopencv_gapi -Lopencv_stitching -Lopencv_ccalib -Lopencv_dnn_objdetect -Lopencv_dnn_superres -Lopencv_highgui -Lopencv_dnn -Lopencv_videoio -Lopencv_xfeatures2d -Lopencv_ml -Lopencv_ximgproc -Lopencv_video -Lopencv_xobjdetect -Lopencv_objdetect -Lopencv_calib3d -Lopencv_imgcodecs  -Lopencv_features2d -Lopencv_flann -Lopencv_xphoto -Lopencv_photo -Lopencv_imgproc -Lopencv_core


CST11=-std=c++11

all: main

main: main.o 
	$(CC) main.o $(LIBDIR) $(LIBFILE) $(CST11) -o main

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCDIR) $(CST11) main.cpp 

clean:
	rm -f *o main

