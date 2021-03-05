#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Equipe
Luiz Bertolino Serpa Neto
*/


FILE *arquivo = NULL;
char separador[4] = {"[Ж}"};
int tamanhoAgenda = 0;
#define ESPACO_LIVRE_INICIAL 255
#define TAM_PADRAO_STRING 100

typedef enum {
    false,
    true
} boolean;

typedef struct 
{
    int codigo;
    char nome[TAM_PADRAO_STRING];
    char telefone[TAM_PADRAO_STRING];
    char email[TAM_PADRAO_STRING];
    boolean status;
} Contato;

//Manipulacao de arquivos
void abrirArquivo(Contato []);
void fecharArquivo(Contato []);
void tamanhoNecessario();

//CRUD
void inserirContato(Contato []);
void listarContatos(Contato []);
void alterarContato(Contato []);
void deletarContato(Contato []);
void pesquisarContato(Contato []);

//Utilitarios
void menu(Contato []);
void imprimirContato(Contato [], int);
void setString(char [], int);
int setNumero(char []);
boolean isStringNaoVazia (char []);
boolean isEmailValido (char [], int);
void listarSerieContatos (Contato [], int []);
boolean isContatoProcurado (char [], char []);
void stringToLowerCase(char [], char []);
void listaContatosEncontrados(Contato [],char [], int []);
void confimarExclusao(Contato[], int);
void setNomeContato (char []);
void setTelefoneEmailContato (char [], char []);
void concatenarString(Contato [], char []);

void main (){
    tamanhoNecessario();
    Contato c[tamanhoAgenda];
    abrirArquivo(c);
    menu(c);
    fecharArquivo(c);
}



void tamanhoNecessario(){
    arquivo = fopen("agenda.txt", "r");
    char *agendaTamanho = NULL;
    if (arquivo != NULL)
    {
        int sizeChar = sizeof(Contato)*tamanhoAgenda;
        agendaTamanho = calloc(sizeChar, sizeof(char));
        fgets(agendaTamanho, 1000, arquivo);
        char *token[sizeChar];
        *token = strtok(agendaTamanho, separador);
        int ContatosSalvos = atoi(*token);
        tamanhoAgenda = ContatosSalvos + ESPACO_LIVRE_INICIAL;
        free(agendaTamanho);
    }
    if (arquivo == NULL){
        arquivo = fopen("agenda.txt", "w");
        fputs("0", arquivo);
        tamanhoAgenda = ESPACO_LIVRE_INICIAL;
    }
    fclose(arquivo);
}

void abrirArquivo(Contato c[]){
    arquivo = fopen("agenda.txt", "r");
    if (arquivo != NULL)
    {
        int sizeChar = sizeof(Contato)*tamanhoAgenda;
        char *agendaConteudo = calloc(sizeChar, sizeof(char));
        char *token[sizeChar];
        char modeloTraco[2]= "-";
        fgets(agendaConteudo, sizeChar, arquivo);
        *token = strtok(agendaConteudo, separador);
        token[strcspn(*token, "\n")] = 0;
        int ContatosSalvos = 0;
        ContatosSalvos = atoi(*token);
        // GCC v = 9.3.0
        // fgets para no "\n"
        for (int i = 0; i < ContatosSalvos; i++)
        {
            char *contatoConteudo = calloc(sizeof(Contato), sizeof(char));
            fgets(contatoConteudo,sizeChar, arquivo);
            c[i].codigo = i;
            *token = strtok(contatoConteudo, separador);
            strcpy(c[i].nome, *token);
            *token = strtok(NULL, separador);
            if (strcmp(modeloTraco, *token)== 0)
            {
                strcpy(c[i].telefone, "");
            }else{
                strcpy(c[i].telefone, *token);
            }
            *token = strtok(NULL, separador);
            strcpy(c[i].email, *token);
            c[i].email[strcspn(c[i].email, "\n")] = 0;
            c[i].status = true;
            free(contatoConteudo);
        }
        for (int i = 0; i < ESPACO_LIVRE_INICIAL; i++)
        {
            c[i+ContatosSalvos].codigo = ContatosSalvos+i;
            c[i+ContatosSalvos].status = false;
        }
        free(agendaConteudo);
    }
    if (arquivo == NULL)
    {
        arquivo = fopen("agenda.txt", "w");
        for (int i = 0; i < tamanhoAgenda; i++)
        {
            c[i].codigo = i;
            c[i].status = false;
        }
    }
    fclose(arquivo);
}

void imprimirContato(Contato c[], int codigoContato){
    if (c[codigoContato].status == true)
    {
        printf("%-50s", c[codigoContato].nome);
        printf("%-50s", c[codigoContato].telefone);
        printf("%s\n", c[codigoContato].email);
    }else
    {
        printf("ERRO IMPRIMIR Contato - STATUS == FALSE");
    }
}

