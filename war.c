#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Definição da struct Territorio
// Representa um território com nome, cor do exército e número de tropas
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Número de tropas no território
} Territorio;

int main() {
    Territorio territorios[QTD_TERRITORIOS]; // Vetor para armazenar 5 territórios

    printf("=== Cadastro de Territórios - Projeto War ===\n\n");

    // Loop para entrada de dados dos 5 territórios
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Cadastro do %do território:\n", i + 1);

        // Entrada do nome do território
        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até a quebra de linha

        // Entrada da cor do exército
        printf("Cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor); // Lê até a quebra de linha

        // Entrada do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Espaço entre cadastros
    }

    // Exibição dos dados cadastrados
    printf("=== Dados dos Territórios Cadastrados ===\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
