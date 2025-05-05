#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CAP 20

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

void pegarDataAtual(Data *data) {
    time_t agora;
    struct tm *infoTempo;

    time(&agora);
    infoTempo = localtime(&agora);

    data->dia = infoTempo->tm_mday;
    data->mes = infoTempo->tm_mon + 1;
    data->ano = infoTempo->tm_year + 1900;
}

typedef struct Registro{
    char nome[600];
    int idade;
    char RG[500];
    Data *entrada;
} Registro;

void addRegistro(Registro *registro, Data *data) { 
    printf("Digite o RG: ");
    fgets(registro->RG, 100, stdin);
    registro->RG[strcspn(registro->RG, "\n")] = '\0';

    printf("Digite o nome: ");
    fgets(registro->nome, 100, stdin);
    registro->nome[strcspn(registro->nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &registro->idade);
    getchar(); 

    registro->entrada = data;
}

//--------------------------------------------

typedef struct Elista {
    Registro *dados;
    struct Elista *proximo;
} Elista;
//LDE
typedef struct Lista{
    Elista *inicio;
    int qtd;
} Lista;


Elista *criar_celula(Registro *dados){
    Elista *nova = malloc(sizeof(Elista)); 
    nova->proximo = NULL;
    nova->dados = dados;
    return nova;
}

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtd = 0;
    return lista;
}

void inserir(Lista *lista, Registro *dados){
    Elista *nova = criar_celula(dados);
    if(lista->inicio == NULL){
        lista->inicio = nova;
        lista->qtd++;
        return;
    }

    Elista *atual = lista->inicio;

    nova->proximo = atual;
    lista->inicio = nova;
    lista->qtd++;
    
    return;
}

void mostrar(Lista *lista){
    Elista *atual = lista->inicio;

    while(atual != NULL){
        printf("------------------------------------\n");
        printf("Nome: %s\n", atual->dados->nome);
        printf("Entrada: %d/", atual->dados->entrada->dia);
        printf("%d/", atual->dados->entrada->mes);
        printf("%d\n", atual->dados->entrada->ano);
        printf("Idade: %d\n", atual->dados->idade);
        printf("RG: %s\n", atual->dados->RG);
        atual = atual->proximo;
    }
    printf("\n");
}

int remover(Lista *lista, Elista *remover){
    if(lista->inicio==NULL){
        return 1;
    }
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && atual != remover){
        anterior = atual;
        atual = atual->proximo;
    }
    //Caso valor nao encontrado na lista
    if(atual ==NULL){
        return 1;
    }
    if(anterior == NULL && atual != NULL){
        lista->inicio = atual->proximo;
        lista->qtd--;
        free(atual);
        return 0;
    }
    if(anterior != NULL && atual != NULL){
        anterior->proximo = atual->proximo;
        lista->qtd--;
        free(atual);
        return 0;
    }
    
    return 0;
}


//----------------------------------------------


//FILA | QUEUE

typedef struct Efila{
	Registro *dados;
    struct Efila *proximo;
} Efila;

typedef struct {
	Efila *head;
	Efila *tail;
	int qtd;
} Fila;

Efila *criarCelula(Registro *dados){
    Efila *nova = malloc(sizeof(Efila));
    nova->proximo = NULL;
    nova->dados = dados;
    return nova;
}

