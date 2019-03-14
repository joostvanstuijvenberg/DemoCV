/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.hpp"

#define THRESHOLD_DEFAULT			127
#define THRESHOLD_MAX				255

/*
 * ---------------------------------------------------------------------------------------------- *
 * ThresholdDemo::ThresholdDemo()                                                                 *
 * ---------------------------------------------------------------------------------------------- *
 */
ThresholdDemo::ThresholdDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Gray values");
	windows.push_back("3. Binary threshold");
	windows.push_back("4. Binary inverted threshold");
	windows.push_back("5. Truncated threshold");
	windows.push_back("6. To-zero threshold");
	windows.push_back("7. To-zero inverted threshold");
	windows.push_back("8. Adaptive mean threshold");
	windows.push_back("9. Adaptive gaussian threshold");
	windows.push_back("10. Otsu threshold");

	tBinary = THRESHOLD_DEFAULT;
	tBinaryInv = THRESHOLD_DEFAULT;
	tTrunc = THRESHOLD_DEFAULT;
	tToZero = THRESHOLD_DEFAULT;
	tToZeroInv = THRESHOLD_DEFAULT;
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * ThresholdDemo::demonstrate()                                                                   *
 * ---------------------------------------------------------------------------------------------- *
 */
void ThresholdDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Convert to gray image.
	cv::Mat gray(original.size(), CV_8U);
	cv::cvtColor(original, gray, CV_BGR2GRAY);
	windowStrategy.placeWindow(windows[1], gray);

	// Binary threshold.
	cv::Mat thrBinary(gray.size(), CV_8U);
	cv::threshold(gray, thrBinary, tBinary, THRESHOLD_MAX, CV_THRESH_BINARY);
	cv::createTrackbar("Binary", windows[2], &tBinary, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[2], thrBinary);

	// Binary inverted threshold.
	cv::Mat thrBinaryInv(gray.size(), CV_8U);
	cv::threshold(gray, thrBinaryInv, tBinaryInv, THRESHOLD_MAX, CV_THRESH_BINARY_INV);
	cv::createTrackbar("Binary inverted", windows[3], &tBinaryInv, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[3], thrBinaryInv);

	// Truncated threshold.
	cv::Mat thrTruncated(gray.size(), CV_8U);
	cv::threshold(gray, thrTruncated, tTrunc, THRESHOLD_MAX, CV_THRESH_TRUNC);
	cv::createTrackbar("Truncated", windows[4], &tTrunc, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[4], thrTruncated);

	// To-zero threshold.
	cv::Mat thrToZero(gray.size(), CV_8U);
	cv::threshold(gray, thrToZero, tToZero, THRESHOLD_MAX, CV_THRESH_TOZERO);
	cv::createTrackbar("To zero", windows[5], &tToZero, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[5], thrToZero);

	// Binary inverted threshold.
	cv::Mat thrToZeroInv(gray.size(), CV_8U);
	cv::threshold(gray, thrToZeroInv, tToZeroInv, THRESHOLD_MAX, CV_THRESH_TOZERO_INV);
	cv::createTrackbar("To zero inverted", windows[6], &tToZeroInv, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[6], thrToZeroInv);

	// Adaptive mean threshold.
	cv::Mat thrAdaptiveMean(gray.size(), CV_8U);
	cv::adaptiveThreshold(gray, thrAdaptiveMean, THRESHOLD_MAX, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 11, 2);
	windowStrategy.placeWindow(windows[7], thrAdaptiveMean);

	// Adaptive gaussian threshold.
	cv::Mat thrAdaptiveGaussian(gray.size(), CV_8U);
	cv::adaptiveThreshold(gray, thrAdaptiveGaussian, THRESHOLD_MAX, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 2);
	windowStrategy.placeWindow(windows[8], thrAdaptiveGaussian);

	// Otsu threshold.
	cv::Mat thrOtsu(gray.size(), CV_8U);
	cv::threshold(gray, thrOtsu, 0, THRESHOLD_MAX, CV_THRESH_BINARY | CV_THRESH_OTSU);
	windowStrategy.placeWindow(windows[9], thrOtsu);
}
