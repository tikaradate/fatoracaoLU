#!/bin/bash


TAMANHO=(10 32 50 64 100 128 200 256 300 400 512 1000)
GRUPO=(L3 L2CACHE FLOPS_DP)


for TAM in "${TAMANHO[@]}"
do
    for G in "${GRUPO[@]}" 
    do
        echo $TAM-$G
        likwid-perfctr -C 3 -g $G -m ./inter_ajuste < inputs/$TAM.in > Resultados/$TAM-$G.out
    done

done
