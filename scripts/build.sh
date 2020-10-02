SCRIPTS_DIR=$(dirname "$0")
PROJECT_DIR=$SCRIPTS_DIR/..

COMPILER=${1:-g++}
TARGET=${2:-Release}

echo Setting compiler = $COMPILER
echo Setting target = $TARGET

mkdir -p $PROJECT_DIR/build
pushd $PROJECT_DIR/build

cmake -DCMAKE_BUILD_TYPE=$TARGET -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build . --config $TARGET
ctest -C $BUILD_TYPE
CTEST_RESULT=$?

popd
exit $CTEST_RESULT
