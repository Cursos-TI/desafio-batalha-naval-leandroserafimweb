#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se há espaço livre e se o navio cabe dentro dos limites
int verificarEspaco(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    // 0: horizontal | 1: vertical | 2: diagonal principal | 3: diagonal secundária
    switch (orientacao) {
        case 0: // Horizontal
            if (coluna + TAM_NAVIO > TAM) return 0;
            for (int j = 0; j < TAM_NAVIO; j++)
                if (tabuleiro[linha][coluna + j] != 0) return 0;
            break;

        case 1: // Vertical
            if (linha + TAM_NAVIO > TAM) return 0;
            for (int i = 0; i < TAM_NAVIO; i++)
                if (tabuleiro[linha + i][coluna] != 0) return 0;
            break;

        case 2: // Diagonal principal (\)
            if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0;
            for (int k = 0; k < TAM_NAVIO; k++)
                if (tabuleiro[linha + k][coluna + k] != 0) return 0;
            break;

        case 3: // Diagonal secundária (/)
            if (linha + TAM_NAVIO > TAM || coluna - TAM_NAVIO + 1 < 0) return 0;
            for (int k = 0; k < TAM_NAVIO; k++)
                if (tabuleiro[linha + k][coluna - k] != 0) return 0;
            break;
    }
    return 1;
}

// Posiciona o navio de acordo com a orientação
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    switch (orientacao) {
        case 0: // Horizontal
            for (int j = 0; j < TAM_NAVIO; j++)
                tabuleiro[linha][coluna + j] = NAVIO;
            break;

        case 1: // Vertical
            for (int i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linha + i][coluna] = NAVIO;
            break;

        case 2: // Diagonal principal (\)
            for (int k = 0; k < TAM_NAVIO; k++)
                tabuleiro[linha + k][coluna + k] = NAVIO;
            break;

        case 3: // Diagonal secundária (/)
            for (int k = 0; k < TAM_NAVIO; k++)
                tabuleiro[linha + k][coluna - k] = NAVIO;
            break;
    }
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n======= TABULEIRO BATALHA NAVAL =======\n\n");
    printf("    ");
    for (int c = 0; c < TAM; c++) printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("|\n");
    }
    printf("\n=======================================\n");
}

int main() {
     int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas e orientações pré-definidas
    // Orientações: 0 = horizontal | 1 = vertical | 2 = diagonal principal | 3 = diagonal secundária
    int posicoes[4][3] = {
        {1, 2, 0}, // Navio 1 - Horizontal
        {5, 5, 1}, // Navio 2 - Vertical
        {0, 0, 2}, // Navio 3 - Diagonal principal (\)
        {0, 9, 3}  // Navio 4 - Diagonal secundária (/)
    };

    for (int n = 0; n < 4; n++) {
        int linha = posicoes[n][0];
        int coluna = posicoes[n][1];
        int orientacao = posicoes[n][2];

        if (verificarEspaco(tabuleiro, linha, coluna, orientacao)) {
            posicionarNavio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Erro ao posicionar navio %d (linha %d, coluna %d, orientacao %d)\n",
                   n + 1, linha, coluna, orientacao);
            return 1;
        }
    }

    exibirTabuleiro(tabuleiro);
    return 0;
}
