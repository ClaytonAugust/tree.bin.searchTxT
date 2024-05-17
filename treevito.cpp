#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    
    return root;
}

// Função para buscar um valor na árvore
Node* searchNode(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

// Função para percorrer a árvore em pré-ordem (pre-order)
void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Função para percorrer a árvore em ordem (in-order)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Função para percorrer a árvore em pós-ordem (post-order)
void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Função para esvaziar a árvore
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int choice, data;
    Node* searchedNode = NULL; // Declaração de searchedNode fora do bloco switch
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Criar árvore vazia\n");
        printf("2. Inserir raiz\n");
        printf("3. Inserir nó à direita\n");
        printf("4. Inserir nó à esquerda\n");
        printf("5. Mostrar árvore\n");
        printf("6. Esvaziar árvore\n");
        printf("7. Buscar valor\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                root = NULL;
                printf("Árvore criada vazia.\n");
                break;
            case 2:
                printf("Digite o valor da raiz: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                printf("Raiz inserida com sucesso.\n");
                break;
            case 3:
                printf("Digite o valor do nó à direita: ");
                scanf("%d", &data);
                if (root == NULL) {
                    printf("Árvore vazia. Insira a raiz primeiro.\n");
                } else {
                    root->right = insertNode(root->right, data);
                    printf("Nó inserido à direita com sucesso.\n");
                }
                break;
            case 4:
                printf("Digite o valor do nó à esquerda: ");
                scanf("%d", &data);
                if (root == NULL) {
                    printf("Árvore vazia. Insira a raiz primeiro.\n");
                } else {
                    root->left = insertNode(root->left, data);
                    printf("Nó inserido à esquerda com sucesso.\n");
                }
                break;
            case 5:
                printf("Árvore em pré-ordem: ");
                preorderTraversal(root);
                printf("\nÁrvore em ordem: ");
                inorderTraversal(root);
                printf("\nÁrvore em pós-ordem: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                freeTree(root);
                root = NULL;
                printf("Árvore esvaziada com sucesso.\n");
                break;
            case 7:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &data);
                searchedNode = searchNode(root, data); // Atribuição do resultado de searchNode a searchedNode
                if (searchedNode != NULL) {
                    printf("Valor encontrado: %d\n", searchedNode->data);
                } else {
                    printf("Valor não encontrado na árvore.\n");
                }
                break;
            case 8:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    
    return 0;
}