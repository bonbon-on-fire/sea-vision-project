#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <map>

// region of interest structure
struct ROI {
    int x;
    int y;
    int width;
    int height;
    bool full_image;

    ROI(int x = 0, int y = 0, int width = 0, int height = 0, bool full_image = false)
        : x(x), y(y), width(width), height(height), full_image(full_image) {}
};

// roi utility functions
namespace ROITools {
    // extract roi from image
    cv::Mat extractROI(const cv::Mat& input, const ROI& roi);
    
    // apply processed roi back to original image
    cv::Mat applyROI(const cv::Mat& input, const cv::Mat& processed_roi, const ROI& roi);
}

// base class for all image processing operations
class Operation {
public:
    virtual ~Operation() = default;
 
    // public non-virtual interface - execute the operation on the input image
    cv::Mat execute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params);
 
    // public non-virtual interface - get the name/type of this operation
    std::string getName() const;
 
    // public non-virtual interface - validate parameters for this operation
    bool validateParameters(const std::map<std::string, double>& parameters) const;

protected:
    // pre-execution validation hook
    virtual bool preExecute(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) const;

    // post-execution validation hook
    virtual bool postExecute(const cv::Mat& input, const cv::Mat& output, const ROI& roi, const std::map<std::string, double>& params) const;

private:
    // private virtual interface - execute the operation implementation
    virtual cv::Mat executeImpl(const cv::Mat& input, const ROI& roi, const std::map<std::string, double>& params) = 0;

    // private virtual interface - get the name/type of this operation
    virtual std::string getNameImpl() const = 0;

    // private virtual interface - validate parameters for this operation
    virtual bool validateParametersImpl(const std::map<std::string, double>& parameters) const = 0;
}; 