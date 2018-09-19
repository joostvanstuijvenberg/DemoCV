/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#ifndef DEMO_H
#define DEMO_H

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "Source.h"
#include "WindowStrategy.h"

/*
 * ---------------------------------------------------------------------------------------------- *
 * Abstract superclass Demonstration                                                              *
 * ---------------------------------------------------------------------------------------------- *
 */
class Demo
{
public:
	void show() const;
	void hide() const;
	int getNumberOfWindows() const;
	virtual void demonstrate(Source& source, WindowStrategy& windowStrategy);
protected:
	std::vector<std::string> windows;
	cv::Mat original;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass BasicMorphologyDemo                                                          *
 * ---------------------------------------------------------------------------------------------- *
 */
class BasicMorphologyDemo : public Demo
{
public:
	BasicMorphologyDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
private:
	int threshold;
	int erosionX, erosionY;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass BitPlaneSlicingDemo                                                          *
 * ---------------------------------------------------------------------------------------------- *
 */
class BitPlaneSlicingDemo : public Demo
{
public:
	BitPlaneSlicingDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
	void addHiddenText(cv::Mat& source, std::string text, cv::Mat& target);
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass BlobDetectionDemo                                                          *
 * ---------------------------------------------------------------------------------------------- *
 */
class BlobDetectionDemo : public Demo
{
public:
	BlobDetectionDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
private:
	cv::SimpleBlobDetector::Params params;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass RegionOfInterestDemo                                                         *
 * ---------------------------------------------------------------------------------------------- *
 */
class RegionOfInterestDemo : public Demo
{
public:
	RegionOfInterestDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass ColorDemo                                                                    *
 * ---------------------------------------------------------------------------------------------- *
 */
class ColorDemo : public Demo
{
public:
	ColorDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass ThresholdDemo                                                                *
 * ---------------------------------------------------------------------------------------------- *
 */
class ThresholdDemo : public Demo
{
public:
	ThresholdDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
private:
	int tBinary, tBinaryInv, tTrunc, tToZero, tToZeroInv;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass SmoothingDemo                                                                *
 * ---------------------------------------------------------------------------------------------- *
 */
class SmoothingDemo : public Demo
{
public:
	SmoothingDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
};

/*
 * ---------------------------------------------------------------------------------------------- *
 * Concrete subclass EdgeDetectionDemo                                                            *
 * ---------------------------------------------------------------------------------------------- *
 */
class EdgeDetectionDemo : public Demo
{
public:
	EdgeDetectionDemo();
	void demonstrate(Source& source, WindowStrategy& windowStrategy) override;
};

#endif