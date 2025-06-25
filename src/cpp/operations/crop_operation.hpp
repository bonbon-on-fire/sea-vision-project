#pragma once

#include "base_operation.hpp"
#include <opencv2/opencv.hpp>

/**
 * Crop Operation class
 * 
 * This operation crops an image to a specified region.
 * Order matters because cropping reduces image size, affecting all subsequent operations.
 * 
 * Parameters:
 * - x: starting x coordinate (default: 0)
 * - y: starting y coordinate (default: 0) 
 * - width: crop width (default: full width)
 * - height: crop height (default: full height)
 */
class CropOperation : public Operation {
public:
    CropOperation() = default;
    ~CropOperation() = default;
    
    /**
     * Execute the crop operation
     * 
     * @param image input image
     * @param roi region of interest (ignored for crop, uses parameters instead)
     * @param parameters crop parameters (x, y, width, height)
     * @return cropped image
     */
    cv::Mat execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) override;
    
    /**
     * Get operation name
     * 
     * @return operation name
     */
    std::string getName() const override { return "crop"; }
    
    /**
     * Validate parameters for crop operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    bool validateParameters(const std::map<std::string, double>& parameters) const override;
}; 