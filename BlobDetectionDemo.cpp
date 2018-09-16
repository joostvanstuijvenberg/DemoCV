/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.h"

#define THRESHOLD_MIN				0
#define THRESHOLD_MAX				175
#define THRESHOLD_STEP				1

#define AREA_MIN					100
#define AREA_MAX					50000

#define BLOB_MIN_DISTANCE			10

BlobDetectionDemo::BlobDetectionDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Gray values");
	windows.push_back("3. Circular blobs");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * BlobDetectionDemo::demonstrate()                                                               *
 * ---------------------------------------------------------------------------------------------- *
 */
void BlobDetectionDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	std::vector<cv::KeyPoint> keypoints;

	// Default parameters for blob detection.
	cv::SimpleBlobDetector::Params params;
	params.minThreshold = (float)THRESHOLD_MIN;
	params.maxThreshold = (float)THRESHOLD_MAX;
	params.thresholdStep = (float)THRESHOLD_STEP;
	params.minDistBetweenBlobs = (float)BLOB_MIN_DISTANCE;
	params.filterByArea = true;
	params.minArea = (float)AREA_MIN;
	params.maxArea = (float)AREA_MAX;

#if CV_MAJOR_VERSION >= 3
	cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
#else
	cv::SimpleBlobDetector detector(params);
#endif
	
	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Convert to gray image.
	cv::Mat gray(original.size(), CV_8U);
	cv::cvtColor(original, gray, CV_BGR2GRAY);
	windowStrategy.placeWindow(windows[1], gray);

	// Circular blobs. Set parameters for circular blob detection.
	cv::Mat circularBlobs(original.size(), original.type());
	cv::imshow(windows[2], circularBlobs);
	params.filterByArea = false;
	params.filterByColor = false;
	params.filterByConvexity = false;
	params.filterByInertia = false;
	params.filterByCircularity = true;
	params.minCircularity = 1.0;
	params.maxCircularity = 1.0;

#if CV_MAJOR_VERSION >= 3
	detector->detect(gray, keypoints);
#else
	detector.detect(gray, keypoints);
#endif
	cv::drawKeypoints(original, keypoints, circularBlobs, cv::Scalar(180, 225, 225), cv::DrawMatchesFlags::DEFAULT);
	windowStrategy.placeWindow(windows[2], circularBlobs);
}
