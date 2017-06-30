#!/bin/bash

i=0
make
while [ "$i" -le 9 ]; do
    ./tp3.out -d < toys/entrada/toy_"$i" > saida.txt
    diff -q toys/saida/toy_"$i" saida.txt
    rm -f saida.txt
    echo "Passou o $i"
    i=$((i+1))
done