void listarContatos(Contato c[]){
    char nome[10] = {"Nome"}, telefone[10] = {"Telefone"}, email[10] = {"E-mail"}, espacoVazio[2] = {" "};
    printf("%-25s===================== Lista de Contatos =====================\n", espacoVazio);
    printf("%-50s%-50s%s\n\n", nome, telefone, email);
    
    for (int i = 0; i < tamanhoAgenda; i++)
    {
        if (c[i].status == true)
        {
            imprimirContato(c, i);
        }
        
    }
    printf("\n%-25s=============================================================\n", espacoVazio);
}

void inserirContato (Contato c[]){
    char nome[TAM_PADRAO_STRING], telefone[TAM_PADRAO_STRING], email[TAM_PADRAO_STRING];
    int i = 0;
    while(true){
        if (!c[i].status){
            break;
        }
        i++;
    }
    printf("===================== Inserir Contatos =====================\n");
    printf("*O nome e pelo menos uma forma de contato devem ser informados\n");
    setNomeContato(nome);
    setTelefoneEmailContato(telefone, email);
    strcpy(c[i].nome, nome);
    strcpy(c[i].telefone, telefone);
    strcpy(c[i].email, email);
    c[i].status = true;
    imprimirContato(c, i);
}

void setString (char string[], int size){
    if (fgets(string, size, stdin))
    {
        string[strcspn(string, "\n")] = 0;
    }
}

boolean isStringNaoVazia(char string[]){
    char *stringVazia = calloc(2, sizeof(char));
    if(strcmp(string, stringVazia) == 0){
        return false;
    }else {
        return true;
    }
    free(stringVazia);
}

boolean isEmailValido (char email[], int size){
    int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;

  for (i = 0; i < size; i++) {
    char c = email[i];
    if(c == '@') {
      if (arroba)
        break; 
      arroba = 1;
      if (i < 3)
        break; 
    }
    else if (arroba) { 
      if (ponto) {
        depoisPonto++;
      }
      else if(c == '.') {
        ponto = 1;
        if (antesPonto < 3) {
          break; 
        }
      }
      else {
        antesPonto++;
      }
    }
  } 

  if (i == size && depoisPonto > 1)
    return true;
  else
    return false;
}

void listarSerieContatos(Contato c[], int codigoContatos[]){
    char nome[10] = {"Nome"}, telefone[10] = {"Telefone"}, email[10] = {"E-mail"}, espacoVazio[2] = {" "};
    printf("%-25s===================== Contatos Encontrados =====================\n", espacoVazio);
    printf("Cod. %-50s%-50s%s\n\n", nome, telefone, email);
    for (int i = 1; i <= codigoContatos[0]; i++)
    {
        if (c[codigoContatos[i]].status == true)
        {
            printf("%-5d", i);
            imprimirContato(c, codigoContatos[i]);
        }
        
    }
    printf("\n%-25s=============================================================\n", espacoVazio);
}

void pesquisarContato(Contato c[]){
    char *informacaoPesquisada = calloc(50, sizeof(char));
    int codigoContatos[tamanhoAgenda];
    codigoContatos[0] = 0;
    printf("===================== Buscar Contatos =====================\n");
    printf("Informe o nome ou telefone do contato que deseja encontrar\n");
    setString(informacaoPesquisada, 50);
    listaContatosEncontrados(c, informacaoPesquisada, codigoContatos);
    if (codigoContatos[0] == 0)
    {
        printf("Nenhum Contato Encontrado\n");
    }else
    {
        listarSerieContatos(c, codigoContatos);
    }
    free(informacaoPesquisada);
}

boolean isContatoProcurado(char haystack[], char needle[]){
    char *substring;
    char *haystackLowerCase = calloc(50, sizeof(char));
    char *needleLowerCase = calloc(50, sizeof(char));
    stringToLowerCase(haystack, haystackLowerCase);
    stringToLowerCase(needle, needleLowerCase);
    substring = strstr(haystackLowerCase, needleLowerCase);
    if (substring != NULL)
    {
        free(needleLowerCase);
        free(haystackLowerCase);
        return true;
    }
    if (substring == NULL)
    {
        free(needleLowerCase);
        free(haystackLowerCase);
        return false;
    }
    
}

void stringToLowerCase (char string[], char stringLowerCase[]){
    int i = 0;
    while (string[i] != '\0')
    {
        stringLowerCase[i] = tolower(string[i]);
        i++;
    }
}

