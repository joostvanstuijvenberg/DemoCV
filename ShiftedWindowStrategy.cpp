/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "WindowStrategy.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * ShiftedWindowStrategy::reset()                                                                 *
 * ---------------------------------------------------------------------------------------------- *
 */
void ShiftedWindowStrategy::reset(const int numberOfWindows, const cv::Size& windowSize)
{
	WindowStrategy::reset(numberOfWindows, windowSize);
	x = (getDisplaySize().width - windowSize.width) / 2;
	y = 0;
	dy = (getDisplaySize().height - windowSize.height) / numberOfWindows;
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * ShiftedWindowStrategy::placeWindow()                                                           *
 * ---------------------------------------------------------------------------------------------- *
 */
void ShiftedWindowStrategy::placeWindow(const std::string& title, const cv::Mat& image)
{
	WindowStrategy::placeWindow(title, image);
	y += dy;
}