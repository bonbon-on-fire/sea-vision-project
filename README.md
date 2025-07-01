# sea vision project

## overview
this project provides a flexible, scriptable image processing pipeline. you can build pipelines interactively using a python cli, or by writing a json config. the c++ backend executes the pipeline, applying each operation in order.

---

## workflow

```mermaid
flowchart LR
    A[user input] --> B[python cli or manual json]
    B --> C[pipeline json]
    C --> D[c++ backend]
    D --> E[processed image output]
```

---

## how to use

### 1. interactive python cli

run:
```sh
python src/python/main_cli.py
```
- select operations (brightness, blur, contrast, crop, sharpen) by number
- enter parameters as prompted
- enter input and output image paths (e.g., `data/input.jpg`, `data/output_result.jpg`)
- the cli creates a json pipeline and runs the c++ backend automatically

### 2. manual json

create a file like:
```json
{
  "operations": [
    {
      "type": "brightness",
      "parameters": {"factor": 1.2}
    },
    {
      "type": "blur",
      "parameters": {"kernel_size": 5, "sigma": 1.0}
    }
  ],
  "input_image": "data/input.jpg",
  "output_image": "data/output_result.jpg"
}
```
then run:
```sh
build/Release/sea_vision.exe pipeline.json data/input.jpg data/output_result.jpg
```

---

## project structure

```
sea_vision_project/
├── main.cpp
├── CMakeLists.txt
├── src/
│   ├── cpp/
│   │   ├── operations/
│   │   │   ├── cpp/
│   │   │   │   ├── base_operation.cpp
│   │   │   │   └── operations.cpp
│   │   │   └── hpp/
│   │   │       ├── base_operation.hpp
│   │   │       └── operations.hpp
│   │   └── bindings/
│   │       ├── cpp/
│   │       │   ├── operation_factory.cpp
│   │       │   └── pipeline_reader.cpp
│   │       └── hpp/
│   │           ├── operation_factory.hpp
│   │           └── pipeline_reader.hpp
│   └── python/
│       └── main_cli.py
├── data/
│   ├── input.jpg
│   └── output_*.jpg
├── tests/
│   ├── cpp/
│   ├── python/
│   └── json/
│       └── test_pipeline.json
└── build/
    └── Release/
        └── sea_vision.exe
```

---

## key files

- **main.cpp**: entry point, runs the pipeline
- **src/cpp/operations/hpp/operations.hpp / cpp/operations.cpp**: all operation implementations
- **src/cpp/bindings/hpp/operation_factory.hpp / cpp/operation_factory.cpp**: factory for creating operations
- **src/cpp/bindings/hpp/pipeline_reader.hpp / cpp/pipeline_reader.cpp**: reads and parses pipeline json
- **src/python/main_cli.py**: interactive cli for building and running pipelines

---

## features

- modular, extensible c++ pipeline
- interactive python cli for easy pipeline creation
- supports: brightness, blur, contrast, crop, sharpen
- simple json config for reproducible pipelines