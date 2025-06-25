#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <map>

/**
 * region of interest structure
 */
struct ROI {
    int x;
    int y;
    int width;
    int height;

    ROI(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}
};

/**
 * base class for all image processing operations
 * 
 * this class defines the interface that all operations must implement.
 * each operation takes an input image, ROI, and parameters, and returns the result.
 */
class Operation {
public:
    virtual ~Operation() = default;

    /**
     * execute the operation on the input image
     * 
     * @param input the input image to process
     * @param roi region of interest (if width/height = 0, process entire image)
     * @param params map of parameter names to values
     * @return the processed image
     */
    virtual cv::Mat execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) = 0;

    /**
     * get the name/type of this operation
     * 
     * @return string identifier for the operation
     */
    virtual std::string getName() const = 0;

    /**
     * validate parameters for this operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    virtual bool validateParameters(const std::map<std::string, double>& parameters) const = 0;

protected:
    /**
     * helper function to extract ROI from image
     * 
     * @param input the input image
     * @param roi the region of interest
     * @return the ROI portion of the image, or entire image if ROI is empty
     */
    cv::Mat extractROI(const cv::Mat& input, const ROI& roi) {
        if (roi.width == 0 || roi.height == 0) {
            return input;
        }
        return input(cv::Rect(roi.x, roi.y, roi.width, roi.height));
    }

    /**
     * helper function to apply processed ROI back to original image
     * 
     * @param input the original input image
     * @param processed_roi the processed ROI image
     * @param roi the region of interest
     * @return the image with processed ROI applied
     */
    cv::Mat applyROI(const cv::Mat& input, const cv::Mat& processed_roi, const ROI& roi) {
        if (roi.width == 0 || roi.height == 0) {
            return processed_roi;
        }
        cv::Mat output = input.clone();
        processed_roi.copyTo(output(cv::Rect(roi.x, roi.y, roi.width, roi.height)));
        return output;
    }
}; 