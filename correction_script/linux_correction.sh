#!/usr/bin/env bash
set -euo pipefail

OUT="resultat.txt"
: > "$OUT"

OS="$(uname -s)"
case "$OS" in
  Linux)
    RUN_SCRIPT="./run_linux.sh"
    TIME_CMD=(/usr/bin/time -v)
    ;;
  Darwin)
    RUN_SCRIPT="./run_mac.sh"
    TIME_CMD=(/usr/bin/time -l)
    ;;
  *)
    printf -- "Unsupported OS: %s\n" "$OS" | tee -a "$OUT"
    exit 1
    ;;
esac

section() {
  printf -- "\n\n========== %s ==========\n\n" "$1" >> "$OUT"
}

run_and_log() {
  local title="$1"
  shift

  printf -- "---- %s ----\n" "$title" >> "$OUT"
  printf -- '$' >> "$OUT"
  for arg in "$@"; do
    printf -- " %q" "$arg" >> "$OUT"
  done
  printf -- "\n\n" >> "$OUT"

  "$@" &>> "$OUT"
  printf -- "\n" >> "$OUT"
}

section "LIBRARY COMPILATION (HOSTTYPE + symlink)"
export HOSTTYPE=Testing
run_and_log "make re" make re

LIB_NAME="libft_malloc_${HOSTTYPE}.so"
if [[ ! -f "$LIB_NAME" ]]; then
  printf -- "ERROR: expected %s not found after make re\n" "$LIB_NAME" | tee -a "$OUT"
  exit 1
fi

run_and_log "ln -sf $LIB_NAME libft_malloc.so" ln -sf "$LIB_NAME" libft_malloc.so
run_and_log "ls -l libft_malloc.so" ls -l libft_malloc.so

section "FUNCTIONS EXPORT (nm)"
run_and_log "nm -g libft_malloc.so | egrep malloc/free/realloc/show_alloc_mem" \
  bash -lc "nm -g libft_malloc.so | egrep '(_?malloc|_?free|_?realloc|show_alloc_mem)' || true"

section "RUN SCRIPT CHECK"
if [[ ! -f "$RUN_SCRIPT" ]]; then
  printf -- "ERROR: %s not found\n" "$RUN_SCRIPT" | tee -a "$OUT"
  exit 1
fi
run_and_log "chmod +x $RUN_SCRIPT" chmod +x "$RUN_SCRIPT"

section "MALLOC TESTS WITHOUT LIB (baseline)"
run_and_log "gcc -o test0 test0.c" gcc -o test0 test0.c
run_and_log "gcc -o test1 test1.c" gcc -o test1 test1.c

run_and_log "test0 (no preload)" "${TIME_CMD[@]}" ./test0
run_and_log "test1 (no preload)" "${TIME_CMD[@]}" ./test1

section "MALLOC TESTS WITH LIB (preload via run_*.sh)"
run_and_log "test0 (with preload)" "$RUN_SCRIPT" "${TIME_CMD[@]}" ./test0
run_and_log "test1 (with preload)" "$RUN_SCRIPT" "${TIME_CMD[@]}" ./test1

section "FREE TESTS (test2 vs test1)"
run_and_log "gcc -o test2 test2.c" gcc -o test2 test2.c
run_and_log "test2 (with preload)" "$RUN_SCRIPT" "${TIME_CMD[@]}" ./test2

section "REALLOC TEST (test3: must print Hello world! twice)"
run_and_log "gcc -o test3 test3.c -L. -lft_malloc -Wl,-rpath,'\$ORIGIN'" \
  gcc -o test3 test3.c -L. -lft_malloc -Wl,-rpath,'$ORIGIN'
run_and_log "run test3 with preload" "$RUN_SCRIPT" ./test3

section "SHOW_ALLOC_MEM TEST (test4)"
run_and_log "gcc -o test4 test4.c -L. -lft_malloc -Wl,-rpath,'\$ORIGIN'" \
  gcc -o test4 test4.c -L. -lft_malloc -Wl,-rpath,'$ORIGIN'
run_and_log "run test4 with preload" "$RUN_SCRIPT" ./test4

section "ALIGNMENT TEST (test5)"
run_and_log "gcc -o test5 test5.c -L. -lft_malloc -Wl,-rpath,'\$ORIGIN'" \
  gcc -o test5 test5.c -L. -lft_malloc -Wl,-rpath,'$ORIGIN'
run_and_log "run test5 with preload" "$RUN_SCRIPT" ./test5

section "CLEANUP"
run_and_log "rm -f test0 test1 test2 test3 test4 test5" rm -f test0 test1 test2 test3 test4 test5

section "DONE"
printf -- "Wrote full report to %s\n" "$OUT" | tee -a "$OUT"
rm libft_malloc_Testing.so
make fclean
