# Workflow:
```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   User Input    │    │  Python Layer   │    │   C++ Backend   │
│                 │    │                 │    │                 │
│ 1. Python CLI   │───▶│ 2. Pipeline     │───▶│ 3. Image        │
│    or Script    │    │    Builder      │    │    Processing   │
│                 │    │                 │    │                 │
│ OR              │    │                 │    │                 │
│                 │    │                 │    │                 │
│ 1. Manual JSON  │────┼─────────────────┼───▶│                 │
│    File         │    │                 │    │                 │
└─────────────────┘    └─────────────────┘    └─────────────────┘
                                │                        │
                                ▼                        ▼
                       ┌─────────────────┐    ┌─────────────────┐
                       │  Generated      │    │  Processed      │
                       │  JSON Config    │    │  Image Output   │
                       └─────────────────┘    └─────────────────┘
```

# The Big Picture:
The system reads a JSON configuration file that defines a sequence of image processing operations. Each operation has parameters (like blur strength, brightness factor, etc.). The C++ pipeline loads your image, applies each operation in order, and saves the result.

# How to Use

Create a JSON file that defines your pipeline:
```json
{
  "global_roi": {"x": 0, "y": 0, "width": 0, "height": 0},
  "operations": [
    {
      "type": "brightness",
      "parameters": {"factor": 1.2}
    },
    {
      "type": "blur",
      "parameters": {"kernel_size": 5, "sigma": 1.0}
    }
  ]
}
```

Then run:
```bash
./sea_vision pipeline.json input.jpg output.jpg
```

# Project Structure

```
sea_vision_project/
├── main.cpp                 # Main entry point - orchestrates the pipeline
├── src/
│   ├── cpp/
│   │   ├── operations/      # Individual operation implementations
│   │   │   ├── base_operation.hpp
│   │   │   ├── brightness_operation.cpp/hpp
│   │   │   ├── blur_operation.cpp/hpp
│   │   │   ├── crop_operation.cpp/hpp
│   │   │   ├── sharpen_operation.cpp/hpp
│   │   │   └── contrast_operation.cpp/hpp
│   │   └── bindings/        # Pipeline system components
│   │       ├── pipeline_reader.cpp/hpp    # Reads and validates JSON
│   │       └── operation_factory.cpp/hpp  # Creates operation objects
│   └── python/              # Python interface (Phase 2)
│       ├── operation_definitions.py       # Operation metadata
│       ├── operation_sequence.py          # Pipeline builder
│       ├── utils.py                       # Helper functions
│       └── test_operation.py              # Python tests
├── tests/
│   ├── cpp/                 # C++ unit tests
│   ├── python/              # Python tests
│   └── json/                # Test pipeline configurations
├── data/                    # Sample images and outputs
└── CMakeLists.txt           # Build configuration
```

# Files

## C++ Files:
- **`main.cpp`**: Entry point that reads JSON, loads image, executes pipeline, saves result
- **`pipeline_reader.cpp/hpp`**: Parses JSON files and validates pipeline configurations
- **`operation_factory.cpp/hpp`**: Creates operation objects dynamically based on type names
- **`base_operation.hpp`**: Abstract base class that all operations inherit from
- **`*_operation.cpp/hpp`**: Individual operation implementations (brightness, blur, etc.)

## Test Files:
- **`test_*.json`**: Sample pipeline configurations demonstrating different effects
- **`test_operations.cpp`**: C++ unit tests for individual operations
- **`test_sequence.py`**: Python tests for pipeline building

# Status 

## Completed:
- C++ pipeline system with JSON configuration
- 5 core operations (brightness, blur, crop, sharpen, contrast)
- Factory pattern for dynamic operation creation
- Parameter validation and error handling
- Comprehensive test suite
- Order-dependent operation effects

## In Progress:
- Python interface for interactive pipeline building
- JSON generation from Python
- Enhanced parameter validation
- User-friendly CLI tools