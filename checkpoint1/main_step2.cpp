#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

/**
 * adjusts the brightness of an image
 * 
 * @param input the input image
 * @param factor brightness factor (1.0 = no change, >1.0 = brighter, <1.0 = darker)
 * @return the brightness-adjusted image
 */
cv::Mat adjustBrightness(const cv::Mat& input, double factor) {
    cv::Mat output;
    
    // convert to float for processing
    cv::Mat float_img;
    input.convertTo(float_img, CV_32F);
    
    // apply brightness adjustment
    float_img *= factor;
    
    // convert back to original type
    float_img.convertTo(output, input.type());
    
    // ensure values are clamped to valid range
    cv::threshold(output, output, 255, 255, cv::THRESH_TRUNC);
    cv::threshold(output, output, 0, 0, cv::THRESH_TOZERO);
    
    return output;
}

/**
 * main function that demonstrates basic image loading and saving
 * 
 * this function:
 * 1. loads an image from the data directory
 * 2. verifies the image was loaded successfully
 * 3. applies brightness adjustment
 * 4. saves the result to the output directory
 * 5. provides detailed logging for debugging
 * 
 * @return 0 on success, -1 on failure
 */
int main_step2() {
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
    
    // apply brightness adjustment
    std::cout << "Applying brightness adjustment..." << std::endl;
    double brightness_factor = 1.5; // increase brightness by 50%
    cv::Mat adjusted_image = adjustBrightness(image, brightness_factor);
    std::cout << "Brightness adjustment applied with factor: " << brightness_factor << std::endl;
    
    // save the adjusted image
    std::cout << "Attempting to save image..." << std::endl;
    cv::imwrite("../../data/output_step2_brightness.jpg", adjusted_image);
    
    std::cout << "Successfully saved image as 'data/output_step2_brightness.jpg'" << std::endl;
    std::cout << "Program completed successfully!" << std::endl;
    
    return 0;
}