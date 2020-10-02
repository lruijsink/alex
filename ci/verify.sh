set +x
MY_DIR=$(dirname "$0")

$MY_DIR/make_single_include.sh
BAD_SINGLE_INCLUDE=$(git ls-files --modified)

$MY_DIR/clang_format_all.sh
BAD_CLANG_FORMAT=$(git ls-files --modified)

if [ $BAD_SINGLE_INCLUDE ] || [ $BAD_CLANG_FORMAT ]; then
  echo   "==================================================="
  echo   "Verification failed, please add hook.sh to your"
  echo   "pre-commit hooks to automatically generate correct"
  echo   "single header include and format all on commit"

  if [ $BAD_SINGLE_INCLUDE ]; then
    echo "REASON: Single header include incorrectly generated"
  fi
  
  if [ $BAD_CLANG_FORMAT ]; then
    echo "REASON: Files were not formatted properly"
    echo $BAD_CLANG_FORMAT
  fi
  
  echo   "==================================================="
  exit 1
fi
