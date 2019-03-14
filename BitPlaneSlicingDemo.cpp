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
 * BitPlaneSlicingDemo::BitPlaneSlicingDemo()                                                     *
 * ---------------------------------------------------------------------------------------------- *
 */
BitPlaneSlicingDemo::BitPlaneSlicingDemo()
{
	windows.push_back("1. Original");
	windows.push_back("2. Gray values");
	windows.push_back("3. Bit plane slicing, method 1, bit 7");
	windows.push_back("4. Bit plane slicing, method 2, bit 6");
	windows.push_back("5. Bit plane slicing, method 2, bit 5");
	windows.push_back("6. Bit plane slicing, method 2, bit 4");
	windows.push_back("7. Bit plane slicing, method 2, bit 3");
	windows.push_back("8. Bit plane slicing, method 2, bit 2");
	windows.push_back("9. Bit plane slicing, method 2, bit 1");
	windows.push_back("10. Bit plane slicing, method 2, bit 0");
	windows.push_back("11. Secretly tagged (in bit 0)");
	windows.push_back("12. Decoded (bit plane 0 isolated)");
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * BitPlaneSlicingDemo::demonstrate()                                                             *
 * ---------------------------------------------------------------------------------------------- *
 */
void BitPlaneSlicingDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
	Demo::demonstrate(source, windowStrategy);

	// Original image.
	windowStrategy.placeWindow(windows[0], original);

	// Convert to gray image.
	cv::Mat gray(original.size(), CV_8U);
	cv::cvtColor(original, gray, CV_BGR2GRAY);
	windowStrategy.placeWindow(windows[1], gray);

	// Bit plane slicing, method 1: pixel by pixel.
	cv::Mat slice[8];
	slice[7] = cv::Mat(original.size(), CV_8U);
	uchar maskByte = 0b10000000;
	for (int y = 0; y < slice[7].rows; y++)
		for (int x = 0; x < slice[7].cols; x++)
			slice[7].at<uchar>(y, x) = gray.at<uchar>(y, x) & maskByte;
	cv::threshold(slice[7], slice[7], 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[2], slice[7]);

	// Bit plane slicing, method 2: using cv::bitwise_and(). Make 7 images, masked by the bit
	// following the MSB (as this was already done in the previous method) and up to the LSB. Store
	// these images in an array as Mat objects.
	for (int i = 6; i >= 0; i--) {
		slice[i] = cv::Mat(original.size(), CV_8U);
		maskByte /= 2;
		cv::Mat mask(original.size(), CV_8U, cv::Scalar(maskByte));
		cv::bitwise_and(gray, mask, slice[i]);
		cv::threshold(slice[i], slice[i], 0, 255, CV_THRESH_BINARY);
		windowStrategy.placeWindow(windows[9 - i], slice[i]);
	}

	// Make a binary image and write a text in it using cv::putText(). Blend this image with the image
	// containing gray values, by replacing bit 0 from each gray value by bit 0 from the text image.
	cv::Mat blended(original.size(), CV_8U);
	addHiddenText(gray, "Text", blended);
	windowStrategy.placeWindow(windows[10], blended);

	// Now decode the 'secret' text by isolating bit plane 0.
	cv::Mat decoded(original.size(), CV_8U);
	cv::Mat mask(gray.size(), CV_8U, cv::Scalar(0b00000001));
	cv::bitwise_and(blended, mask, decoded);
	cv::threshold(decoded, decoded, 0, 255, CV_THRESH_BINARY);
	windowStrategy.placeWindow(windows[11], decoded);
}

/*
 * ---------------------------------------------------------------------------------------------- *
 * BitPlaneSlicingDemo::addHiddenText()                                                           *
 * ---------------------------------------------------------------------------------------------- *
 */
void BitPlaneSlicingDemo::addHiddenText(cv::Mat& source, std::string text, cv::Mat& target)
{
	cv::Mat textImage(original.size(), CV_8U, cv::Scalar(0));
	cv::putText(textImage, "Text", cv::Point(10, 90), cv::FONT_HERSHEY_COMPLEX, 2.0, cv::Scalar(1));
	for (int y = 0; y < source.rows; y++)
		for (int x = 0; x < source.cols; x++)
		{
			uchar b = source.at<uchar>(y, x);
			uchar m = textImage.at<uchar>(y, x);
			if (m & 0b00000001)
				b = b | 0b00000001;
			else
				b = b & 0b11111110;
			target.at<uchar>(y, x) = b;
		}

}