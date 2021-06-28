#!/bin/bash

textoPergunta="Informar o nome do programa que deseja consultar"

echo $textoPergunta
read nomePrograma

processo=$(pgrep $nomePrograma)
processo=$(echo $processo | cut -d ' ' -f 1)
echo $processo

if [ -z $processo ]; then
    echo "opa, não achou!!!"
else
    echo "PID: $( ps axo pid | grep $processo )"
    estado="$(ps axo stat,pid | grep $processo)"
    estado=${estado:0:1}

    if [ $estado = "D" ]; then
        echo "Estado: uninterruptible sleep"
    elif [ $estado = "R" ]; then
        echo "Estado: running or runnable"
    elif [ $estado = "S" ]; then
        echo "Estado: interruptible sleep"
    elif [ $estado = "T" ]; then
        echo "Estado: stopped"
    elif [ $estado = "W" ]; then
        echo "Estado: paging"
    elif [ $estado = "X" ]; then
        echo "Estado: dead"
    elif [ $estado = "Z" ]; then
        echo "Estado: zombie"
    fi
fi