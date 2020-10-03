CI_DIR=$(dirname "$0")
ROOT_DIR=$CI_DIR/..
SCRIPT_DIR=$ROOT_DIR/script

set +x

$SCRIPT_DIR/generate-single-include.sh
BAD_SINGLE_INCLUDE=$(git ls-files --modified)

$CI_DIR/format-all.sh
BAD_CLANG_FORMAT=$(git ls-files --modified)

if [ $BAD_SINGLE_INCLUDE ] || [ $BAD_CLANG_FORMAT ]; then
  echo   "==============================================================================="
  echo   "Verification failed, please run Quom and clang-format before pushing changes."

  if [ $BAD_SINGLE_INCLUDE ]; then
    echo ""
    echo "REASON: Single header include incorrectly generated"
  fi
  
  if [ $BAD_CLANG_FORMAT ]; then
    echo ""
    echo "REASON: Files were not formatted properly, clang-format check failed for files:"
    echo $BAD_CLANG_FORMAT
  fi
  
  echo   "================================================================================"
  exit 1
fi
