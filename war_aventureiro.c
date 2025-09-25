#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do território
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Número de tropas
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("Cadastro do %do território:\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n=== Dados dos Territórios ===\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }
}

// Função que simula o ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("⚠️ O ataque não é permitido! Ambos os territórios pertencem ao mesmo exército.\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("⚠️ O atacante não possui tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n🎲 Rolagem dos dados:\n");
    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);   // muda a cor do exército
        defensor->tropas = atacante->tropas / 2; // metade das tropas vai para o defensor
        atacante->tropas = atacante->tropas - defensor->tropas; // ajusta tropas do atacante
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // atacante perde 1 tropa
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int qtdTerritorios;
    printf("Digite a quantidade de territórios a cadastrar: ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, qtdTerritorios);

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Exibir territórios\n");
        printf("2. Realizar ataque\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, qtdTerritorios);
        } else if (opcao == 2) {
            int iAtacante, iDefensor;
            exibirTerritorios(mapa, qtdTerritorios);

            printf("Escolha o número do território atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o número do território defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > qtdTerritorios ||
                iDefensor < 1 || iDefensor > qtdTerritorios) {
                printf("⚠️ Escolha inválida!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }
        }
    } while (opcao != 3);

    // Liberação da memória
    liberarMemoria(mapa);

    printf("Programa encerrado.\n");
    return 0;
}
