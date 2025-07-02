#include "bindings/hpp/pipeline_reader.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

PipelineConfig PipelineReader::readPipeline(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("could not open pipeline file: " + filename);
    }
    
    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("invalid JSON in pipeline file: " + std::string(e.what()));
    }
    
    PipelineConfig config;
    
    // parse global roi
    if (j.contains("roi")) {
        config.global_roi = parseROI(j["roi"]);
    } else {
        config.global_roi = ROI(0, 0, 0, 0, true);
    }
    
    // parse operations array
    if (!j.contains("operations") || !j["operations"].is_array()) {
        throw std::runtime_error("pipeline must contain 'operations' array");
    }
    
    for (const auto& op_json : j["operations"]) {
        config.operations.push_back(parseOperation(op_json));
    }
    
    // parse input/output image paths
    if (j.contains("input_image")) {
        config.input_image = j["input_image"];
    }
    
    if (j.contains("output_image")) {
        config.output_image = j["output_image"];
    }
    
    return config;
}

ROI PipelineReader::parseROI(const json& roi_json) {
    ROI roi;
    
    roi.x = roi_json.value("x", 0);
    roi.y = roi_json.value("y", 0);
    roi.width = roi_json.value("width", 0);
    roi.height = roi_json.value("height", 0);
    
    roi.full_image = (roi.width == 0 && roi.height == 0);
    
    return roi;
}

OperationConfig PipelineReader::parseOperation(const json& op_json) {
    OperationConfig op;
    
    // parse operation type
    if (!op_json.contains("type") || !op_json["type"].is_string()) {
        throw std::runtime_error("operation must have 'type' field");
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
    
    // parse roi
    if (op_json.contains("roi")) {
        op.roi = parseROI(op_json["roi"]);
    } else {
        op.roi = ROI(0, 0, 0, 0, true);
    }
    
    return op;
} 