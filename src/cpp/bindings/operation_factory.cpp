#include "operation_factory.hpp"
#include "../operations/brightness_operation.hpp"
#include "../operations/blur_operation.hpp"

// Define the static creators map
const std::map<std::string, OperationFactory::OperationCreator> OperationFactory::creators = {
    {"brightness", &OperationFactory::createBrightness},
    {"blur", &OperationFactory::createBlur}
};

std::unique_ptr<Operation> OperationFactory::createOperation(const std::string& type) {
    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second(); // Call the creation function
    }
    return nullptr; // Type not supported
}

bool OperationFactory::isSupported(const std::string& type) {
    return creators.find(type) != creators.end();
}

std::vector<std::string> OperationFactory::getSupportedTypes() {
    std::vector<std::string> types;
    for (const auto& [type, creator] : creators) {
        types.push_back(type);
    }
    return types;
}

std::unique_ptr<Operation> OperationFactory::createBrightness() {
    return std::make_unique<BrightnessOperation>();
}

std::unique_ptr<Operation> OperationFactory::createBlur() {
    return std::make_unique<BlurOperation>();
}
