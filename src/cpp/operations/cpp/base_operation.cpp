#include "../hpp/base_operation.hpp"
#include <iostream>

// roi utility functions
namespace ROITools {
    cv::Mat extractROI(const cv::Mat& input, const ROI& roi) {
        if (roi.full_image) {
            return input;
        }
        return input(cv::Rect(roi.x, roi.y, roi.width, roi.height));
    }
    
    cv::Mat applyROI(const cv::Mat& input, const cv::Mat& processed_roi, const ROI& roi) {
        if (roi.full_image) {
            return processed_roi;
        }
        cv::Mat output = input.clone();
        processed_roi.copyTo(output(cv::Rect(roi.x, roi.y, roi.width, roi.height)));
        return output;
    }
}

// base class implementation - non-virtual interface pattern
cv::Mat Operation::execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) {
    // pre-execution validation
    if (!preExecute(input, roi, params)) {
        throw std::runtime_error("pre-execution validation failed for operation: " + getNameImpl());
    }

    // parameter validation
    if (!validateParameters(params)) {
        throw std::runtime_error("invalid parameters for operation: " + getNameImpl());
    }

    // execute operation
    cv::Mat result = executeImpl(input, roi, params);

    // post-execution validation
    if (!postExecute(input, result, roi, params)) {
        throw std::runtime_error("post-execution validation failed for operation: " + getNameImpl());
    }

    return result;
}

std::string Operation::getName() const {
    return getNameImpl();
}

bool Operation::validateParameters(const std::map<std::string, double>& parameters) const {
    return validateParametersImpl(parameters);
}

bool Operation::preExecute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) const {
    return true;
}

bool Operation::postExecute(const cv::Mat& input, const cv::Mat& output, const ROI& roi, const std::map<std::string, double>& params) const {
    return true;
} 