#!/usr/bin/env bash
# Maintainer check: every solution must pass, and every exercise must fail
# as shipped (except intro1, which passes and only needs its marker removed).
set -u
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT" || exit 1
CC="${CC:-cc}"
OUT="$(mktemp -d)"
trap 'rm -rf "$OUT"' EXIT
FLAGS=(-std=c17 -Wall -Wextra -Werror -g -O0 -fsanitize=address,undefined
       -fno-sanitize-recover=all -fno-omit-frame-pointer -I "$ROOT/include")

run() { # <file> -> echo status: COMPILE / RUN=<code>
    local f=$1 b
    b="$OUT/$(echo "$f" | tr / _)"
    if ! "$CC" "${FLAGS[@]}" "$f" -o "$b" -lm >"$b.log" 2>&1; then
        echo COMPILE; return
    fi
    (cd "$(dirname "$f")" && timeout 5 "$b" >"$b.log" 2>&1)
    echo "RUN=$?"
}

bad=0
while read -r p; do
    s=$(run "solutions/$p")
    e=$(run "exercises/$p")
    status=ok
    [[ $s == RUN=0 ]] || status=BAD
    [[ $e == RUN=0 && $p != 00_intro/intro1.c ]] && status=BAD
    [[ $status == BAD ]] && bad=$((bad + 1))
    printf '%-4s %-44s solution:%-8s exercise:%s\n' "$status" "$p" "$s" "$e"
done < <(grep -v '^\s*\(#\|$\)' info)
echo "$bad problem(s)"
[[ $bad -eq 0 ]]
