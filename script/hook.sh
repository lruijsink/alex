SCRIPTS_DIR=$(dirname "$0")
PROJECT_DIR=$SCRIPTS_DIR/..

# Generate single header include
quom $PROJECT_DIR/include/alex/alex.hpp \
     $PROJECT_DIR/single_include/alex/alex.hpp

clang-format -i $PROJECT_DIR/single_include/alex/alex.hpp
git add $PROJECT_DIR/single_include/alex/alex.hpp

# Run clang-format on whole project
find $PROJECT_DIR -iname *.h -o \
                  -iname *.hpp -o \
                  -iname *.c -o \
                  -iname *.cpp \
| xargs clang-format -i
