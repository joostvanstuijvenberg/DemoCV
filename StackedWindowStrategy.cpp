/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "WindowStrategy.hpp"

/*
 * ---------------------------------------------------------------------------------------------- *
 * StackedWindowStrategy::reset()                                                                 *
 * ---------------------------------------------------------------------------------------------- *
 */
void StackedWindowStrategy::reset(const int numberOfWindows, const cv::Size& windowSize)
{
    WindowStrategy::reset(numberOfWindows, windowSize);
    dx = (getDisplaySize().width - windowSize.width) / numberOfWindows;
    dy = (getDisplaySize().height - windowSize.height) / numberOfWindows;
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * StackedWindowStrategy::placeWindow()                                                           *
 * ---------------------------------------------------------------------------------------------- *
 */
void StackedWindowStrategy::placeWindow(const std::string& title, const cv::Mat& image)
{
    WindowStrategy::placeWindow(title, image);
    x += dx;
    y += dy;
}