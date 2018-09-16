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

/*
 * ---------------------------------------------------------------------------------------------- *
 * Superclass WindowStrategy                                                                      *
 * ---------------------------------------------------------------------------------------------- *
 */
class WindowStrategy
{
public:
	virtual void reset(const int numberOfWindows, const cv::Size& windowSize);
	virtual void placeWindow(const std::string& title, const cv::Mat& image);
	bool isMoveEnabled() { return moveEnabled; }
	void setMoveEnabled(bool moveEnabled) { this->moveEnabled = moveEnabled; }
	virtual void alternate();
protected:
	cv::Size getDisplaySize();
	int x = 0, y = 0;
private:
	bool moveEnabled = true;
};

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

inline cv::Size WindowStrategy::getDisplaySize()
{
	return cv::Size(1280, 1024);
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass StackedWindowStrategy                                                        *
 * ---------------------------------------------------------------------------------------------- *
 */
class StackedWindowStrategy : public WindowStrategy
{
public:
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
