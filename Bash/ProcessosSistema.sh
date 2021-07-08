#!/bin/bash

#a) Número total de processos ativos no sistema.
numeroProcessosAtivos=$(ps -e | wc -l)
numeroProcessosAtivos=$(($numeroProcessosAtivos - 2))

#b) Número de processos ativos do usuário.
numeroProcessosUsuario=$(ps -ue | wc -l)
numeroProcessosUsuario=$(($numeroProcessosUsuario - 2))

#c) Quantidade total de threads dos processos do usuário.
numeroTotalTheadsUser=$(ps -eo user H | grep "$USER" | wc -l)
numeroTotalTheadsUser=$(($numeroTotalTheadsUser - 2))

#d) Processo mais antigo do usuário.
pidProcessoMaisAntigoUser=$(pgrep -U "$USER" -o)

#e) Nome do usuário corrente.
usuarioCorrente=$(echo "$USER") 

#f) Quantidade de processos sendo executados, excluindo-se os do usuário corrente.
processosExecutadosUser=$(ps -U "$USER" -u "$USER" u | wc -l)
processosExecutadosUser=$(($processosExecutadosUser - 2))


#g) Quantidade de processos sendo executados como root.
processosExecutadosRoot=$(ps -U root -u root u | wc -l)
processosExecutadosRoot=$(($processosExecutadosRoot - 2))

dataFormatada=$(date '+%Y%m%d')
horaFormatada=$(date '+%H%M%S')

tituloArquivo="${dataFormatada}_${horaFormatada}_Processos_${usuarioCorrente}.csv"

echo $(touch $tituloArquivo)

conteudoArquivo="${numeroProcessosAtivos}"
conteudoArquivo="${conteudoArquivo},${numeroProcessosUsuario}"
conteudoArquivo="${conteudoArquivo},${numeroTotalTheadsUser}"
conteudoArquivo="${conteudoArquivo},${pidProcessoMaisAntigoUser}"
conteudoArquivo="${conteudoArquivo},${usuarioCorrente}"
conteudoArquivo="${conteudoArquivo},${processosExecutadosUser}"
conteudoArquivo="${conteudoArquivo},${processosExecutadosRoot}"

echo "${conteudoArquivo}">>$tituloArquivo