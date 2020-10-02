COMPILER=${1:-g++}
TARGET=${2:-Release}
PROJECT_ROOT=${3:-.}

echo Setting compiler = $COMPILER
echo Setting target = $TARGET
echo Setting project root = $PROJECT_ROOT

mkdir -p $PROJECT_ROOT/build
pushd $PROJECT_ROOT/build

cmake -DCMAKE_BUILD_TYPE=$TARGET -DCMAKE_CXX_COMPILER=$COMPILER ..
cmake --build . --config $TARGET
ctest -C $BUILD_TYPE
CTEST_RESULT=$?

popd
exit $CTEST_RESULT
