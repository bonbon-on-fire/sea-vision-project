#pragma once

#include "base_operation.hpp"
#include <opencv2/opencv.hpp>

/**
 * sharpen operation class
 * 
 * this operation sharpens an image by enhancing edges and details.
 * order matters because sharpening works differently on blurred vs sharp images.
 * 
 * parameters:
 * - strength: sharpening strength (0.0 to 2.0, default: 1.0)
 * - kernel_size: kernel size for unsharp mask (default: 5)
 */
class SharpenOperation : public Operation {
public:
    SharpenOperation() = default;
    ~SharpenOperation() = default;
    
    /**
     * execute the sharpen operation
     * 
     * @param image input image
     * @param roi region of interest
     * @param parameters sharpen parameters (strength, kernel_size)
     * @return sharpened image
     */
    cv::Mat execute(const cv::Mat& image, const ROI& roi, const std::map<std::string, double>& parameters) override;
    
    /**
     * get operation name
     * 
     * @return operation name
     */
    std::string getName() const override { return "sharpen"; }
    
    /**
     * validate parameters for sharpen operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    bool validateParameters(const std::map<std::string, double>& parameters) const override;
}; 