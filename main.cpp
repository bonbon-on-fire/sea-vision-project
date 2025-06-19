#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>

// include operation classes
#include "src/cpp/operations/base_operation.hpp"
#include "src/cpp/operations/brightness_operation.hpp"
#include "src/cpp/operations/blur_operation.hpp"

/**
 * main function that demonstrates the operation system with parameters
 * 
 * this function:
 * 1. loads an image from the data directory
 * 2. verifies the image was loaded successfully
 * 3. creates a brightness operation and sets parameters
 * 4. applies the operation and saves the result
 * 5. provides detailed logging for debugging
 * 
 * @return 0 on success, -1 on failure
 */
int main() {
    std::cout << "Starting SEA Vision image processing..." << std::endl;
    
    // load image
    std::cout << "Loading image..." << std::endl;
    cv::Mat image = cv::imread("data/input.jpg");
    
    if (image.empty()) {
        std::cout << "Error: Could not load image 'data/input.jpg'" << std::endl;
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        return -1;
    }
    
    std::cout << "Successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
    
    // create operations
    BrightnessOperation brightness_op;
    BlurOperation blur_op;
    
    // test brightness operation on full image
    std::cout << "Testing brightness operation (full image)..." << std::endl;
    std::map<std::string, double> brightness_params;
    brightness_params["factor"] = 1.5; // increase brightness by 50%
    ROI full_roi(0, 0, 0, 0); // full image
    cv::Mat brightness_result = brightness_op.execute(image, full_roi, brightness_params);
    cv::imwrite("data/output_step5_brightness_full.jpg", brightness_result);
    std::cout << "Brightness (full image) completed. Saved as 'data/output_step5_brightness_full.jpg'" << std::endl;

    // test blur operation on full image
    std::cout << "Testing blur operation (full image)..." << std::endl;
    std::map<std::string, double> blur_params;
    blur_params["kernel_size"] = 5;
    blur_params["sigma"] = 1.0;
    cv::Mat blur_result = blur_op.execute(image, full_roi, blur_params);
    cv::imwrite("data/output_step5_blur_full.jpg", blur_result);
    std::cout << "Blur (full image) completed. Saved as 'data/output_step5_blur_full.jpg'" << std::endl;

    // test brightness operation on ROI
    ROI roi(image.cols / 4, image.rows / 4, image.cols / 2, image.rows / 2); // center box
    std::cout << "Testing brightness operation (ROI)..." << std::endl;
    cv::Mat brightness_roi_result = brightness_op.execute(image, roi, brightness_params);
    cv::imwrite("data/output_step5_brightness_roi.jpg", brightness_roi_result);
    std::cout << "Brightness (ROI) completed. Saved as 'data/output_step5_brightness_roi.jpg'" << std::endl;

    // test blur operation on ROI
    std::cout << "Testing blur operation (ROI)..." << std::endl;
    cv::Mat blur_roi_result = blur_op.execute(image, roi, blur_params);
    cv::imwrite("data/output_step5_blur_roi.jpg", blur_roi_result);
    std::cout << "Blur (ROI) completed. Saved as 'data/output_step5_blur_roi.jpg'" << std::endl;

    std::cout << "All operations completed successfully!" << std::endl;
    return 0;
}