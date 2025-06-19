//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <filesystem>

///**
 //* main function that demonstrates basic image loading and saving
 //* 
 //* this function:
 //* 1. loads an image from the data directory
 //* 2. verifies the image was loaded successfully
 //* 3. saves a copy of the image to the output directory
 //* 4. provides detailed logging for debugging
 //* 
 //* @return 0 on success, -1 on failure
 //*/
//int main_step1() {
    //std::cout << "Starting program..." << std::endl;
    
    //// load image
    //std::cout << "Attempting to load image..." << std::endl;
    //cv::Mat image = cv::imread("../../data/input.jpg");
    
    //// check if image loading was successful
    //if (image.empty()) {
        //std::cout << "Error: Could not load image 'data/input.jpg'" << std::endl;
        //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        //return -1;
    //}
    
    //// display image information for verification
    //std::cout << "Successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
    
    //// save the same image (just to test)
    //std::cout << "Attempting to save image..." << std::endl;
    //cv::imwrite("../../data/output_step1_copy.jpg", image);
    
    //std::cout << "Successfully saved image as 'data/output_step1_copy.jpg'" << std::endl;
    //std::cout << "Program completed successfully!" << std::endl;
    
    //return 0;
//} 