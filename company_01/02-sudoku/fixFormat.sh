#!/bin/bash
if [ ! -f "/usr/bin/clang-format-6.0" ]; then
  echo "need to install clang-format-6.0"
  echo "sudo apt install clang-format-6.0"
  exit 1
fi
DIFF_COUNT=0
CLANG_FORMAT_CMD=clang-format-6.0
AVOID_01="-path ./spdlog -prune"
AVOID_02="-path ./benchmark -prune"
AVOID_03="-path ./build -prune"
AVOID_04="-path ./moc_\* -prune"
AVOID_FORMATTING="${AVOID_01} -o ${AVOID_02} -o ${AVOID_03} -o ${AVOID_04}"
#echo "$(find . ${AVOID_FORMATTING} -o -name '*.cpp' -print)"
FILES=$(find . ${AVOID_FORMATTING} -o -iname "*.c" -o -iname "*.h" -o -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.cc" -o -iname "*.hh" -o -iname "*.c++" -o -iname "*.h++" -iname "*.cxx" -o -iname "*.hxx")


for f in ${FILES}
do
  if [ ! -d "$f" ]; then
    DIFF_FILE="$($CLANG_FORMAT_CMD -style=file $f | diff -u $f -)"
    $($CLANG_FORMAT_CMD -style=file -i $f)
    DIFF_WORDCOUNT="$(echo "$DIFF_FILE" | wc -w)"
    if [ $DIFF_WORDCOUNT -gt 0 ]; then
      echo "FORMAT FIXED:$f"
      DIFF_COUNT=$(($DIFF_COUNT+1))
    fi
  fi
done

echo "Code format is ok"

exit $DIFF_COUNT
