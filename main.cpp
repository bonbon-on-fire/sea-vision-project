#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>

// include operation classes
#include "src/cpp/operations/base_operation.hpp"
#include "src/cpp/operations/brightness_operation.hpp"
#include "src/cpp/operations/blur_operation.hpp"

// include new pipeline system
#include "src/cpp/bindings/pipeline_reader.hpp"
#include "src/cpp/bindings/operation_factory.hpp"

/**
 * main function that demonstrates JSON-driven pipeline execution
 * 
 * usage: ./step <pipeline.json> <input_image> <output_image>
 * 
 * this function:
 * 1. reads pipeline configuration from JSON file
 * 2. loads the input image
 * 3. creates operations dynamically based on JSON
 * 4. executes the pipeline in order
 * 5. saves the result
 * 
 * @return 0 on success, -1 on failure
 */
int main(int argc, char* argv[]) {
    // check command line arguments
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <pipeline.json> <input_image> <output_image>" << std::endl;
        std::cout << "Example: " << argv[0] << " pipeline.json data/input.jpg data/output.jpg" << std::endl;
        return -1;
    }
    
    std::string pipeline_file = argv[1];
    std::string input_image = argv[2];
    std::string output_image = argv[3];
    
    std::cout << "Starting SEA Vision JSON-driven pipeline..." << std::endl;
    std::cout << "Pipeline config: " << pipeline_file << std::endl;
    std::cout << "Input image: " << input_image << std::endl;
    std::cout << "Output image: " << output_image << std::endl;
    
    try {
        // read pipeline configuration from JSON
        std::cout << "Reading pipeline configuration..." << std::endl;
        PipelineConfig config = PipelineReader::readPipeline(pipeline_file);
        
        // validate pipeline configuration
        std::cout << "Validating pipeline configuration..." << std::endl;
        if (!PipelineReader::validatePipeline(config)) {
            std::cerr << "Error: Invalid pipeline configuration" << std::endl;
            return -1;
        }
        
        // load input image
        std::cout << "Loading input image..." << std::endl;
        cv::Mat image = cv::imread(input_image);
        if (image.empty()) {
            std::cerr << "Error: Could not load image '" << input_image << "'" << std::endl;
            return -1;
        }
        
        std::cout << "Successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
        
        // execute pipeline
        std::cout << "Executing pipeline with " << config.operations.size() << " operations..." << std::endl;
        cv::Mat result = image.clone();
        
        for (size_t i = 0; i < config.operations.size(); ++i) {
            const auto& op_config = config.operations[i];
            
            std::cout << "  Step " << (i + 1) << ": " << op_config.type << std::endl;
            
            // create operation using factory
            auto operation = OperationFactory::createOperation(op_config.type);
            if (!operation) {
                std::cerr << "Error: Could not create operation of type '" << op_config.type << "'" << std::endl;
                return -1;
            }
            
            // determine ROI to use (operation-specific or global)
            ROI roi_to_use = (op_config.roi.width == 0 && op_config.roi.height == 0) 
                           ? config.global_roi 
                           : op_config.roi;
            
            // execute operation
            result = operation->execute(result, roi_to_use, op_config.parameters);
            
            std::cout << "    Completed successfully" << std::endl;
        }
        
        // save result
        std::cout << "Saving result..." << std::endl;
        if (!cv::imwrite(output_image, result)) {
            std::cerr << "Error: Could not save image to '" << output_image << "'" << std::endl;
            return -1;
        }
        
        std::cout << "Pipeline completed successfully!" << std::endl;
        std::cout << "Output saved to: " << output_image << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}