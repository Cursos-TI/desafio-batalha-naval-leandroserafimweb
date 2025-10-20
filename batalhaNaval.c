#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3
#define HABILIDADE 5

// ---------- FUNÇÕES DO TABULEIRO E NAVIOS ----------

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

int verificarEspaco(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    // 0 = horizontal, 1 = vertical, 2 = diagonal principal, 3 = diagonal secundária
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
        case 2: // Diagonal principal
            if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0;
            for (int k = 0; k < TAM_NAVIO; k++)
                if (tabuleiro[linha + k][coluna + k] != 0) return 0;
            break;
        case 3: // Diagonal secundária
            if (linha + TAM_NAVIO > TAM || coluna - TAM_NAVIO + 1 < 0) return 0;
            for (int k = 0; k < TAM_NAVIO; k++)
                if (tabuleiro[linha + k][coluna - k] != 0) return 0;
            break;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    switch (orientacao) {
        case 0:
            for (int j = 0; j < TAM_NAVIO; j++)
                tabuleiro[linha][coluna + j] = NAVIO;
            break;
        case 1:
            for (int i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linha + i][coluna] = NAVIO;
            break;
        case 2:
            for (int k = 0; k < TAM_NAVIO; k++)
                tabuleiro[linha + k][coluna + k] = NAVIO;
            break;
        case 3:
            for (int k = 0; k < TAM_NAVIO; k++)
                tabuleiro[linha + k][coluna - k] = NAVIO;
            break;
    }
}

// ---------- FUNÇÕES DE HABILIDADE ----------

void criarCone(int cone[HABILIDADE][HABILIDADE]) {
    for (int i = 0; i < HABILIDADE; i++) {
        for (int j = 0; j < HABILIDADE; j++) {
            if (j >= (HABILIDADE / 2 - i) && j <= (HABILIDADE / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

void criarCruz(int cruz[HABILIDADE][HABILIDADE]) {
    int meio = HABILIDADE / 2;
    for (int i = 0; i < HABILIDADE; i++) {
        for (int j = 0; j < HABILIDADE; j++) {
            if (i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

void criarOctaedro(int octaedro[HABILIDADE][HABILIDADE]) {
    int meio = HABILIDADE / 2;
    for (int i = 0; i < HABILIDADE; i++) {
        for (int j = 0; j < HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HABILIDADE][HABILIDADE], int origemLinha, int origemColuna) {
    int offset = HABILIDADE / 2;

    for (int i = 0; i < HABILIDADE; i++) {
        for (int j = 0; j < HABILIDADE; j++) {
            int linha = origemLinha - offset + i;
            int coluna = origemColuna - offset + j;

            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5; // Marca área afetada
                }
            }
        }
    }
}

// ---------- EXIBIÇÃO ----------

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n========= TABULEIRO BATALHA NAVAL =========\n\n");
    printf("    ");
    for (int c = 0; c < TAM; c++) printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAM; j++) {
            int valor = tabuleiro[i][j];
            if (valor == 0)
                printf(" ~ ");  // Água
            else if (valor == 3)
                printf(" N ");  // Navio
            else if (valor == 5)
                printf(" * ");  // Habilidade
        }
        printf("|\n");
    }
    printf("\n===========================================\n");
}


int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posições e orientações dos 4 navios
    int posicoes[4][3] = {
        {1, 2, 0}, // Horizontal
        {5, 5, 1}, // Vertical
        {0, 0, 2}, // Diagonal principal
        {0, 9, 3}  // Diagonal secundária
    };

    for (int n = 0; n < 4; n++) {
        int linha = posicoes[n][0];
        int coluna = posicoes[n][1];
        int orientacao = posicoes[n][2];

        if (verificarEspaco(tabuleiro, linha, coluna, orientacao))
            posicionarNavio(tabuleiro, linha, coluna, orientacao);
        else {
            printf("Erro ao posicionar navio %d!\n", n + 1);
            return 1;
        }
    }

    // Criação das matrizes de habilidades
    int cone[HABILIDADE][HABILIDADE];
    int cruz[HABILIDADE][HABILIDADE];
    int octaedro[HABILIDADE][HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 4);     // Cone centrado no (2,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 7);    // Cruz centrada no (7,7)
    aplicarHabilidade(tabuleiro, octaedro, 5, 2); // Octaedro centrado no (5,2)

    // Exibir resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
