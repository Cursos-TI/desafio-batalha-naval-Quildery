#include <stdio.h>

int main() {
    // Inicializa o tabuleiro 10x10 com água (0)
    int tabuleiro[10][10] = {0};
    
    // Array para identificar as linhas com letras
    char linhas[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    // Define as posições dos navios (cada um com tamanho 3)
    // Navio 1: horizontal, linha B (índice 1), colunas 0,1,2
    int navio1[3][2] = {{1,0}, {1,1}, {1,2}}; // B0, B1, B2
    
    // Navio 2: vertical, coluna 7, linhas F,G,H (índices 5,6,7)
    int navio2[3][2] = {{5,7}, {6,7}, {7,7}}; // F7, G7, H7
    
    // Navio 3: diagonal, posições (3,3), (4,4), (5,5)
    int navio3[3][2] = {{3,3}, {4,4}, {5,5}}; // D3, E4, F5
    
    // Navio 4: diagonal inversa, posições (0,9), (1,8), (2,7)
    int navio4[3][2] = {{0,9}, {1,8}, {2,7}}; // A9, B8, C7
    
    // Verifica se há sobreposição entre navios
    int sobreposicao = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (navio1[i][0] == navio2[j][0] && navio1[i][1] == navio2[j][1]) sobreposicao = 1;
            if (navio1[i][0] == navio3[j][0] && navio1[i][1] == navio3[j][1]) sobreposicao = 1;
            if (navio1[i][0] == navio4[j][0] && navio1[i][1] == navio4[j][1]) sobreposicao = 1;
            if (navio2[i][0] == navio3[j][0] && navio2[i][1] == navio3[j][1]) sobreposicao = 1;
            if (navio2[i][0] == navio4[j][0] && navio2[i][1] == navio4[j][1]) sobreposicao = 1;
            if (navio3[i][0] == navio4[j][0] && navio3[i][1] == navio4[j][1]) sobreposicao = 1;
        }
    }
    
    if (sobreposicao) {
        printf("Erro: Navios se sobrepõem!\n");
        return 1;
    }
    
    // Posiciona os navios no tabuleiro (marca com 3)
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio1[i][0]][navio1[i][1]] = 3;
        tabuleiro[navio2[i][0]][navio2[i][1]] = 3;
        tabuleiro[navio3[i][0]][navio3[i][1]] = 3;
        tabuleiro[navio4[i][0]][navio4[i][1]] = 3;
    }
    
    // Define matrizes de habilidades 5x5
    int habilidade_cone[5][5] = {0};
    int habilidade_cruz[5][5] = {0};
    int habilidade_octaedro[5][5] = {0};
    
    // Preenche a habilidade em cone (topo na linha 0, coluna 2, expansão para baixo)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= (2 - i) && j <= (2 + i) && i <= 2) {
                habilidade_cone[i][j] = 1;
            }
        }
    }
    
    // Preenche a habilidade em cruz (centro em (2,2))
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                habilidade_cruz[i][j] = 1;
            }
        }
    }
    
    // Preenche a habilidade em octaedro (losango, centro em (2,2))
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int di = i - 2 >= 0 ? i - 2 : -(i - 2); // Substitui abs
            int dj = j - 2 >= 0 ? j - 2 : -(j - 2); // Substitui abs
            if (di + dj <= 1) { // Losango menor
                habilidade_octaedro[i][j] = 1;
            }
        }
    }
    
    // Define pontos de origem para as habilidades no tabuleiro
    int origem_cone[2] = {2, 4}; // C4
    int origem_cruz[2] = {5, 2}; // F2
    int origem_octaedro[2] = {8, 8}; // I8
    
    // Sobrepor habilidades ao tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Habilidade Cone
            int linha_tab = origem_cone[0] - 2 + i;
            int col_tab = origem_cone[1] - 2 + j;
            if (linha_tab >= 0 && linha_tab < 10 && col_tab >= 0 && col_tab < 10) {
                if (habilidade_cone[i][j] == 1 && tabuleiro[linha_tab][col_tab] != 3) {
                    tabuleiro[linha_tab][col_tab] = 5;
                }
            }
            
            // Habilidade Cruz
            linha_tab = origem_cruz[0] - 2 + i;
            col_tab = origem_cruz[1] - 2 + j;
            if (linha_tab >= 0 && linha_tab < 10 && col_tab >= 0 && col_tab < 10) {
                if (habilidade_cruz[i][j] == 1 && tabuleiro[linha_tab][col_tab] != 3) {
                    tabuleiro[linha_tab][col_tab] = 5;
                }
            }
            
            // Habilidade Octaedro
            linha_tab = origem_octaedro[0] - 2 + i;
            col_tab = origem_octaedro[1] - 2 + j;
            if (linha_tab >= 0 && linha_tab < 10 && col_tab >= 0 && col_tab < 10) {
                if (habilidade_octaedro[i][j] == 1 && tabuleiro[linha_tab][col_tab] != 3) {
                    tabuleiro[linha_tab][col_tab] = 5;
                }
            }
        }
    }
    
    // Exibe o tabuleiro
    printf("Tabuleiro de Batalha Naval com Habilidades:\n");
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    for (int i = 0; i < 10; i++) {
        printf("%c ", linhas[i]);
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~"); // Água
            else if (tabuleiro[i][j] == 3) printf(" N"); // Navio
            else if (tabuleiro[i][j] == 5) printf(" X"); // Área de efeito
        }
        printf("\n");
    }
    
    // Exibe as matrizes de habilidades
    printf("\nHabilidade Cone (centro C4):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf(" %d", habilidade_cone[i][j]);
        }
        printf("\n");
    }
    
    printf("\nHabilidade Cruz (centro F2):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf(" %d", habilidade_cruz[i][j]);
        }
        printf("\n");
    }
    
    printf("\nHabilidade Octaedro (centro I8):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf(" %d", habilidade_octaedro[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
