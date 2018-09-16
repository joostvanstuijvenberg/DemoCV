/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "WindowStrategy.h"
#include "math.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * CircularWindowStrategy::reset()                                                                *
 * ---------------------------------------------------------------------------------------------- *
 */
void CircularWindowStrategy::reset(const int numberOfWindows, const cv::Size& windowSize)
{
	WindowStrategy::reset(numberOfWindows, windowSize);
	angle = 0.0;
	angleIncrement = 2.0 * std::acos(-1) / numberOfWindows;
	arrow = getDisplaySize().height / 2 - (windowSize.height / 2) - 40;
	centreX = getDisplaySize().width / 2;
	centreY = getDisplaySize().height / 2;
	displaceX = windowSize.width / 2;
	displaceY = windowSize.height / 2;
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * CircularWindowStrategy::placeWindow()                                                          *
 * ---------------------------------------------------------------------------------------------- *
 */
void CircularWindowStrategy::placeWindow(const std::string& title, const cv::Mat& image)
{
	x = (int)(centreX - (std::sin(angle) * arrow) - displaceX);
	y = (int)(centreY - (std::cos(angle) * arrow) - displaceY);
	WindowStrategy::placeWindow(title, image);
	angle += (angleIncrement * direction);
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * CircularWindowStrategy::alternate()                                                            *
 * ---------------------------------------------------------------------------------------------- *
 */
void CircularWindowStrategy::alternate()
{
	direction *= -1;
}