#!/bin/bash

PROJ_NAME="booked"

TEST_CASES=$(ls ./tests)

GREEN="\033[0;32m"
RED="\033[0;31m"
WHITE="\033[0;01m"

echo "Compilando o programa:"
make

echo -e "${WHITE}"

echo "Rodando os casos de teste:"
echo""
echo "--------------"

cd ./tests

for TEST in $TEST_CASES; do
    cd ./$TEST
    mkdir -p saidas

    echo "$TEST:"
    valgrind --leak-check=full --show-leak-kinds=all --log-file=saidas/valgrind.log ./../../$PROJ_NAME > saidas/minha_saida.txt

    echo -n "Output: "
    diff saidas/minha_saida.txt saida.txt > saidas/diff.log
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}CORRETO!"
    else
        echo -e "${RED}INCORRETO!"
    fi
    echo -e -n "${WHITE}"
    
    echo -n "Valgrind: "
    grep -q "ERROR SUMMARY: 0 errors" saidas/valgrind.log
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}SEM VAZAMENTO DE MEMÓRIA!"
    else
        echo -e "${RED}COM VAZAMENTO DE MEMORIA!"
        echo "Cheque o arquivo saidas/valgrind.log"
    fi

    echo -e -n "${WHITE}"
    cd ..
    echo "--------------"
done

cd ..
