/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.hpp"

/*
 * ---------------------------------------------------------------------------------------------- *
 * EdgeDetectionDemo::EdgeDetectionDemo()                                                     *
 * ---------------------------------------------------------------------------------------------- *
 */
EdgeDetectionDemo::EdgeDetectionDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Canny on original image");
	windows.push_back("3. Blurred");
	windows.push_back("4. Canny on blurred image");
	windows.push_back("5. Sobel");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * EdgeDetectionDemo::demonstrate()                                                             *
 * ---------------------------------------------------------------------------------------------- *
 */
void EdgeDetectionDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Perform Canny's edge detection algorithm on the original.
	cv::Mat canny1(original.size(), original.type());
	cv::Canny(original, canny1, 10, 30, 3);
	windowStrategy.placeWindow(windows[1], canny1);

	// Blur to reduce noise.
	cv::Mat blurred(original.size(), original.type());
	cv::blur(original, blurred, cv::Size(5, 5));
	windowStrategy.placeWindow(windows[2], blurred);

	// Perform Canny's edge detection algorithm on the blurred image.
	cv::Mat canny2(original.size(), original.type());
	cv::Canny(blurred, canny2, 10, 30, 3);
	windowStrategy.placeWindow(windows[3], canny2);

	// Perform Canny's edge detection algorithm.
	cv::Mat sobel(original.size(), original.type());
	cv::Mat grad_x(original.size(), original.type());
	cv::Mat grad_y(original.size(), original.type());
	cv::Mat abs_grad_x(grad_x.size(), grad_x.type());
	cv::Mat abs_grad_y(grad_y.size(), grad_y.type());
	cv::Sobel(blurred, grad_x, CV_16S, 1, 0, 3);
	cv::convertScaleAbs(grad_x, abs_grad_x);
	cv::Sobel(blurred, grad_y, CV_16S, 0, 1, 3);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobel);
	windowStrategy.placeWindow(windows[4], sobel);
}
