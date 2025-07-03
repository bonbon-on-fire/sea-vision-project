#pragma once

#include <string>
#include <vector>
#include <map>
#include "operations/hpp/base_operation.hpp"
#include <nlohmann/json.hpp>

/**
 * structure to hold operation configuration from JSON
 */
struct OperationConfig {
    std::string type;
    std::map<std::string, double> parameters;
    ROI roi;
};

/**
 * structure to hold complete pipeline configuration
 */
struct PipelineConfig {
    ROI global_roi;
    std::vector<OperationConfig> operations;
    std::string input_image;
    std::string output_image;
};

// json pipeline reader class
class PipelineReader {
public:
    // read pipeline configuration from json file
    static PipelineConfig readPipeline(const std::string& filename);

private:
    // parse roi from json object
    static ROI parseROI(const nlohmann::json& roi_json);
    
    // parse operation configuration from json object
    static OperationConfig parseOperation(const nlohmann::json& op_json);
}; 