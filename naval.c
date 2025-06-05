#include <stdio.h>

int main() {

    int tabuleiro[10][10] = {0};

    
    char linhas[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    int navio1[3][2] = {{2,2}, {2,3}, {2,4}};
    
    int navio2[3][2] = {{5,7}, {6,7}, {7,7}}; 
    
    
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio1[i][0]][navio1[i][1]] = 3; // Navio 1
        tabuleiro[navio2[i][0]][navio2[i][1]] = 3; // Navio 2
    }
    
    // Exibe o tabuleiro
    printf("Tabuleiro de Batalha Naval:\n");
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    for (int i = 0; i < 10; i++) {
        printf("%c ", linhas[i]); 
        for (int j = 0; j < 10; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}


