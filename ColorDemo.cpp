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
 * ColorDemo::ColorDemo()                                                                         *
 * ---------------------------------------------------------------------------------------------- *
 */
ColorDemo::ColorDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Red channel");
	windows.push_back("3. Green channel");
	windows.push_back("4. Blue channel");
	windows.push_back("5. Blue and green set to 0");
	windows.push_back("6. Negative");
	windows.push_back("7. HSV - Hue channel");
	windows.push_back("8. HSV - Saturation channel");
	windows.push_back("9. HSV - Value/Brightness channel");
	windows.push_back("10. HSL - Hue channel");
	windows.push_back("11. HSL - Saturation channel");
	windows.push_back("12. HSL - Lightness channel");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * ColorDemo::demonstrate()                                                                       *
 * ---------------------------------------------------------------------------------------------- *
 */
void ColorDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Red, green and blue channels.
	cv::Mat bgr[3];
	cv::split(original, bgr);
	windowStrategy.placeWindow(windows[1], bgr[2]);
	windowStrategy.placeWindow(windows[2], bgr[1]);
	windowStrategy.placeWindow(windows[3], bgr[0]);

	// Set the blue and green components to 0.
	cv::Mat red(original);
	for (int y = 0; y < red.rows; y++)
		for (int x = 0; x < red.cols; x++)
		{
			red.at<cv::Vec3b>(y, x)[0] = 0;
			red.at<cv::Vec3b>(y, x)[1] = 0;
		}
	windowStrategy.placeWindow(windows[4], red);

	// Negative.
	cv::Mat negative(original);
	cv::subtract(cv::Scalar(255, 255, 255), original, negative);
	windowStrategy.placeWindow(windows[5], negative);

	// Hue, saturation and value channels.
	cv::Mat hsv[3];
	cv::Mat hsvImage(original);
	cv::cvtColor(original, hsvImage, CV_RGB2HSV);
	cv::split(hsvImage, hsv);
	windowStrategy.placeWindow(windows[6], hsv[0]);
	windowStrategy.placeWindow(windows[7], hsv[1]);
	windowStrategy.placeWindow(windows[8], hsv[2]);

	// Hue, saturation and lightness channels.
	cv::Mat hsl[3];
	cv::Mat hslImage(original);
	cvtColor(original, hslImage, CV_RGB2HLS);
	cv::split(hslImage, hsl);
	windowStrategy.placeWindow(windows[9], hsl[0]);
	windowStrategy.placeWindow(windows[10], hsl[1]);
	windowStrategy.placeWindow(windows[11], hsl[2]);
}
