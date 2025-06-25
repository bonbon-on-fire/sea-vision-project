#include "contrast_operation.hpp"
#include <iostream>

cv::Mat ContrastOperation::execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) {
    // Get parameters with defaults
    double factor = parameters.count("factor") ? parameters.at("factor") : 1.0;
    double brightness_offset = parameters.count("brightness_offset") ? parameters.at("brightness_offset") : 0.0;
    
    cv::Mat result;
    
    // Apply ROI if specified
    if (roi.width > 0 && roi.height > 0) {
        cv::Rect roi_rect(roi.x, roi.y, roi.width, roi.height);
        cv::Mat roi_image = image(roi_rect).clone();
        
        // Apply contrast and brightness adjustment
        roi_image.convertTo(roi_image, -1, factor, brightness_offset);
        
        // Copy back to result
        result = image.clone();
        roi_image.copyTo(result(roi_rect));
    } else {
        // Apply to full image
        image.convertTo(result, -1, factor, brightness_offset);
    }
    
    std::cout << "    Adjusted contrast with factor " << factor 
              << " and brightness offset " << brightness_offset << std::endl;
    
    return result;
}

bool ContrastOperation::validateParameters(const std::map<std::string, double>& parameters) const {
    // Check contrast factor
    if (parameters.count("factor")) {
        double factor = parameters.at("factor");
        if (factor < 0.0 || factor > 3.0) {
            std::cerr << "Error: Contrast factor must be between 0.0 and 3.0" << std::endl;
            return false;
        }
    }
    
    // Check brightness offset
    if (parameters.count("brightness_offset")) {
        double offset = parameters.at("brightness_offset");
        if (offset < -100.0 || offset > 100.0) {
            std::cerr << "Error: Brightness offset must be between -100 and 100" << std::endl;
            return false;
        }
    }
    
    return true;
} 