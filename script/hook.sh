SCRIPTS_DIR=$(dirname "$0")
PROJECT_DIR=$SCRIPTS_DIR/..

# Generate single header include
quom $PROJECT_DIR/include/alex/alex.hpp \
     $PROJECT_DIR/single_include/alex/alex.hpp

clang-format -i $PROJECT_DIR/single_include/alex/alex.hpp
git add $PROJECT_DIR/single_include/alex/alex.hpp

# Run clang-format on changes
git diff --name-only --cached | grep '\.\(c\|h\|cpp\|hpp\)$' \
                              | xargs clang-format -i

git diff --name-only --cached | xargs git add
