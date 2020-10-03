SCRIPT_DIR=$(dirname "$0")

# Generate single header include
$SCRIPT_DIR/generate-header.sh

# clang-format all staged changes and re-add
git diff --name-only --cached | grep '\.\(c\|h\|cpp\|hpp\)$' \
                              | xargs clang-format -i

git diff --name-only --cached | xargs git add
