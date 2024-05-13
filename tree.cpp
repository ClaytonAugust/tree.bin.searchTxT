#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da árvore
struct Node {
    int data;
    struct Node *left, *right;
};

// Função para criar um novo nó
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Função para inserir um novo nó na árvore
struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data > node->data)
        node->left = insert(node->left, data);
    else if (data < node->data)
        node->right = insert(node->right, data);

    return node;
}

// Função para encontrar o nó com o valor mínimo
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Função para remover um nó da árvore
struct Node* removeNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = removeNode(root->left, key);
    else if (key > root->data)
        root->right = removeNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);

        root->data = temp->data;

        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

// Função para exibir a árvore em ordem
void inOrder(struct Node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%d ", node->data);
        inOrder(node->right);
    }
}

// Função para desenhar a árvore em formato textual
void printTree(struct Node* node, int space) {
    if (node == NULL)
        return;

    // Aumenta o espaço
    space += 10;

    // Processa o nó direito primeiro
    printTree(node->right, space);

    // Imprime este nó
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", node->data);

    // Processa o nó esquerdo
    printTree(node->left, space);
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir um elemento\n");
        printf("2. Remover um elemento\n");
        printf("3. Exibir a arvore\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Insira o elemento a ser inserido: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Insira o elemento a ser removido: ");
                scanf("%d", &data);
                root = removeNode(root, data);
                break;
            case 3:
                printf("Arvore em ordem:\n");
                inOrder(root);
                printf("\n\nArvore:\n");
                printTree(root, 0);
                break;
            case 4:
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