void deletarContato (Contato c[]){
    char informancaoPesquisada[TAM_PADRAO_STRING];
    int codigoContatos[tamanhoAgenda];
    int ordemInformado = 0;
    codigoContatos[0] = 0;
    printf("===================== Deletar Contatos =====================\n");
    printf("Informe o nome ou telefone do contato que deseja deletar\n");
    setString(informancaoPesquisada, TAM_PADRAO_STRING);
    listaContatosEncontrados(c, informancaoPesquisada, codigoContatos);
    if (codigoContatos[0] == 0)
    {
        printf("Nenhum Contato Encontrado\n");
    }else
    {
        if (codigoContatos[0] == 1)
        {
            confimarExclusao(c, codigoContatos[1]);
        }
        if (codigoContatos[0] > 1){
            listarSerieContatos(c, codigoContatos);
            char informacaoNumero[50] = "Informe o codigo do contato que deseja excluir\n";
            while(true){
                ordemInformado = setNumero(informacaoNumero);
                if(codigoContatos[0] >= ordemInformado && ordemInformado != 0){
                    if(c[codigoContatos[ordemInformado]].status == true){
                        confimarExclusao(c, codigoContatos[ordemInformado]);
                        break;
                    }else{
                        printf("Entrada invalida2\n");
                    }
                }else
                {
                    printf("Entrada invalida3\n");
                }
            }
        }
    }
}

void listaContatosEncontrados (Contato c[],char informacaoPesquisada[], int codigoContatos[]){
    for (int i = 0; i < tamanhoAgenda; i++)
    {
        if (c[i].status == true)
        {
            if (isContatoProcurado(c[i].nome, informacaoPesquisada) || isContatoProcurado(c[i].telefone, informacaoPesquisada))
            {
                codigoContatos[0] += 1;
                codigoContatos[codigoContatos[0]] = i;
            }
        }
    }
}

int setNumero(char informacaoNumero[]){
    int numero;
    char limpa_buffer[255];
    while(true){
        printf("%s", informacaoNumero);
        if (scanf("%d", &numero)){
            fgets(limpa_buffer, 255, stdin);
            return numero;
        }else{
            printf("Entrada Invalida\n");
            fgets(limpa_buffer, 255, stdin);
        }
    }
}

void confimarExclusao(Contato c[], int codigoContato){
    printf("Deseja excluir o contato?\n");
    imprimirContato(c,codigoContato);
    while(true){
        printf("Confirma exclusao? (S/N): ");
        char *opcaoUsuario = calloc(255,sizeof(char));
        char *opcaoUsuarioToLowerCase = calloc(255, sizeof(char));
        char sim[2] = "s", nao[2] = "n";
        setString(opcaoUsuario, 255);
        stringToLowerCase(opcaoUsuario,opcaoUsuarioToLowerCase);
        if (strcmp(opcaoUsuarioToLowerCase,sim) == 0)
        {
            c[codigoContato].status = false;
            printf("Exclusao feita com sucesso\n");
            free(opcaoUsuario);
            free(opcaoUsuarioToLowerCase);
            break;
        }else if(strcmp(opcaoUsuarioToLowerCase,nao) == 0){
            printf("Exclusao cancelada\n");
            free(opcaoUsuario);
            free(opcaoUsuarioToLowerCase);
            break;
        }else{
            printf("Entrada Invalida\n");
            free(opcaoUsuario);
            free(opcaoUsuarioToLowerCase);
        }
    }
}

void alterarContato(Contato c[]){
    char informancaoPesquisada[TAM_PADRAO_STRING];
    int codigoContatos[tamanhoAgenda];
    int ordemInformado = 0;
    codigoContatos[0] = 0;
    printf("===================== Alterar Contatos =====================\n");
    printf("Informe o nome ou telefone do contato que deseja alterar\n");
    setString(informancaoPesquisada, TAM_PADRAO_STRING);
    listaContatosEncontrados(c, informancaoPesquisada, codigoContatos);
    if (codigoContatos[0] == 0)
    {
        printf("Nenhum Contato Encontrado\n");
    }else
    {
        if (codigoContatos[0] == 1)
        {
            printf("Informacoes contato: \n");
            imprimirContato(c,codigoContatos[1]);
            printf("Atualizacao das informacoes: \n");
            setNomeContato(c[codigoContatos[1]].nome);
            setTelefoneEmailContato(c[codigoContatos[1]].telefone, c[codigoContatos[1]].email);
            imprimirContato(c, codigoContatos[1]);
        }
        if (codigoContatos[0] > 1){
            listarSerieContatos(c, codigoContatos);
            char informacaoNumero[TAM_PADRAO_STRING] = "Informe o codigo do contato que deseja Alterar\n";
            while(true){
                ordemInformado = setNumero(informacaoNumero);
                if(codigoContatos[0] >= ordemInformado && ordemInformado != 0){
                    if(c[codigoContatos[ordemInformado]].status == true){
                        printf("Informacoes contato: \n");
                        imprimirContato(c,codigoContatos[ordemInformado]);
                        printf("Atualizacao das informacoes: \n");
                        setNomeContato(c[codigoContatos[ordemInformado]].nome);
                        setTelefoneEmailContato(c[codigoContatos[ordemInformado]].telefone, c[codigoContatos[ordemInformado]].email);
                        imprimirContato(c, codigoContatos[ordemInformado]);
                        break;
                    }else{
                        printf("Entrada invalida\n");
                    }
                }else
                {
                    printf("Entrada invalida\n");
                }
            }
        }
    }
}

