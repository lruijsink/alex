# alex
a lex icographic parser

Progress board: https://trello.com/b/zKQZAnMd/alex

# Contributing
When submitting contributions, make sure:
- All changes have been formatted using `clang-format`
- The single header is updated with Quom, and formatted

This process can be automated by adding `script/hook.sh` to your pre-commit hooks. This script will run Quom to generate the single header and run `clang-format` on all staged changes.

# Build + test locally
To build the project the following dependencies are required:
- CMake v3.1.0
- Python 3.6+ with PIP
- Catch2: unit testing library (https://github.com/catchorg/Catch2)
- Quom: single header generator (https://github.com/Viatorus/quom)

Use your CMake setup of choice or use the `script/build.sh` script, which outputs to the `build` folder.

`build.sh` takes two optional arguments: `compiler` and `target`, which default to `g++` and `Release`:
```
script/build.sh                 # build with GCC in Release mode
script/build.sh clang++ Debug   # build with Clang in Debug mode
```

# Installing dependencies
CMake
```
sudo apt-get install cmake
```

Python 3.6+ with PIP
```
sudo apt-get install python3.6
sudo apt-get install python3-pip
```

Catch2
```
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install
```

Quom
```
pip3 install quom
```
