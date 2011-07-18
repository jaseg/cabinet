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

	Mat fltimg(img.size(), CV_32FC3);
	img.convertTo(fltimg, fltimg.type());

	Mat hsvimg(img.size(), CV_32FC3);
	cvtColor(fltimg, hsvimg, CV_RGB2HSV, 1);

	Mat pimg(img.size(), CV_32FC1);
	int from_to[] = {2,0}; //value channel extraction
	mixChannels(&hsvimg, 1, &pimg, 1, from_to, 1);

	Mat thrimg(img.size(), CV_32FC1);
	adaptiveThreshold(pimg, thrimg, 1, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 10, 128);

	Mat displayimg(img.size(), CV_8UC1);
	thrimg.convertTo(displayimg, displayimg.type());

	namedWindow("Processed image", 0);
	imshow("Processed image", displayimg);
	waitKey();
	return 0;
}

