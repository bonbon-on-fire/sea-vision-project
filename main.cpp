#include <iostream>
#include <string>

// opencv
#include <opencv2/opencv.hpp>

// operation classes
#include "operations/hpp/base_operation.hpp"
#include "operations/hpp/operations.hpp"

// pipeline system
#include "bindings/hpp/pipeline_reader.hpp"
#include "bindings/hpp/operation_factory.hpp"

// main function for json-driven pipeline execution
int main(int argc, char* argv[]) {
    std::cout << "sea_vision.exe started" << std::endl;

    // check command line arguments
    if (argc != 4) {
        std::cout << "usage: " << argv[0] << " <pipeline.json> <input_image> <output_image>" << std::endl;
        std::cout << "example: " << argv[0] << " tests/json/test_pipeline.json data/input.jpg output.jpg" << std::endl;
        return -1;
    }

    // get command line arguments
    std::string pipeline_file = argv[1];
    std::string input_image = argv[2];
    std::string output_image = argv[3];
    
    std::cout << "starting sea vision json-driven pipeline..." << std::endl;
    std::cout << "pipeline config: " << pipeline_file << std::endl;
    std::cout << "input image: " << input_image << std::endl;
    std::cout << "output image: " << output_image << std::endl;
    
    // execute pipeline
    try {
        // read pipeline configuration from json
        std::cout << "reading pipeline configuration..." << std::endl;
        PipelineConfig config = PipelineReader::readPipeline(pipeline_file);
        
        // load input image
        std::cout << "loading input image..." << std::endl;
        cv::Mat image = cv::imread(input_image);
        if (image.empty()) {
            std::cerr << "error: could not load image '" << input_image << "'" << std::endl;
            return -1;
        }
        
        std::cout << "successfully loaded image with size: " << image.cols << "x" << image.rows << std::endl;
        
        // execute pipeline
        std::cout << "executing pipeline with " << config.operations.size() << " operations..." << std::endl;
        cv::Mat result = image.clone();
        
        // execute operations
        for (size_t i = 0; i < config.operations.size(); ++i) {
            const auto& op_config = config.operations[i];
            
            std::cout << "  step " << (i + 1) << ": " << op_config.type << std::endl;
            
            // create operation using factory
            auto operation = OperationFactory::createOperation(op_config.type);
            if (!operation) {
                std::cerr << "error: could not create operation of type '" << op_config.type << "'" << std::endl;
                return -1;
            }
            
            // determine roi to use
            ROI roi_to_use = (op_config.roi.full_image) 
                           ? config.global_roi 
                           : op_config.roi;
            
            // execute operation
            result = operation->execute(result, roi_to_use, op_config.parameters);
            
            std::cout << "operation " << (i + 1) << " completed successfully!!" << std::endl;
        }
        
        // save result
        std::cout << "saving result..." << std::endl;
        if (!cv::imwrite(output_image, result)) {
            std::cerr << "error: could not save image to '" << output_image << "'" << std::endl;
            return -1;
        }
    
        std::cout << "pipeline completed successfully!!" << std::endl;
        std::cout << "output saved to: " << output_image << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}