Fila *criarFila(){
    Fila *fila = malloc(sizeof(fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtd = 0;

    return fila;
}

void enfileirar(Fila *fila, Registro *dados){
    Efila *nova = criarCelula(dados);
    
    if(fila->qtd == 0){
        fila->head = nova;
    }else{
        fila->tail->proximo = nova;
    }
    fila->tail = nova;
    fila->qtd++;
} 

void desenfileirar(Fila *fila){
    if(fila->qtd == 0){
        return -1;
    }

    Efila *liberar = fila->head;
    //Registro *dados = fila->head->dados;

    if(fila->qtd == 1){
        fila->head = NULL;
        fila->tail = NULL;
    }else{
        fila->head = fila->head->proximo;
    }
    fila->qtd--;
    free(liberar);
    //return valor;
}

void mostrarFila(Fila *fila){
    printf("HEAD - > ");
    Efila *atual = fila->head;
    while(atual != NULL){
        printf("------------------------------------\n");
        printf("Nome: %s\n", atual->dados->nome);
        printf("Entrada: %d/", atual->dados->entrada->dia);
        printf("%d/", atual->dados->entrada->mes);
        printf("%d\n", atual->dados->entrada->ano);
        printf("Idade: %d\n", atual->dados->idade);
        printf("RG: %s\n", atual->dados->RG);
        atual = atual->proximo;
    }
    printf("<- TAIL");
    
    printf("\n");
}

//------------------------------------------------

typedef struct {
    Registro dados[CAP];
    int qtde;
  } heap;

//-------------------------------------------------

Elista *procurarPaciente(Lista *l){
    if(l->inicio == NULL){
        printf("Sem pacientes.\n");
        return;
    }
    Elista *atual = l->inicio;

    char rg[200];
    printf("Digite o RG do paciente: ");
    
    fgets(rg, 100, stdin);
    rg[strcspn(rg, "\n")] = '\0';

    while(atual != NULL && strcmp(atual->dados->RG, rg) != 0){
            atual = atual->proximo;
    }
    if(atual == NULL){
        printf("Paciente nâo encontrado\n");
        return;
    }

    return atual;
}

void cadastrar(Lista *l){
    while(1){
        int opcao;

        printf("1 - Cadastrar novo paciente\n");
        printf("2 - Consultar paciente\n");
        printf("3 - Mostrar lista completa\n");
        printf("4 - Atualizar dados de paciente\n");
        printf("5 - Remover paciente\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1: {
            Data dataAtual;
            pegarDataAtual(&dataAtual);
    
            Registro *r = malloc(sizeof(Registro));;
            addRegistro(r, &dataAtual);
            inserir(l, r);
            break;
        }
        case 2:{
            Elista *atual = procurarPaciente(l);
            printf("Nome: %s\n", atual->dados->nome);
            printf("Entrada: %d/", atual->dados->entrada->dia);
            printf("%d/", atual->dados->entrada->mes);
            printf("%d\n", atual->dados->entrada->ano);
            printf("Idade: %d\n", atual->dados->idade);
            printf("RG: %s\n", atual->dados->RG);
            break;
        }
        case 3:
            if(l->inicio == NULL){
                printf("Sem pacientes.\n");
                break;
            }
            mostrar(l);
            break;
        case 4: {
            Elista *atual = procurarPaciente(l);
            printf("Nome: %s\n", atual->dados->nome);
            printf("Entrada: %d/", atual->dados->entrada->dia);
            printf("%d/", atual->dados->entrada->mes);
            printf("%d\n", atual->dados->entrada->ano);
            printf("Idade: %d\n", atual->dados->idade);
            printf("RG: %s\n", atual->dados->RG);
            
            printf("Alterar\n");
            printf("1 - Nome   2 - Idade   3 - RG\n");

            int opcao2;

            scanf("%d", &opcao2);
            if(opcao2 == 1){
                printf("Digite o novo nome do paciente: \n");
                clearBuffer();
                fgets(atual->dados->nome, 100, stdin);
                atual->dados->nome[strcspn(atual->dados->nome, "\n")] = '\0';
            }else if(opcao2 == 2){
                printf("Digite a idade: ");
                scanf("%d", &atual->dados->idade);
                getchar(); 
            }else if(opcao2 == 3){
                printf("Digite o novo RG do paciente: \n");
                clearBuffer();
                fgets(atual->dados->RG, 100, stdin);
                atual->dados->RG[strcspn(atual->dados->RG, "\n")] = '\0';
            }
            break;
        }
        case 5: {
            Elista *atual = procurarPaciente(l);
            if(remover(l, atual) == 0){
                printf("Removido com suceeso!\n");
            }else{
                printf("Erro ao remover\n");
            }
            break;
        }
        case 0:
            main();
        }
    }
    
}

void atendimento(Fila *fila){
    while(1){
        int opcao;

        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1: {
            printf("Digite o RG do paciente que deseja adicionar na fila: \n");

            //enfileirar(fila);
        }
        case 0:
            main();
        }
    }
}

void atendimentoP(){
    while(1){
        int opcao;

        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void pesquisa(){
    while(1){
        int opcao;

        printf("1 - Mostrar por ano\n");
        printf("2 - Mostrar por mes\n");
        printf("3 - Mostrar por dia\n");
        printf("4 - Mostrar por idade\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void desfazer(){
    while(1){
        int opcao;

        printf("1 - Mostrar operacoes fila de atendimento\n");
        printf("2 - Desfazer ultima operacao\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void arquivo(){
    while(1){
        int opcao;

        printf("1 - Carregar dados\n");
        printf("2 - Salvar dados\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void sobre(){
    printf("Eduardo Gonçalves Moreira\n");
    printf("David Gabriel de Souza Batista\n");
    printf("3° Ciclo\n");
    printf("Ciencias da Computacao\n");
    printf("Estrutura de Dados\n");
    main();
}


void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(){
    Lista *l = criar_lista();
    Fila *fila = criarFila();

    while(1){
        int opcao;

        printf("Escolha uma opção:\n");
        printf("1 - Cadastrar\n");
        printf("2 - Atendimento\n");
        printf("3 - Atendimento prioritário\n");
        printf("4 - Pesquisa\n");
        printf("5 - Desfazer\n");
        printf("6 - Carregar / Salvar\n");
        printf("7 - Sobre\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastrar(l);
        case 2:
            atendimento(fila);
        case 3:
            atendimentoP();
        case 4:
            pesquisa();
        case 5:
            desfazer();
        case 6:
            arquivo();
        case 7:
            sobre();
        case 0:
            printf("Encerrando\n");
            exit(0);
        }
        
    }

    return 1;
}