#include "crop_operation.hpp"
#include <iostream>

cv::Mat CropOperation::execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) {
    // Get crop parameters with defaults
    int x = static_cast<int>(parameters.count("x") ? parameters.at("x") : 0);
    int y = static_cast<int>(parameters.count("y") ? parameters.at("y") : 0);
    int width = static_cast<int>(parameters.count("width") ? parameters.at("width") : image.cols - x);
    int height = static_cast<int>(parameters.count("height") ? parameters.at("height") : image.rows - y);
    
    // Validate crop region
    if (x < 0 || y < 0 || x >= image.cols || y >= image.rows) {
        std::cerr << "Error: Crop coordinates out of bounds" << std::endl;
        return image.clone();
    }
    
    if (width <= 0 || height <= 0 || x + width > image.cols || y + height > image.rows) {
        std::cerr << "Error: Crop dimensions invalid" << std::endl;
        return image.clone();
    }
    
    // Create crop region
    cv::Rect crop_region(x, y, width, height);
    
    // Perform crop
    cv::Mat cropped = image(crop_region).clone();
    
    std::cout << "    Cropped image from " << image.cols << "x" << image.rows 
              << " to " << cropped.cols << "x" << cropped.rows << std::endl;
    
    return cropped;
}

bool CropOperation::validateParameters(const std::map<std::string, double>& parameters) const {
    // Check for required parameters
    if (parameters.count("x") && parameters.at("x") < 0) {
        std::cerr << "Error: Crop x coordinate must be non-negative" << std::endl;
        return false;
    }
    
    if (parameters.count("y") && parameters.at("y") < 0) {
        std::cerr << "Error: Crop y coordinate must be non-negative" << std::endl;
        return false;
    }
    
    if (parameters.count("width") && parameters.at("width") <= 0) {
        std::cerr << "Error: Crop width must be positive" << std::endl;
        return false;
    }
    
    if (parameters.count("height") && parameters.at("height") <= 0) {
        std::cerr << "Error: Crop height must be positive" << std::endl;
        return false;
    }
    
    return true;
} 