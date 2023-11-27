#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Produto
typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

// Definição da estrutura Node para a lista encadeada
typedef struct Node {
    Produto produto;
    struct Node *prox;
} Node;

// Função que inicializa uma lista vazia
Node* inicializaLista() {
    return NULL;
}

// Função que adiciona um novo produto à lista de estoque
Node* adicionaProduto(Node* lista, Produto novoProduto) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->produto = novoProduto;
    novoNode->prox = lista;
    return novoNode;
}

// Função que percorre a lista de estoque e imprime um relatório com as informações de cada produto
void imprimeRelatorio(Node* lista) {
    Node* atual = lista;

    printf("\nRelatório de Produtos:\n");
    while (atual != NULL) {
        printf("Código: %d\n", atual->produto.codigo);
        printf("Descrição: %s\n", atual->produto.descricao);
        printf("Quantidade: %d\n", atual->produto.quantidade);
        printf("Valor: %.2f\n\n", atual->produto.valor);

        atual = atual->prox;
    }
}

// Função que permite ao usuário pesquisar um produto pelo código
Node* pesquisaPorCodigo(Node* lista, int codigo) {
    Node* atual = lista;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}

// Função que permite ao usuário remover um produto do estoque
Node* removeProduto(Node* lista, int codigo) {
    Node *atual = lista, *anterior = NULL;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            if (anterior == NULL) {
                // Remoção do primeiro elemento
                lista = atual->prox;
            } else {
                // Remoção de um elemento no meio ou final
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Produto removido com sucesso.\n");
            return lista;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Produto não encontrado.\n");
    return lista;
}

int main() {
    Node* lista = inicializaLista();
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Imprimir Relatório\n");
        printf("3. Pesquisar Produto por Código\n");
        printf("4. Remover Produto\n");
        printf("0. Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Produto novoProduto;
                printf("Digite o código do produto: ");
                scanf("%d", &novoProduto.codigo);
                printf("Digite a descrição do produto: ");
                scanf("%s", novoProduto.descricao);
                printf("Digite a quantidade do produto: ");
                scanf("%d", &novoProduto.quantidade);
                printf("Digite o valor do produto: ");
                scanf("%f", &novoProduto.valor);

                lista = adicionaProduto(lista, novoProduto);
                printf("Produto adicionado com sucesso.\n");
                break;
            }
            case 2:
                imprimeRelatorio(lista);
                break;
            case 3: {
                int codigo;
                printf("Digite o código do produto: ");
                scanf("%d", &codigo);

                Node* resultado = pesquisaPorCodigo(lista, codigo);
                if (resultado != NULL) {
                    printf("Produto encontrado:\n");
                    printf("Descrição: %s\n", resultado->produto.descricao);
                    printf("Quantidade: %d\n", resultado->produto.quantidade);
                    printf("Valor: %.2f\n", resultado->produto.valor);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 4: {
                int codigo;
                printf("Digite o código do produto a ser removido: ");
                scanf("%d", &codigo);

                lista = removeProduto(lista, codigo);
                break;
            }
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    // Libera a memória alocada para a lista
    Node* atual = lista;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}
