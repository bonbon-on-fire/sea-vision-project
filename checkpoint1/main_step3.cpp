#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <map>
#include "brightness_operation.hpp"

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
int main_step3() {
    std::cout << "Starting program..." << std::endl;
    
    // load image
    std::cout << "Attempting to load image..." << std::endl;
    cv::Mat image = cv::imread("../../data/input.jpg");
    
    // check if image loading was successful
    if (image.empty()) {
        std::cout << "Error: Could not load image 'data/input.jpg'" << std::endl;
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        return -1;
    }
    
    // display image information for verification
    std::cout << "Successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
    
    // create brightness operation
    std::cout << "Creating brightness operation..." << std::endl;
    BrightnessOperation brightness_op;
    
    // set parameters
    std::map<std::string, double> params;
    params["factor"] = 1.5; // increase brightness by 50%
    std::cout << "Set brightness factor: " << params["factor"] << std::endl;
    
    // apply the operation
    std::cout << "Applying brightness operation..." << std::endl;
    cv::Mat adjusted_image = brightness_op.execute(image, params);
    std::cout << "Brightness operation applied successfully!" << std::endl;
    
    // save the adjusted image
    std::cout << "Attempting to save image..." << std::endl;
    cv::imwrite("../../data/output_step3_operation.jpg", adjusted_image);
    
    std::cout << "Successfully saved image as 'data/output_step3_operation.jpg'" << std::endl;
    std::cout << "Program completed successfully!" << std::endl;
    
    return 0;
}