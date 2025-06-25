#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "../operations/base_operation.hpp"

// Forward declarations
class BrightnessOperation;
class BlurOperation;

/**
 * Operation Factory class
 * 
 * This class creates operation objects based on type strings.
 * It uses the Factory pattern to dynamically instantiate operations.
 */
class OperationFactory {
public:
    /**
     * Create an operation based on type string
     * 
     * @param type the operation type (e.g., "brightness", "blur")
     * @return unique_ptr to the created operation, or nullptr if type is not supported
     */
    static std::unique_ptr<Operation> createOperation(const std::string& type);
    
    /**
     * Check if an operation type is supported
     * 
     * @param type the operation type to check
     * @return true if the operation type is supported, false otherwise
     */
    static bool isSupported(const std::string& type);
    
    /**
     * Get list of all supported operation types
     * 
     * @return vector of supported operation type names
     */
    static std::vector<std::string> getSupportedTypes();

private:
    // Map of operation type strings to creation functions
    using OperationCreator = std::unique_ptr<Operation>(*)();
    static const std::map<std::string, OperationCreator> creators;
    
    // Static creation functions for each operation type
    static std::unique_ptr<Operation> createBrightness();
    static std::unique_ptr<Operation> createBlur();
}; 