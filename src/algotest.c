/* 	Cabinet algorithm test file.
 *  This file is used to test any algorithm code -- it's a playground.
 *	Copyright (C) 2011 by Sebastian Götte <s@jaseg.de>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdio> //for printf()
#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	Mat img;
	//Parse arguments
	if(argc > 2)
		cout<<"Only processing argument no. 1"<<endl;
	if(argc == 1){
		cout<<"Defaulting to image file ../testdata/free-on-wood"<<endl;
		img = imread("../testdata/free-on-wood");
	}else{
		img = imread(argv[1]);
	}
	if(!img.data){
		cout<<"Could not properly read the image file (does it exist? Is $PWD correct? etc... Exiting now."<<endl;
		return 1;
	}
	namedWindow("Raw image", 0);
	imshow("Raw image", img);
	printf("   img: %d*%d, type %d ch %d\n", img.rows, img.cols, img.type(), img.channels());
	Mat hsvimg(img.size(), CV_8UC3);
	printf("hsvimg: %d*%d, type %d ch %d\n", hsvimg.rows, hsvimg.cols, hsvimg.type(), hsvimg.channels());
	cvtColor(img, hsvimg, CV_RGB2HSV, 1);
	Mat pimg(img.size(), CV_8UC1);
	printf("  pimg: %d*%d, type %d ch %d\n", pimg.rows, pimg.cols, pimg.type(), pimg.channels());
	int from_to[] = {2,0}; //value channel extraction
	mixChannels(&hsvimg, 1, &pimg, 1, from_to, 1);

	namedWindow("Processed image", 0);
	imshow("Processed image", pimg);
	waitKey();
	return 0;
}

