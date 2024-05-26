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

/*pega os dados do elemento na estrutura de variaveis e
  se esquerda e direita estivar nulo, vai criar um novo
  nó com a alocação dinamica de memoria do tamanho do no*/
  
No *criarNo(t_elemento dado) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

/*Pega o dado.RGM e compara se for menor que a raiz e raiz aponta
  para dado.rgm para também ser comparado ele passa para a esquerda.
  se dado.RGM for maior que raiz aponta para dado.RGM vai passar
  para a direita*/

No *inserir(No *raiz, t_elemento dado) {
    if (raiz == NULL)
        return criarNo(dado);

    if (dado.RGM < raiz->dado.RGM)
        raiz->esquerda = inserir(raiz->esquerda, dado);
    else if (dado.RGM > raiz->dado.RGM)
        raiz->direita = inserir(raiz->direita, dado);

    return raiz;
}

/*Ele vai procurar pelo RGM se existe ou não e depois ele vai buscar se raiz aponta
  para dado.RGM for menor que o RGM que o usuário inseriu ele vai buscar para a direita
  senão vai buscar para o que estiver na esquerda, fazendo esse "loop" até encontrar o RGM*/

No *buscar(No *raiz, int RGM) {
    if (raiz == NULL || raiz->dado.RGM == RGM)
        return raiz;

    if (raiz->dado.RGM < RGM)
        return buscar(raiz->direita, RGM);

    return buscar(raiz->esquerda, RGM);
}

/*Função para remover, ele faz a comparação se a raiz estiver vazia ele retornará null,
  vai percorrer recursivamente  se o RGM a ser removido é menor que o RGM da raiz ele
  chama remover recursivamente na subárvore esquerda, se o RGM for maior que o RGM da raiz
  chama remover recursivamente na subárvore direita, ao ser encontrado o RGM e se caso coincide
   com o RGM da raiz, lida com os três casos possíveis */

No *remover(No *raiz, int RGM) {
	//Caso árvore está vazia
    if (raiz == NULL)
        return raiz;
	//percorrer a árvore recursivamente
    if (RGM < raiz->dado.RGM)
    	//RGM está na subárvore esquerda
        raiz->esquerda = remover(raiz->esquerda, RGM);
    else if (RGM > raiz->dado.RGM)
    	//O RGM está na subárvore direita
        raiz->direita = remover(raiz->direita, RGM);
    else {//no com um único filho ou sem
    
    	// se o filho esquerdo é nulo retonar filho direito
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        //se o filho direito é nulo retorna filho esquerdo
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
		//(Nó com dois filhos) Encontra o sucessor em ordem o menor nó na subárvore direita
        No *temp = raiz->direita;
        while (temp->esquerda != NULL)
            temp = temp->esquerda;
		//substitui os dados do nó pelos dados do sucessor em ordem
        raiz->dado = temp->dado;
		//Remove o sucessor em ordem
        raiz->direita = remover(raiz->direita, temp->dado.RGM);
    }
    return raiz;
}
//funções para exibir nós tres tipos os dados armazenados na arvore
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
//função para limpar toda a arvore
void esvaziarArvore(No *raiz) {
    if (raiz != NULL) {
        esvaziarArvore(raiz->esquerda);
        esvaziarArvore(raiz->direita);
        free(raiz);
    }
}
// função para mover o cursor para linha e coluna
void gotoxy(int coluna, int linha){
	COORD point;
	point.X = coluna;
	point.Y = linha;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

/* função usada para limpar terminal para que não ocorra
   problemas de exibição para o cliente*/
   
void limparTerminal() {
    system("cls || clear");
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
		//cada inserção vai ser deslocado 4 linhas
		exibirArvoreGraficamente(raiz->esquerda, col-desloc, lin+4, desloc/2+1);

	if(raiz->direita != NULL)
		exibirArvoreGraficamente(raiz->direita, col+desloc, lin+4, desloc/2+1);
}
/*Essa função ela vai alterar o diretorio de trabalho atual do programa
 para o diretorio onde o executavel do programa esta localizado*/
void mudarParaExeDiretorio(){
    char path[MAX_PATH];//armazenamento completo do caminho do .exe
    
	//Obtém o caminho do exe
    if(GetModuleFileName(NULL, path, MAX_PATH) == 0) {
        perror("GetModuleFileName() erro");
        exit(EXIT_FAILURE);
    }
	//encontrando o diretorio do exe
    char *dir_end = strrchr(path, '\\');
    if (dir_end != NULL) {
        *dir_end = '\0';
    }
	//mudar para o diretorio do exe
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
        getchar();

        switch (opcao) {
            case 1:
            	limparTerminal();
                printf("Digite o RGM e o Nome do aluno: ");
                scanf("%d %[^\n]", &elemento.RGM, elemento.nome);
                getchar();
                raiz = inserir(raiz, elemento);
                printf("O aluno com RGM %d foi inserido com sucesso!\n", elemento.RGM);
                break;
            case 2:
            	limparTerminal();
                printf("Digite o RGM a remover: ");
                scanf("%d", &RGM);
                getchar();

                if (buscar(raiz, RGM) != NULL){
                    printf("O RGM %d está presente na árvore e foi removido.\n", RGM);
                    raiz = remover(raiz, RGM);
            	
                	printf("Exibindo a árvore:\n");
                
                	printf("Pré-Ordem: ");
                	exibirPreOrdem(raiz);
                	printf("\n");
                
                	printf("In-Ordem: ");
            		exibirInOrdem(raiz);
                	printf("\n");
                
                	printf("Pós-Ordem: ");
                	exibirPosOrdem(raiz);
                	printf("\n");
                
					printf("Exibindo a árvore graficamente:\n");
                	exibirArvoreGraficamente(raiz, 50 , 10 , 35);
                	printf("\n");
                }
                else{
                    printf("O RGM %d não está presente na árvore.\n", RGM);
                }
                break;
            case 3:
            	
                printf("Digite o RGM a pesquisar: ");
                scanf("%d", &RGM);
                getchar();
                
                if (buscar(raiz, RGM) != NULL)
                    printf("O RGM %d está presente na árvore, aperta enter para continuar.\n", RGM);
                else{
                	printf("O RGM %d não está presente na árvore, aperta enter para continuar.\n", RGM);
				}
                while (getchar() != '\n');
                	limparTerminal();
                break;
            case 4:
                esvaziarArvore(raiz);
                raiz = NULL;
                printf("A árvore foi esvaziada.\n");
                break;
            case 5:
            	limparTerminal();
                printf("Exibindo a árvore:\n");
                
                printf("Pré-Ordem: ");
                exibirPreOrdem(raiz);
                printf("\n");
                
                printf("In-Ordem: ");
            	exibirInOrdem(raiz);
                printf("\n");
                
                printf("Pós-Ordem: ");
                exibirPosOrdem(raiz);
                printf("\n");
                
				printf("Exibindo a árvore graficamente:\n");
                exibirArvoreGraficamente(raiz, 50 , 10 , 35);
                printf("\n");
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
