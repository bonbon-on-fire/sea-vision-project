#include "blur_operation.hpp"

cv::Mat BlurOperation::execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) {
    // get parameters with defaults
    int kernel_size = 5;
    double sigma = 1.0;
    
    auto kernel_it = params.find("kernel_size");
    if (kernel_it != params.end()) {
        kernel_size = static_cast<int>(kernel_it->second);
        // ensure kernel size is odd
        if (kernel_size % 2 == 0) {
            kernel_size += 1;
        }
    }
    
    auto sigma_it = params.find("sigma");
    if (sigma_it != params.end()) {
        sigma = sigma_it->second;
    }
    
    // extract ROI from input image
    cv::Mat roi_image = extractROI(input, roi);
    cv::Mat output;
    
    // apply Gaussian blur
    cv::GaussianBlur(roi_image, output, cv::Size(kernel_size, kernel_size), sigma);
    
    // apply the processed ROI back to the original image
    return applyROI(input, output, roi);
} 