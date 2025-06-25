#pragma once

#include <string>
#include <vector>
#include <map>
#include "../operations/base_operation.hpp"
#include "../../../include/json-develop/single_include/nlohmann/json.hpp"

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

/**
 * json pipeline reader class
 * 
 * This class reads pipeline configurations from JSON files
 * and converts them into C++ data structures.
 */
class PipelineReader {
public:
    /**
     * read pipeline configuration from json file
     * 
     * @param filename path to the JSON configuration file
     * @return PipelineConfig object containing the parsed configuration
     * @throws std::runtime_error if file cannot be read or JSON is invalid
     */
    static PipelineConfig readPipeline(const std::string& filename);
    
    /**
     * validate pipeline configuration
     * 
     * @param config the pipeline configuration to validate
     * @return true if configuration is valid, false otherwise
     */
    static bool validatePipeline(const PipelineConfig& config);
    
    /**
     * get list of supported operation types
     * 
     * @return vector of supported operation type names
     */
    static std::vector<std::string> getSupportedOperations();

private:
    /**
     * parse roi from json object
     * 
     * @param roi_json JSON object containing ROI data
     * @return ROI struct
     */
    static ROI parseROI(const nlohmann::json& roi_json);
    
    /**
     * parse operation configuration from json object
     * 
     * @param op_json JSON object containing operation data
     * @return OperationConfig struct
     */
    static OperationConfig parseOperation(const nlohmann::json& op_json);
}; 