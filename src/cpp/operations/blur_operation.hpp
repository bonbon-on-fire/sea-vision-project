#pragma once

#include "base_operation.hpp"

/**
 * blur operation
 * 
 * this operation applies Gaussian blur to an image to reduce noise
 * and smooth the image.
 * 
 * parameters:
 * - "kernel_size": size of the blur kernel (must be odd, default 5)
 * - "sigma": standard deviation for Gaussian blur (default 1.0)
 */
class BlurOperation : public Operation {
public:
    /**
     * execute the blur operation
     * 
     * @param input the input image
     * @param roi region of interest to process
     * @param params map containing "kernel_size" and "sigma" parameters
     * @return the blurred image
     */
    cv::Mat execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) override;

    /**
     * get the operation name
     * 
     * @return "blur"
     */
    std::string getName() const override { return "blur"; }

    /**
     * validate parameters for blur operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    bool validateParameters(const std::map<std::string, double>& parameters) const override;
}; 