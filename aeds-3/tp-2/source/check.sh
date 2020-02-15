#!/bin/bash

i=0
make
while [ "$i" -le 9 ]; do
    ./tp2.out < toys/toy_"$i"_input
    diff -q toys/indices/toy_"$i"/index toys/indices/toy_"$i"/indexx.txt
    rm -f toys/indices/toy_"$i"/indexx.txt
    i=$((i+1))
done
