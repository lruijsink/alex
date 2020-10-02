COMPILER=${1:-g++}
TARGET=${2:-Release}
PROJECT_ROOT=${3:-.}
OUTPUT_DIR=${4:-build}

echo Compiling with $COMPILER
echo Setting target to $TARGET
echo Building directory $PROJECT_ROOT
echo Outputting to $OUTPUT_DIR

cd $PROJECT_ROOT
mkdir -p $OUTPUT_DIR
cd $OUTPUT_DIR
cmake -DCMAKE_BUILD_TYPE=$TARGET -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build . --config $TARGET
ctest -C $BUILD_TYPE
cd ..