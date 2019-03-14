/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, zie: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#ifndef WINDOWSTRATEGY_H
#define WINDOWSTRATEGY_H

#include "opencv2/opencv.hpp"

#if WIN64
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

/*
 * ---------------------------------------------------------------------------------------------- *
 * Superclass WindowStrategy                                                                      *
 * ---------------------------------------------------------------------------------------------- *
 */
class WindowStrategy
{
public:
    WindowStrategy();
	virtual void reset(const int numberOfWindows, const cv::Size& windowSize);
	virtual void placeWindow(const std::string& title, const cv::Mat& image);
	bool isMoveEnabled() { return moveEnabled; }
	void setMoveEnabled(bool moveEnabled) { this->moveEnabled = moveEnabled; }
	virtual void alternate();
protected:
	cv::Size getDisplaySize() { return cv::Size(width, height); }
	int x = 0, y = 0;
	int width = 0, height = 0;
private:
	bool moveEnabled = true;
};

inline WindowStrategy::WindowStrategy()
{
#if WIN32
    width  = (int) GetSystemMetrics(SM_CXSCREEN);
    height = (int) GetSystemMetrics(SM_CYSCREEN);
#else
    auto disp = XOpenDisplay(nullptr);
    auto scrn = DefaultScreenOfDisplay(disp);
    width  = scrn->width;
    height = scrn->height;
#endif
}

inline void WindowStrategy::reset(const int numberOfWindows, const cv::Size& windowSize) {
	assert(numberOfWindows > 0);
	x = 0, y = 0;
}

inline void WindowStrategy::placeWindow(const std::string& title, const cv::Mat& image)
{
	cv::imshow(title, image);
	if (moveEnabled)
		cv::moveWindow(title, x, y);
}

inline void WindowStrategy::alternate() {}

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass StackedWindowStrategy                                                        *
 * ---------------------------------------------------------------------------------------------- *
 */
class StackedWindowStrategy : public WindowStrategy
{
public:
    StackedWindowStrategy() : WindowStrategy() {}
	void reset(const int numberOfWindows, const cv::Size& windowSize) override;
	void placeWindow(const std::string& title, const cv::Mat& image) override;
private:
	int dx, dy;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass ShiftedWindowStrategy                                                        *
 * ---------------------------------------------------------------------------------------------- *
 */
class ShiftedWindowStrategy : public WindowStrategy
{
public:
    ShiftedWindowStrategy() : WindowStrategy() {}
	void reset(const int numberOfWindows, const cv::Size& windowSize) override;
	void placeWindow(const std::string& title, const cv::Mat& image) override;
private:
	int dy;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass CircularWindowStrategy                                                       *
 * ---------------------------------------------------------------------------------------------- *
 */
class CircularWindowStrategy : public WindowStrategy
{
public:
    CircularWindowStrategy() : WindowStrategy() {}
	void reset(const int numberOfWindows, const cv::Size& windowSize) override;
	void placeWindow(const std::string& title, const cv::Mat& image) override;
	void alternate() override;
private:
	double angle, angleIncrement;
	int direction = 1;
	int arrow;
	int centreX, centreY;
	int displaceX, displaceY;
};

#endif
