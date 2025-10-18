#include <stdio.h>

#define TAM 10   // Tamanho do tabuleiro
#define TAM_NAVIO 3  // Tamanho fixo dos navios

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

int verificarEspaco(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    // Retorna 1 se o navio cabe e não há sobreposição, senão 0.
    if (orientacao == 0) { // Horizontal
        if (coluna + TAM_NAVIO > TAM) return 0; // Fora do limite
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (tabuleiro[linha][coluna + j] != 0) return 0; // Sobreposição
        }
    } else { // Vertical
        if (linha + TAM_NAVIO > TAM) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
    }
    return 1;
}
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Horizontal
        for (int j = 0; j < TAM_NAVIO; j++) {
            tabuleiro[linha][coluna + j] = 3; // 3 representa navio
        }
    } else { // Vertical
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n--- TABULEIRO BATALHA NAVAL ---\n\n");
    printf("   ");
    for (int c = 0; c < TAM; c++) printf("%d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais dos navios (podem ser alteradas livremente)
    int linhaH = 2, colunaH = 4; // Navio 1 - Horizontal
    int linhaV = 5, colunaV = 7; // Navio 2 - Vertical

    // Validação e posicionamento do primeiro navio
    if (verificarEspaco(tabuleiro, linhaH, colunaH, 0)) {
        posicionarNavio(tabuleiro, linhaH, colunaH, 0);
    } else {
        printf("Erro: Navio horizontal fora dos limites ou sobreposto!\n");
        return 1;
    }

    // Validação e posicionamento do segundo navio
    if (verificarEspaco(tabuleiro, linhaV, colunaV, 1)) {
        posicionarNavio(tabuleiro, linhaV, colunaV, 1);
    } else {
        printf("Erro: Navio vertical fora dos limites ou sobreposto!\n");
        return 1;
    }

    // Exibição do tabuleiro completo
    exibirTabuleiro(tabuleiro);

    return 0;
}