void setNomeContato(char nome[]){
    boolean isStringValida;
    do{
        isStringValida = false;
        printf("Nome :");
        setString(nome, TAM_PADRAO_STRING);
        if (isStringNaoVazia(nome)){
            isStringValida = true;
        }else{
            printf("O nome do contato deve ser informado\n");
        }
    }while(!isStringValida);
}

void setTelefoneEmailContato(char telefone[], char email[]){
    boolean isStringValida;
    char *emailVazio = calloc(TAM_PADRAO_STRING, sizeof(char));
    do
    {
        boolean isEmailConforme = false;
        isStringValida = false;
        printf("Telefone: ");
        setString(telefone, TAM_PADRAO_STRING);
        if (isStringNaoVazia(telefone))
        {
            isStringValida = true;
        }
        do{
            printf("E-mail: ");
            setString(emailVazio, TAM_PADRAO_STRING);
            if (isStringNaoVazia(emailVazio)){
                if (isEmailValido(emailVazio, TAM_PADRAO_STRING))
                {
                    strcpy(email, emailVazio);
                    free(emailVazio);
                    isEmailConforme = true;
                    isStringValida = true;
                }else{
                    printf("E-mail invalido\n");
                }   
            }else{
                strcpy(email, emailVazio);
                free(emailVazio);
                isEmailConforme = true;
            }
        }while (isEmailConforme == false);
        if (!isStringValida)
        {
            printf("Pelo menos uma forma de contato deve ser informada\n");
        }
    } while (!isStringValida);
}

void menu (Contato c[]){
    int entradaMenu;
    char perguntaSetNumero[TAM_PADRAO_STRING] = "Informe o a opcao desejada: ";
    do{
        printf("\n\n===================== Menu =====================\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Alterar Contato\n");
        printf("5. Deletar Contato\n");
        printf("0. Sair\n");
        printf("================================================\n");
        entradaMenu = setNumero(perguntaSetNumero);
        system("clear");
        switch (entradaMenu)
        {
        case 1 :
            inserirContato(c);
            break;
        case 2:
            listarContatos(c);
            break;
        case 3:
            pesquisarContato(c);
            break;
        case 4:
            alterarContato(c);
            break;
        case 5:
            deletarContato(c);
            break;
        case 0:
            break;
        default:
            printf("Entrada Invalida\n\n");
            break;
        }
    }while(entradaMenu != 0);
}

void fecharArquivo(Contato c[]){
    arquivo = fopen("agenda.txt", "w+");
    char quebralinha[10] = "\n";
    char *saida = calloc(sizeof(Contato)*tamanhoAgenda, sizeof(char));
    int numeroContatosAtivos = 0;
    for (int i = 0; i < tamanhoAgenda; i++)
    {
        if (c[i].status == true)
        {
            numeroContatosAtivos++;
        }
    }
    snprintf(saida,sizeof(Contato)*tamanhoAgenda, "%d", numeroContatosAtivos);
    strcat(saida, quebralinha);
    concatenarString(c,saida);
    fputs(saida, arquivo);
    free(saida);
    fclose(arquivo);
}

void concatenarString (Contato c[], char saidaConcatenada[]){
    char quebralinha[10] = "\n", modeloNumeroVazio[2];
    modeloNumeroVazio[0] = 0;
    for (int i = 0; i < tamanhoAgenda; i++)
    {
        if (c[i].status == true)
        {
            strcat(saidaConcatenada, c[i].nome);
            strcat(saidaConcatenada, separador);
            if(strcmp(modeloNumeroVazio, c[i].telefone) == 0){
                char espacoVazio[10] = "-";
                strcat(saidaConcatenada, espacoVazio);
            }else
            {
                strcat(saidaConcatenada, c[i].telefone);
            }
            strcat(saidaConcatenada, separador);
            strcat(saidaConcatenada, c[i].email);
            strcat(saidaConcatenada, quebralinha);
        }
    }
}
