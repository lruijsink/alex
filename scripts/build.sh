COMPILER=$1
TARGET=$2

cd build
cmake -DCMAKE_BUILD_TYPE=$TARGET -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build . --config $TARGET
ctest -C $BUILD_TYPE
cd ..