clear
rm -r build
mkdir build
cd build
export CC=gcc-11
export CXX=g++-11
cmake ..
cmake --build .
./example_basic
cd ..
