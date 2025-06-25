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
    valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=2 --log-file=saidas/valgrind.log ./../../$PROJ_NAME > saidas/minha_saida.txt
    VALGRIND_EXITCODE=$?

    echo -n "Output: "
    diff saidas/minha_saida.txt saida.txt > saidas/diff.log
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}CORRETO!"
    else
        echo -e "${RED}INCORRETO!"
    fi
    echo -e -n "${WHITE}"
    
    echo -n "Valgrind: "
    if [ ${VALGRIND_EXITCODE} -eq 2 ]; then
        echo -e "${RED}VALGRIND IDENTIFICOU 1 OU MAIS ERROS!"
        echo "Cheque o arquivo saidas/valgrind.log"
    else
        echo -e "${GREEN}SEM ERROS ACUSADOS PELO VALGRIND!"
    fi

    echo -e -n "${WHITE}"
    cd ..
    echo "--------------"
done

cd ..
