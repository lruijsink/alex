SCRIPT_DIR=$(dirname "$0")
ROOT_DIR=$SCRIPT_DIR/..
BUILD_DIR=$ROOT_DIR/build

COMPILER=${1:-g++}
TARGET=${2:-Release}
echo Setting COMPILER = $COMPILER
echo Setting TARGET = $TARGET

mkdir -p $BUILD_DIR
pushd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=$TARGET -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build . --config $TARGET
ctest -C $BUILD_TYPE
CTEST_RESULT=$?

popd
exit $CTEST_RESULT
