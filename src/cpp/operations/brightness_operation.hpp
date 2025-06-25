#pragma once

#include "base_operation.hpp"

/**
 * brightness adjustment operation
 * 
 * this operation adjusts the brightness of an image by multiplying
 * all pixel values by a factor.
 * 
 * parameters:
 * - "factor": brightness factor (1.0 = no change, >1.0 = brighter, <1.0 = darker)
 */
class BrightnessOperation : public Operation {
public:
    /**
     * execute the brightness adjustment
     * 
     * @param input the input image
     * @param roi region of interest to process
     * @param params map containing "factor" parameter
     * @return the brightness-adjusted image
     */
    cv::Mat execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) override;

    /**
     * get the operation name
     * 
     * @return "brightness"
     */
    std::string getName() const override { return "brightness"; }

    /**
     * validate parameters for brightness operation
     * 
     * @param parameters parameters to validate
     * @return true if parameters are valid, false otherwise
     */
    bool validateParameters(const std::map<std::string, double>& parameters) const override;
}; 