/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * SmoothingDemo::SmoothingDemo()                                                                 *
 * ---------------------------------------------------------------------------------------------- *
 */
SmoothingDemo::SmoothingDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Basic convolution");
	windows.push_back("3. Blur");
	windows.push_back("4. Gaussian blur");
	windows.push_back("5. Median blur");
	windows.push_back("6. Bilateral filter");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * SmoothingDemo::demonstrate()                                                                   *
 * ---------------------------------------------------------------------------------------------- *
 */
void SmoothingDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Basic convolution.
	cv::Mat filter2D(original.size(), original.type());
	cv::Mat kernel1 = cv::Mat::ones(9, 9, CV_32F);
	cv::filter2D(original, filter2D, -1, kernel1);
	windowStrategy.placeWindow(windows[1], filter2D);

	// Blur.
	cv::Mat blur(original.size(), original.type());
	cv::blur(original, blur, cv::Size(3, 3));
	windowStrategy.placeWindow(windows[2], blur);

	// Gaussian blur.
	cv::Mat gaussian(original.size(), original.type());
	cv::GaussianBlur(original, gaussian, cv::Size(3, 3), 1.0, 1.0);
	windowStrategy.placeWindow(windows[3], gaussian);

	// Median blur.
	cv::Mat median(original.size(), original.type());
	cv::medianBlur(original, median, 5);
	windowStrategy.placeWindow(windows[4], median);

	// Bilateral filter.
	cv::Mat bilateral(original.size(), original.type());
	cv::bilateralFilter(original, bilateral, 9, 75, 75);
	windowStrategy.placeWindow(windows[5], bilateral);
}
