/*
 * Joost van Stuijvenberg
 * Avans Hogeschool Breda
 *
 * CC BY-SA 4.0, see: https://creativecommons.org/licenses/by-sa/4.0/
 * sources & updates: https://github.com/joostvanstuijvenberg/DemoCV
 */

#include "Demo.h"

BlobDetectionDemo::BlobDetectionDemo()
{
    windows.emplace_back("1. Original");
    windows.emplace_back("2. Circular blobs");

    cv::FileStorage storage("BlobDetectionParameters.xml", cv::FileStorage::READ);
    cv::FileNode node = storage["opencv_storage"];
    params.read(node);

}

/*
 * ---------------------------------------------------------------------------------------------- *
 * BlobDetectionDemo::demonstrate()                                                               *
 * ---------------------------------------------------------------------------------------------- *
 */
void BlobDetectionDemo::demonstrate(Source& source, WindowStrategy& windowStrategy)
{
    Demo::demonstrate(source, windowStrategy);

    std::vector<cv::KeyPoint> keypoints;
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    // Original image.
    windowStrategy.placeWindow(windows[0], original);

    // Circular blobs.
    cv::Mat circularBlobs(original.size(), original.type());
    cv::imshow(windows[1], circularBlobs);

    detector->detect(original, keypoints);
    cv::drawKeypoints(original, keypoints, circularBlobs, cv::Scalar(180, 225, 225), cv::DrawMatchesFlags::DEFAULT);
    windowStrategy.placeWindow(windows[1], circularBlobs);
}
