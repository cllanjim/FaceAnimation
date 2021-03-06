#ifndef IMAGE_READER_KINECT_
#define IMAGE_READER_KINECT_

#include <glog/logging.h>

#include <string>
#include <fstream>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "parameters.h"

#include <vector>
using namespace std;

class ImageReaderKinect
{
public:
	ImageReaderKinect(string p)
	{
		path = p;
		
		dframes.resize(frame_count_end, cv::Mat(1080, 1920, CV_8UC3));
		cframes.resize(frame_count_end, cv::Mat(512, 424, CV_16UC3));
#pragma omp parallel for
		for (int i = 0; i < frame_count_end; i++) {
			char str[20];
			sprintf(str, "c%d.png", i);
			cframes[i] = cv::imread(path + str/*, cv::IMREAD_UNCHANGED*/);
			//cv::imshow("infrared", cframes[i]);
			//cv::waitKey(0);
			sprintf(str, "d%d.png", i);
			dframes[i] = cv::imread(path + str, cv::IMREAD_UNCHANGED);
		}
	}

	void GetFrame(int idx, cv::Mat& cframe, cv::Mat& dframe)
	{
		LOG(INFO) << "read image (I/O)";
		cframe = cframes[idx];
		dframe = dframes[idx];
	}
private:
	string path;
	std::vector<cv::Mat> dframes;
	std::vector<cv::Mat> cframes;
};

#endif 