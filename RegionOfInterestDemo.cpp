/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * RegionOfInterestDemo::RegionOfInterestDemo()                                                   *
 * ---------------------------------------------------------------------------------------------- *
 */
RegionOfInterestDemo::RegionOfInterestDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. 1/4th of the original");
	windows.push_back("3. Upper half");
	windows.push_back("4. Bottom half");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * RegionOfInterestDemo::demonstrate()                                                            *
 * ---------------------------------------------------------------------------------------------- *
 */
void RegionOfInterestDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Draw a square around the middle 1/9th part of the image.
	int w2 = original.size().width / 3;
	int h2 = original.size().height / 3;
	cv::rectangle(original, cv::Point(w2, h2), cv::Point(w2 * 2, h2 * 2), cv::Scalar(127, 80, 23), 3, CV_AA);

	// Original image, with rectangle.
	windowStrategy.placeWindow(windows[0], original);

	// Copy 1/4th of the original image to a new image.
	cv::Rect roi(0, 0, original.size().width / 2, original.size().height / 2);
	cv::Mat snippet = original(roi);
	windowStrategy.placeWindow(windows[1], snippet);

	// Split into upper and lower halves.
	int h = original.rows, w = original.cols;
	cv::Mat upper = original(cv::Rect(0, 0, w - 1, (h / 2) - 1));
	windowStrategy.placeWindow(windows[2], upper);
	cv::Mat lower = original(cv::Rect(0, h / 2, w - 1, (h / 2) - 1));
	windowStrategy.placeWindow(windows[3], lower);
}
