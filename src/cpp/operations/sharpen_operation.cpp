#include "sharpen_operation.hpp"
#include <iostream>

cv::Mat SharpenOperation::execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) {
    // Get parameters with defaults
    double strength = parameters.count("strength") ? parameters.at("strength") : 1.0;
    int kernel_size = static_cast<int>(parameters.count("kernel_size") ? parameters.at("kernel_size") : 5);
    
    // Ensure kernel size is odd
    if (kernel_size % 2 == 0) {
        kernel_size++;
    }
    
    cv::Mat result;
    
    // Apply ROI if specified
    if (roi.width > 0 && roi.height > 0) {
        cv::Rect roi_rect(roi.x, roi.y, roi.width, roi.height);
        cv::Mat roi_image = image(roi_rect).clone();
        
        // Create unsharp mask
        cv::Mat blurred;
        cv::GaussianBlur(roi_image, blurred, cv::Size(kernel_size, kernel_size), 0);
        
        // Apply unsharp mask
        cv::Mat sharpened;
        cv::addWeighted(roi_image, 1.0 + strength, blurred, -strength, 0, sharpened);
        
        // Copy back to result
        result = image.clone();
        sharpened.copyTo(result(roi_rect));
    } else {
        // Apply to full image
        cv::Mat blurred;
        cv::GaussianBlur(image, blurred, cv::Size(kernel_size, kernel_size), 0);
        
        // Apply unsharp mask
        cv::addWeighted(image, 1.0 + strength, blurred, -strength, 0, result);
    }
    
    std::cout << "    Sharpened image with strength " << strength 
              << " and kernel size " << kernel_size << std::endl;
    
    return result;
}

bool SharpenOperation::validateParameters(const std::map<std::string, double>& parameters) const {
    // Check strength parameter
    if (parameters.count("strength")) {
        double strength = parameters.at("strength");
        if (strength < 0.0 || strength > 2.0) {
            std::cerr << "Error: Sharpen strength must be between 0.0 and 2.0" << std::endl;
            return false;
        }
    }
    
    // Check kernel size parameter
    if (parameters.count("kernel_size")) {
        double kernel_size = parameters.at("kernel_size");
        if (kernel_size < 3 || kernel_size > 15) {
            std::cerr << "Error: Sharpen kernel size must be between 3 and 15" << std::endl;
            return false;
        }
    }
    
    return true;
} 