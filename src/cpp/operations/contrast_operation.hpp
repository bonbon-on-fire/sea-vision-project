#pragma once

#include "base_operation.hpp"
#include <opencv2/opencv.hpp>

/**
 * Contrast Operation class
 * 
 * This operation adjusts the contrast of an image.
 * Order matters because contrast affects how brightness operations work.
 * 
 * Parameters:
 * - factor: contrast factor (0.0 to 3.0, default: 1.0)
 * - brightness_offset: brightness offset (-100 to 100, default: 0)
 */
class ContrastOperation : public Operation {
public:
    ContrastOperation() = default;
    ~ContrastOperation() = default;
    
    /**
     * Execute the contrast operation
     * 
     * @param image input image
     * @param roi region of interest
     * @param parameters contrast parameters (factor, brightness_offset)
     * @return contrast-adjusted image
     */
    cv::Mat execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) override;
    
    /**
     * Get operation name
     * 
     * @return operation name
     */
    std::string getName() const override { return "contrast"; }
    
    /**
     * Validate parameters for contrast operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    bool validateParameters(const std::map<std::string, double>& parameters) const override;
}; 