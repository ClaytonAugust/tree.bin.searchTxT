#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("(%d, %s) ", raiz->dado.RGM, raiz->dado.nome);
        exibirPreOrdem(raiz->esquerda);
        exibirPreOrdem(raiz->direita);
    }
}

void exibirInOrdem(No *raiz) {
    if (raiz != NULL) {
        exibirInOrdem(raiz->esquerda);
        printf("(%d, %s) ", raiz->dado.RGM, raiz->dado.nome);
        exibirInOrdem(raiz->direita);
    }
}

void exibirPosOrdem(No *raiz) {
    if (raiz != NULL) {
        exibirPosOrdem(raiz->esquerda);
        exibirPosOrdem(raiz->direita);
        printf("(%d, %s) ", raiz->dado.RGM, raiz->dado.nome);
    }
}

void esvaziarArvore(No *raiz) {
    if (raiz != NULL) {
        esvaziarArvore(raiz->esquerda);
        esvaziarArvore(raiz->direita);
        free(raiz);
    }
}

// Função para exibir a árvore graficamente
void exibirArvoreGraficamente(No *raiz, int espaco) {
    if (raiz == NULL)
        return;

    espaco += 10;

    // Exibir o nó direito primeiro
    exibirArvoreGraficamente(raiz->direita, espaco);

    // Imprimir este nó
    printf("\n");
    for (int i = 10; i < espaco; i++)
        printf(" ");
    printf("%d, %s\n", raiz->dado.RGM, raiz->dado.nome);

    // Exibir o nó esquerdo
    exibirArvoreGraficamente(raiz->esquerda, espaco);
}

int main() {
    No *raiz = NULL;
    FILE *arquivo;
    t_elemento elemento;
    int opcao, RGM;

    // Abrir arquivo
    arquivo = fopen("F:/minhafaculdade/Webapi/tree.bin.searchTxT/TREE/dados.txt", "r");
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
        printf("2 - REMOVER UM NÓ\n");
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
                        exibirArvoreGraficamente(raiz, 0);
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
                        exibirArvoreGraficamente(raiz, 0);
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
