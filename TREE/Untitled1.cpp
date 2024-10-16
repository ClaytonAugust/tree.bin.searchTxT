#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <locale.h>

typedef struct {
    int RGM;
    char nome[50];
} t_elemento;

typedef struct No {
    t_elemento dado;
    struct No *esquerda;
    struct No *direita;
} No;

No *criarNo(t_elemento dado) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

No *inserir(No *raiz, t_elemento dado) {
    if (raiz == NULL)
        return criarNo(dado);

    if (dado.RGM < raiz->dado.RGM)
        raiz->esquerda = inserir(raiz->esquerda, dado);
    else if (dado.RGM > raiz->dado.RGM)
        raiz->direita = inserir(raiz->direita, dado);

    return raiz;
}

No *buscar(No *raiz, int RGM) {
    if (raiz == NULL || raiz->dado.RGM == RGM)
        return raiz;

    if (raiz->dado.RGM < RGM)
        return buscar(raiz->direita, RGM);

    return buscar(raiz->esquerda, RGM);
}

No *remover(No *raiz, int RGM) {
    if (raiz == NULL)
        return raiz;

    if (RGM < raiz->dado.RGM)
        raiz->esquerda = remover(raiz->esquerda, RGM);
    else if (RGM > raiz->dado.RGM)
        raiz->direita = remover(raiz->direita, RGM);
    else {
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No *temp = raiz->direita;
        while (temp->esquerda != NULL)
            temp = temp->esquerda;

        raiz->dado = temp->dado;

        raiz->direita = remover(raiz->direita, temp->dado.RGM);
    }
    return raiz;
}

void exibirPreOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("(RGM: %d, NOME: %s) ", raiz->dado.RGM, raiz->dado.nome);
        exibirPreOrdem(raiz->esquerda);
        exibirPreOrdem(raiz->direita);
    }
}

void exibirInOrdem(No *raiz) {
    if (raiz != NULL) {
        exibirInOrdem(raiz->esquerda);
        printf("(RGM: %d, NOME: %s) ", raiz->dado.RGM, raiz->dado.nome);
        exibirInOrdem(raiz->direita);
    }
}

void exibirPosOrdem(No *raiz) {
    if (raiz != NULL) {
        exibirPosOrdem(raiz->esquerda);
        exibirPosOrdem(raiz->direita);
        printf("(RGM: %d, NOME: %s) ", raiz->dado.RGM, raiz->dado.nome);
    }
}

void esvaziarArvore(No *raiz) {
    if (raiz != NULL) {
        esvaziarArvore(raiz->esquerda);
        esvaziarArvore(raiz->direita);
        free(raiz);
    }
}
void gotoxy(int coluna, int linha){
	COORD point;
	point.X = coluna;
	point.Y = linha;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
// Função para exibir a árvore graficamente
void exibirArvoreGraficamente(No *raiz, int col, int lin, int desloc) {
	if(raiz == NULL)
		return;
	gotoxy(col,lin);
	printf("(RGM: %d", raiz->dado.RGM);
    gotoxy(col, lin + 1);
	printf(", NOME: %s)", raiz->dado.nome);

	if(raiz->esquerda != NULL)
		exibirArvoreGraficamente(raiz->esquerda, col-desloc, lin+3, desloc/2+1);

	if(raiz->direita != NULL)
		exibirArvoreGraficamente(raiz->direita, col+desloc, lin+3, desloc/2+1);
}

void mudarParaExeDiretorio(){
    char path[MAX_PATH];

    if(GetModuleFileName(NULL, path, MAX_PATH) == 0) {
        perror("GetModuleFileName() erro");
        exit(EXIT_FAILURE);
    }

    char *dir_end = strrchr(path, '\\');
    if (dir_end != NULL) {
        *dir_end = '\0';
    }

    if (_chdir(path) != 0) {
        perror("_chdir() erro");
        exit(EXIT_FAILURE);
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    No *raiz = NULL;
    No *raizEstatica = NULL;
    FILE *arquivo;
    t_elemento elemento;
    int opcao, RGM;
    int primeiroElementoInserido = 0;

    mudarParaExeDiretorio();

    // Abrir arquivo
    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler dados do arquivo e inserir na árvore
    while (fscanf(arquivo, "%d %[^\n]", &elemento.RGM, elemento.nome) != EOF) {
        raiz = inserir(raiz, elemento);
    }

    // Menu
    do {
        printf("\nMENU:\n");
        printf("1 - INSERIR\n");
        printf("2 - REMOVER UM Nó\n");
        printf("3 - PESQUISAR\n");
        printf("4 - ESVAZIAR A ÁRVORE\n");
        printf("5 - EXIBIR A ÁRVORE\n");
        printf("0 - SAIR\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        getchar(); // Consumir a nova linha deixada por scanf

        switch (opcao) {
            case 1:
                printf("Digite o RGM e o Nome do aluno: ");
                scanf("%d %[^\n]", &elemento.RGM, elemento.nome);
                raiz = inserir(raiz, elemento);
                break;
            case 2:
                printf("Digite o RGM a remover: ");
                scanf("%d", &RGM);

                if (buscar(raiz, RGM) != NULL){
                    printf("O RGM %d está presente na árvore.\n", RGM);
                    raiz = remover(raiz, RGM);

                    printf("\n");
                    printf("Exibindo a árvore:\n");
                    printf("\n");
                    printf("Pré-Ordem: ");
                    exibirPreOrdem(raiz);
                    printf("\n");
                    printf("\n");
                    printf("In-Ordem: ");
                    exibirInOrdem(raiz);
                    printf("\n");
                    printf("\n");
                    printf("Pós-Ordem: ");
                    exibirPosOrdem(raiz);
                    printf("\n");
                    printf("\n");
                    printf("Exibindo a árvore graficamente:\n");
                    exibirArvoreGraficamente(raiz, 50 , 20 , 15);
                }
                else{
                    printf("O RGM %d não está presente na árvore.\n", RGM);
                }
                break;
            case 3:
                printf("Digite o RGM a pesquisar: ");
                scanf("%d", &RGM);
                if (buscar(raiz, RGM) != NULL)
                    printf("O RGM %d está presente na árvore.\n", RGM);
                else
                    printf("O RGM %d não está presente na árvore.\n", RGM);
                break;
            case 4:
                esvaziarArvore(raiz);
                raiz = NULL;
                printf("A árvore foi esvaziada.\n");
                break;
            case 5:
                printf("\n");
                 printf("Exibindo a árvore:\n");
                  printf("\n");
                    printf("Pré-Ordem: ");
                        exibirPreOrdem(raiz);
                        printf("\n");
                         printf("\n");
                    printf("In-Ordem: ");
                        exibirInOrdem(raiz);
                        printf("\n");
                         printf("\n");
                    printf("Pós-Ordem: ");
                        exibirPosOrdem(raiz);
                        printf("\n");
                         printf("\n");
                    printf("Exibindo a árvore graficamente:\n");
                        exibirArvoreGraficamente(raiz, 40 , 22 , 40);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Fechar arquivo
    fclose(arquivo);

    return 0;
}
