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

	Mat hsvimg(img.size(), CV_8UC3);
	cvtColor(img, hsvimg, CV_RGB2HSV, 1);

	Mat pimg(img.size(), CV_8UC1);
	int from_to[] = {2,0}; //value channel extraction
	mixChannels(&hsvimg, 1, &pimg, 1, from_to, 1);

	//Mat thrimg(img.size(), CV_8UC1);
	//adaptiveThreshold(pimg, thrimg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 23, -23);
	
	//GaussianBlur(thrimg, pimg, Size(23, 23), 2.3, 2.3);

	//Mat eqimg(img.size(), CV_8UC1);
	//equalizeHist(pimg, eqimg);
	Mat qimg(img.size(), CV_8UC1);
	Mat displayimg(img.size(), CV_8UC3);
	//adaptiveThreshold(eqimg, newthrimg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 23, -8);
	threshold(pimg, pimg, 123, 255, THRESH_BINARY);
	GaussianBlur(pimg, qimg, Size(23, 23), 5, 5);
	threshold(qimg, qimg, 142, 255, THRESH_BINARY);
	multiply(pimg, qimg, qimg);
	//Canny(qimg, qimg, 42, 123);
	//threshold(qimg, qimg, 127, 255, THRESH_BINARY);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(qimg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	int chmux[] = {0,0, 0,1, 0,2};
	mixChannels(&qimg, 1, &displayimg, 1, chmux, 3);
	vector<Vec4i> lines;
	//HoughLinesP(qimg, lines, 1, CV_PI/180, 42, 42, 0);
	int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] ){
		Scalar color(rand()&255, rand()&255, rand()&255);
		drawContours(displayimg, contours, idx, color, CV_FILLED, 8, hierarchy );
	}
	/*for(vector<Vec4i>::iterator i = lines.begin(); i<lines.end(); i++){
		line(displayimg, Point((*i)[0], (*i)[1]), Point((*i)[2], (*i)[3]), Scalar(0, 255, 0), 5);
	}*/

	//namedWindow("pimg", 0);
	//imshow("pimg", pimg);
	//namedWindow("eqimg", 0);
	//imshow("eqimg", eqimg);
	namedWindow("displayimg", 0);
	imshow("displayimg", displayimg);
	namedWindow("qimg", 0);
	imshow("qimg", qimg);
	//namedWindow("pimg", 0);
	//imshow("pimg", pimg);
	waitKey();
	return 0;
}

