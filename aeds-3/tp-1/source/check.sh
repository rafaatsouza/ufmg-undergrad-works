#!/bin/bash

i=0
make
while [ "$i" -le 9 ]; do
    ./tp1.out < testes/input_"$i" > testes/saida_"$i".txt
    diff -q testes/resposta_"$i" testes/saida_"$i".txt
    rm -f testes/saida_"$i".txt
    i=$((i+1))
done
