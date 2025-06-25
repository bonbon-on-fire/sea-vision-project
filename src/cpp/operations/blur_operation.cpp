#include "blur_operation.hpp"
#include <iostream>

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

bool BlurOperation::validateParameters(const std::map<std::string, double>& parameters) const {
    // check kernel size
    if (parameters.count("kernel_size")) {
        double kernel_size = parameters.at("kernel_size");
        if (kernel_size < 3 || kernel_size > 31) {
            std::cerr << "Error: Blur kernel size must be between 3 and 31" << std::endl;
            return false;
        }
    }
    
    // check sigma
    if (parameters.count("sigma")) {
        double sigma = parameters.at("sigma");
        if (sigma < 0.1 || sigma > 10.0) {
            std::cerr << "Error: Blur sigma must be between 0.1 and 10.0" << std::endl;
            return false;
        }
    }
    
    return true;
} 