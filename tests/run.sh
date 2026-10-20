#!/bin/sh
# Usage: tests/run.sh ./scoreboard
set -u
bin=${1:-./scoreboard}
fail=0
check() {  # check <name> <input lines> <expected substring>
    out=$(printf "$2" | "$bin")
    case $out in
        *"$3"*) echo "PASS $1" ;;
        *) echo "FAIL $1: expected '$3' in: $out"; fail=1 ;;
    esac
}
check join     'JOIN alice\nJOIN bob\n'                  'OK 1'
check score    'JOIN alice\nSCORE 0 7\nSCORE 0 -2\n'     'OK alice 5'
check show     'JOIN alice\nJOIN bob\nSCORE 1 3\nSHOW\n' 'OK 1 bob 3'
check winner   'JOIN a\nJOIN b\nSCORE 0 1\nSCORE 1 9\nWINNER\n' 'OK b 9'
check rename   'JOIN alice\nRENAME 0 carol\nSHOW\n'      'OK 0 carol 0'
check noplayer 'JOIN alice\nSCORE 3 1\n'                 'ERR no such player'
check badname  'JOIN aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n'   'ERR board full'
check reset    'JOIN a\nSCORE 0 4\nRESET\nSHOW\n'        'OK 0 a 0'
exit $fail
