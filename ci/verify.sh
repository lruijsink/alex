set +x
MY_DIR=$(dirname "$0")

$MY_DIR/make_single_include.sh
BAD_SINGLE_INCLUDE=$(git ls-files --modified)

$MY_DIR/clang_format_all.sh
BAD_CLANG_FORMAT=$(git ls-files --modified)

if [ $BAD_SINGLE_INCLUDE ] || [ $BAD_CLANG_FORMAT ]; then
  echo   "==============================================================================="
  echo   "Verification failed, please add script/hook.sh to .git/hooks/pre-commit or run"
  echo   "clang-format and Quom manually before pushing changes."

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
