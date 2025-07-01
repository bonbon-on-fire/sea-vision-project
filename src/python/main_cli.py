import argparse
import sys
import os
from pathlib import Path
import json
import subprocess

# define available operations and their parameters
OPERATIONS = [
    {
        "name": "brightness",
        "params": [
            {"name": "factor", "type": float, "prompt": "brightness factor (0.0-5.0, default 1.0)", "default": 1.0}
        ]
    },
    {
        "name": "blur",
        "params": [
            {"name": "kernel_size", "type": int, "prompt": "kernel size (odd, 3-31, default 5)", "default": 5},
            {"name": "sigma", "type": float, "prompt": "sigma (0.1-10.0, default 1.0)", "default": 1.0}
        ]
    },
    {
        "name": "contrast",
        "params": [
            {"name": "factor", "type": float, "prompt": "contrast factor (0.0-3.0, default 1.0)", "default": 1.0},
            {"name": "brightness_offset", "type": float, "prompt": "brightness offset (-100 to 100, default 0)", "default": 0.0}
        ]
    },
    {
        "name": "crop",
        "params": [
            {"name": "x", "type": int, "prompt": "x (default 0)", "default": 0},
            {"name": "y", "type": int, "prompt": "y (default 0)", "default": 0},
            {"name": "width", "type": int, "prompt": "width (default: image width - x)", "default": None},
            {"name": "height", "type": int, "prompt": "height (default: image height - y)", "default": None}
        ]
    },
    {
        "name": "sharpen",
        "params": [
            {"name": "strength", "type": float, "prompt": "strength (0.0-2.0, default 1.0)", "default": 1.0},
            {"name": "kernel_size", "type": int, "prompt": "kernel size (odd, 3-15, default 5)", "default": 5}
        ]
    }
]

def prompt_for_operation():
    print("\navailable operations:")
    for idx, op in enumerate(OPERATIONS, 1):
        print(f"  {idx}. {op['name']}")
    print("  0. done (finish pipeline)")
    while True:
        try:
            choice = int(input("select operation number: "))
            if 0 <= choice <= len(OPERATIONS):
                return choice
            else:
                print(f"please enter a number between 0 and {len(OPERATIONS)}.")
        except ValueError:
            print("invalid input. please enter a number.")

def prompt_for_params(op):
    params = {}
    for param in op["params"]:
        while True:
            prompt = f"  {param['prompt']}: "
            val = input(prompt)
            if val == '' and param["default"] is not None:
                params[param["name"]] = param["default"]
                break
            try:
                if val == '' and param["default"] is None:
                    break  # skip optional param
                params[param["name"]] = param["type"](val)
                break
            except ValueError:
                print(f"invalid value for {param['name']}. please enter a {param['type'].__name__}.")
    return params

def main():
    print("welcome to the sea vision pipeline builder!!")
    operations = []
    while True:
        op_num = prompt_for_operation()
        if op_num == 0:
            break
        op = OPERATIONS[op_num - 1]
        params = prompt_for_params(op)
        operations.append({
            "type": op["name"],
            "parameters": params
        })
    if not operations:
        print("no operations selected. exiting.")
        return
    input_image = input("enter input image path: ")
    output_image = input("enter output image path: ")
    pipeline = {
        "operations": operations,
        "input_image": input_image,
        "output_image": output_image
    }
    json_path = "pipeline_cli.json"
    with open(json_path, "w") as f:
        json.dump(pipeline, f, indent=2)
    print(f"pipeline json written to {json_path}")
    # run the c++ executable
    exe_path = os.path.join("build", "Release", "sea_vision.exe")
    cmd = [exe_path, json_path, input_image, output_image]
    print(f"running: {' '.join(cmd)}")
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        print(result.stdout)
        print("pipeline executed successfully.")
    except subprocess.CalledProcessError as e:
        print("error running pipeline:")
        print(e.stdout)
        print(e.stderr)

if __name__ == "__main__":
    main()