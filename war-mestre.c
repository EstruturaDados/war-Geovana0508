#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
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

// Função para exibir os territórios
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

// Função que simula um ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("⚠️ O ataque não é permitido! Ambos pertencem ao mesmo exército.\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("⚠️ O atacante não possui tropas suficientes!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n🎲 Dados lançados:\n");
    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("❌ O defensor resistiu!\n");
        atacante->tropas -= 1;
    }
}

// Atribui missão aleatória a um jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão de um jogador
void exibirMissao(char* missao) {
    printf("\n🎯 Sua missão: %s\n", missao);
}

// Verifica de forma simples se uma missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int qtd) {
    if (strstr(missao, "3 territorios")) {
        int count = 0;
        for (int i = 0; i < qtd; i++) {
            if (mapa[i].tropas > 0) count++;
        }
        return (count >= 3);
    }
    if (strstr(missao, "vermelha")) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0;
        }
        return 1;
    }
    return 0; // padrão para missões não implementadas
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int qtdJogadores) {
    free(mapa);
    for (int i = 0; i < qtdJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    srand(time(NULL));

    int qtdTerritorios, qtdJogadores;
    printf("Digite a quantidade de territórios: ");
    scanf("%d", &qtdTerritorios);
    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &qtdJogadores);

    // Aloca territórios
    Territorio* mapa = (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para territórios!\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(mapa, qtdTerritorios);

    // Missoes pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 2 territorios",
        "Manter pelo menos 1 territorio sempre protegido",
        "Ser o ultimo jogador restante"
    };
    int totalMissoes = 5;

    // Aloca missões para jogadores
    char** missoesJogadores = (char**) malloc(qtdJogadores * sizeof(char*));
    for (int i = 0; i < qtdJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("\nJogador %d:", i + 1);
        exibirMissao(missoesJogadores[i]);
    }

    int opcao, turno = 0, vencedor = -1;
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

            printf("Escolha o território atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o território defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > qtdTerritorios ||
                iDefensor < 1 || iDefensor > qtdTerritorios) {
                printf("⚠️ Escolha inválida!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }

            // Após cada ataque, verifica missão
            if (verificarMissao(missoesJogadores[turno % qtdJogadores], mapa, qtdTerritorios)) {
                vencedor = turno % qtdJogadores;
                break;
            }
            turno++;
        }
    } while (opcao != 3);

    if (vencedor != -1) {
        printf("\n🏆 Jogador %d cumpriu sua missão: %s\n", vencedor + 1, missoesJogadores[vencedor]);
    }

    liberarMemoria(mapa, missoesJogadores, qtdJogadores);

    printf("Programa encerrado.\n");
    return 0;
}
