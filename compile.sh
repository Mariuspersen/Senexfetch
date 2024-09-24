#!/bin/bash
rm -r out 2> /dev/null
mkdir out 2> /dev/null
cc65 src/main.c -t cx16 -o out/main.s && cl65 out/main.s -t cx16 -o out/main.prg