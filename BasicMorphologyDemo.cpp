/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.hpp"

#define THRESHOLD_DEFAULT			127
#define THRESHOLD_MAX				255

#define EROSION_ELEMENT_DEFAULT		5
#define EROSION_ELEMENT_MAX			39

/*
 * ---------------------------------------------------------------------------------------------- *
 * BasicMorphologyDemo::BasicMorphologyDemo()                                                     *
 * ---------------------------------------------------------------------------------------------- *
 */
BasicMorphologyDemo::BasicMorphologyDemo()
{
	windows.emplace_back("1. Original");
	windows.emplace_back("2. Gray values");
	windows.emplace_back("3. Binary");
	windows.emplace_back("4. Erode");
	windows.emplace_back("5. Contours");
	windows.emplace_back("6. Dilate");
	windows.emplace_back("7. Opening");
	windows.emplace_back("8. Closing");
	windows.emplace_back("9. DistanceTransform");

	threshold = THRESHOLD_DEFAULT;
	erosionX = EROSION_ELEMENT_DEFAULT;
	erosionY = EROSION_ELEMENT_DEFAULT;
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * BasicMorphologyDemo::demonstrate()                                                             *
 * ---------------------------------------------------------------------------------------------- *
 */
void BasicMorphologyDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Convert to gray image.
	cv::Mat gray(original.size(), CV_8U);
	cv::cvtColor(original, gray, CV_BGR2GRAY);
	windowStrategy.placeWindow(windows[1], gray);

	// Binary image.
	cv::Mat binary(original.size(), CV_8U);
	cv::Mat binaryForDisplay(original.size(), CV_8U);
	cv::threshold(gray, binary, threshold, 1, CV_THRESH_BINARY);
	cv::threshold(binary, binaryForDisplay, 0, 255, CV_THRESH_BINARY);
	cv::createTrackbar("Threshold", windows[2], &threshold, THRESHOLD_MAX);
	windowStrategy.placeWindow(windows[2], binaryForDisplay);

	// Erosion.
	cv::Mat eroded(original.size(), CV_8U);
	cv::Mat erosionKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(erosionX, erosionY));
	cv::erode(binary, eroded, erosionKernel);
	cv::threshold(eroded, eroded, 0, 255, CV_THRESH_BINARY);
	cv::createTrackbar("Erosion structuring element x", windows[3], &erosionX, EROSION_ELEMENT_MAX);
	cv::createTrackbar("Erosion structuring element y", windows[3], &erosionY, EROSION_ELEMENT_MAX);
	windowStrategy.placeWindow(windows[3], eroded);

	// Make contours by subtracting the eroded image from the original.
	cv::Mat contours(original.size(), CV_8U);
	cv::subtract(binary, eroded, contours);
	cv::threshold(contours, contours, 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[4], contours);

	// Dilation.
	cv::Mat dilated(original.size(), CV_8U);
	cv::Mat dilationKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(binary, dilated, dilationKernel);
	cv::threshold(dilated, dilated, 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[5], dilated);

	// Opening.
	cv::Mat opened(original.size(), CV_8U);
	cv::Mat openingKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
	cv::erode(binary, opened, openingKernel);
	cv::dilate(opened, opened, openingKernel);
	cv::threshold(opened, opened, 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[6], opened);

	// Closing.
	cv::Mat closed(original.size(), CV_8U);
	cv::Mat closingKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::dilate(binary, closed, closingKernel);
	cv::erode(closed, closed, closingKernel);
	cv::threshold(closed, closed, 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[7], closed);

	// Distance transform. Normalise the floating point values to 8 bit gray values.
	cv::Mat distTransformed(original.size(), CV_8U);
	cv::distanceTransform(binary, distTransformed, CV_DIST_C, 3);
	cv::normalize(distTransformed, distTransformed, 0.0, 1.0, cv::NORM_MINMAX);
	windowStrategy.placeWindow(windows[8], distTransformed);
}
