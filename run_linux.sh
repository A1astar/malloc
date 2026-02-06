#!/usr/bin/env bash
set -euo pipefail

# Se placer dans le dossier du script (donc du projet)
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

LIB="$SCRIPT_DIR/libft_malloc.so"

if [[ ! -f "$LIB" ]]; then
  echo "ERROR: $LIB not found. Build the library and create the symlink first." >&2
  echo "Hint: make re && ln -sf libft_malloc_\${HOSTTYPE}.so libft_malloc.so" >&2
  exit 1
fi

# Exécute la commande passée en gardant toutes les sorties
env -i \
  PATH="$PATH" \
  HOME="${HOME:-/tmp}" \
  USER="${USER:-user}" \
  TERM="${TERM:-xterm-256color}" \
  LD_PRELOAD="$LIB" \
  LD_LIBRARY_PATH="$SCRIPT_DIR:${LD_LIBRARY_PATH:-}" \
  "$@"
