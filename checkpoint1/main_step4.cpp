//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <filesystem>
//#include <map>
//#include <string>

//// Include our operation classes
//#include "src/cpp/operations/base_operation.hpp"
//#include "src/cpp/operations/brightness_operation.hpp"
//#include "src/cpp/operations/blur_operation.hpp"

///**
 //* main function that demonstrates the operation system with parameters
 //* 
 //* this function:
 //* 1. loads an image from the data directory
 //* 2. verifies the image was loaded successfully
 //* 3. creates a brightness operation and sets parameters
 //* 4. applies the operation and saves the result
 //* 5. provides detailed logging for debugging
 //* 
 //* @return 0 on success, -1 on failure
 //*/
//int main_step4() {
    //std::cout << "Starting SEA Vision image processing..." << std::endl;
    
    //// load image
    //std::cout << "Loading image..." << std::endl;
    //cv::Mat image = cv::imread("data/input.jpg");
    
    //if (image.empty()) {
        //std::cout << "Error: Could not load image 'data/input.jpg'" << std::endl;
        //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        //return -1;
    //}
    
    //std::cout << "Successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
    
    //// create operations
    //BrightnessOperation brightness_op;
    //BlurOperation blur_op;
    
    //// test brightness operation
    //std::cout << "Testing brightness operation..." << std::endl;
    //std::map<std::string, double> brightness_params;
    //brightness_params["factor"] = 1.5; // increase brightness by 50%
    
    //cv::Mat brightness_result = brightness_op.execute(image, brightness_params);
    //cv::imwrite("data/output_brightness.jpg", brightness_result);
    //std::cout << "Brightness operation completed. Saved as 'data/output_brightness.jpg'" << std::endl;
    
    //// test blur operation
    //std::cout << "Testing blur operation..." << std::endl;
    //std::map<std::string, double> blur_params;
    //blur_params["kernel_size"] = 5;
    //blur_params["sigma"] = 1.0;
    
    //cv::Mat blur_result = blur_op.execute(image, blur_params);
    //cv::imwrite("data/output_step4_blur.jpg", blur_result);
    //std::cout << "Blur operation completed. Saved as 'data/output_step4_blur.jpg'" << std::endl;
    
    //// test combined operations (brightness then blur)
    //std::cout << "Testing combined operations..." << std::endl;
    //cv::Mat combined_result = blur_op.execute(brightness_result, blur_params);
    //cv::imwrite("data/output_step4_combined.jpg", combined_result);
    //std::cout << "Combined operations completed. Saved as 'data/output_step4_combined.jpg'" << std::endl;
    
    //std::cout << "All operations completed successfully!" << std::endl;
    //return 0;
//}