#include "brightness_operation.hpp"

cv::Mat BrightnessOperation::execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) {
    // get brightness factor from parameters (default to 1.0 if not specified)
    double factor = 1.0;
    auto it = params.find("factor");
    if (it != params.end()) {
        factor = it->second;
    }
    
    // extract ROI from input image
    cv::Mat roi_image = extractROI(input, roi);
    cv::Mat output;
    
    // convert to float for processing
    cv::Mat float_img;
    roi_image.convertTo(float_img, CV_32F);
    
    // apply brightness adjustment
    float_img *= factor;
    
    // convert back to original type
    float_img.convertTo(output, roi_image.type());
    
    // ensure values are clamped to valid range
    cv::threshold(output, output, 255, 255, cv::THRESH_TRUNC);
    cv::threshold(output, output, 0, 0, cv::THRESH_TOZERO);
    
    // apply the processed ROI back to the original image
    return applyROI(input, output, roi);
} 