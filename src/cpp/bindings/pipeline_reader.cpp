#include "pipeline_reader.hpp"
#include "../../../include/json-develop/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

PipelineConfig PipelineReader::readPipeline(const std::string& filename) {
    // open and read the json file
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open pipeline file: " + filename);
    }
    
    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Invalid JSON in pipeline file: " + std::string(e.what()));
    }
    
    PipelineConfig config;
    
    // parse global roi (optional, defaults to full image)
    if (j.contains("roi")) {
        config.global_roi = parseROI(j["roi"]);
    } else {
        config.global_roi = ROI(0, 0, 0, 0); // Full image
    }
    
    // parse operations array
    if (!j.contains("operations") || !j["operations"].is_array()) {
        throw std::runtime_error("Pipeline must contain 'operations' array");
    }
    
    for (const auto& op_json : j["operations"]) {
        config.operations.push_back(parseOperation(op_json));
    }
    
    // parse input/output image paths (optional)
    if (j.contains("input_image")) {
        config.input_image = j["input_image"];
    }
    
    if (j.contains("output_image")) {
        config.output_image = j["output_image"];
    }
    
    return config;
}

bool PipelineReader::validatePipeline(const PipelineConfig& config) {
    // check if we have at least one operation
    if (config.operations.empty()) {
        std::cerr << "Error: Pipeline must contain at least one operation" << std::endl;
        return false;
    }
    
    // get list of supported operations
    auto supported_ops = getSupportedOperations();
    
    // validate each operation
    for (size_t i = 0; i < config.operations.size(); ++i) {
        const auto& op = config.operations[i];
        
        // check if operation type is supported
        bool supported = false;
        for (const auto& supported_op : supported_ops) {
            if (op.type == supported_op) {
                supported = true;
                break;
            }
        }
        
        if (!supported) {
            std::cerr << "Error: Operation " << i << " has unsupported type: " << op.type << std::endl;
            return false;
        }
        
        // validate operation-specific parameters
        if (op.type == "brightness") {
            if (op.parameters.find("factor") == op.parameters.end()) {
                std::cerr << "Error: Brightness operation requires 'factor' parameter" << std::endl;
                return false;
            }
        } else if (op.type == "blur") {
            if (op.parameters.find("kernel_size") == op.parameters.end()) {
                std::cerr << "Error: Blur operation requires 'kernel_size' parameter" << std::endl;
                return false;
            }
            if (op.parameters.find("sigma") == op.parameters.end()) {
                std::cerr << "Error: Blur operation requires 'sigma' parameter" << std::endl;
                return false;
            }
        }
    }
    
    return true;
}

std::vector<std::string> PipelineReader::getSupportedOperations() {
    return {"brightness", "blur", "crop", "sharpen", "contrast"};
}

ROI PipelineReader::parseROI(const json& roi_json) {
    ROI roi;
    
    if (roi_json.contains("x")) {
        roi.x = roi_json["x"];
    }
    if (roi_json.contains("y")) {
        roi.y = roi_json["y"];
    }
    if (roi_json.contains("width")) {
        roi.width = roi_json["width"];
    }
    if (roi_json.contains("height")) {
        roi.height = roi_json["height"];
    }
    
    return roi;
}

OperationConfig PipelineReader::parseOperation(const json& op_json) {
    OperationConfig op;
    
    // parse operation type
    if (!op_json.contains("type") || !op_json["type"].is_string()) {
        throw std::runtime_error("Operation must have 'type' field");
    }
    op.type = op_json["type"];
    
    // parse parameters
    if (op_json.contains("parameters") && op_json["parameters"].is_object()) {
        for (const auto& [key, value] : op_json["parameters"].items()) {
            if (value.is_number()) {
                op.parameters[key] = value.get<double>();
            }
        }
    }
    
    // parse roi (optional, will use global roi if not specified)
    if (op_json.contains("roi")) {
        op.roi = parseROI(op_json["roi"]);
    } else {
        op.roi = ROI(0, 0, 0, 0); // will be overridden by global roi
    }
    
    return op;
} 