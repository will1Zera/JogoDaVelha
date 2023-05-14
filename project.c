#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3

char board[BOARD_SIZE][BOARD_SIZE]; // Matriz do tabuleiro do jogo
char player1[20], player2[20]; // Nomes dos jogadores
char current_player; // Jogador atual
int num_plays; // Número de jogadas realizadas

// Cria o tabuleiro e preenche com ' '
void initialize_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Imprime o esqueleto do tabuleiro
void print_board() {
    printf("\n\n\t    1   2   3  \n\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\t%d  ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("\t   -----------\n");
        }
    }
    printf("\n\n");
}

// Pega os nomes dos jogadores
void get_player_names() {
    printf("Digite o nome do Jogador 1: ");
    scanf("%s", player1);
    printf("\nDigite o nome do Jogador 2: ");
    scanf("%s", player2);
}

// Pega os coordenadas da linha e da coluna
void get_move(int *row, int *col) {
    printf("%s, digite a linha e coluna que deseja jogar (exemplo: 1 2): ", current_player == 'X' ? player1 : player2);
    scanf("%d %d", row, col);
    (*row)--;
    (*col)--;
}

// Valida as coordenadas de linha e coluna passadas anteriormente
int is_valid_move(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return 0;
    }
    if (board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

// Realiza a jogada colocando X ou O no tabuleiro
void make_move(int row, int col) {
    board[row][col] = current_player;
    num_plays++;
}

// Verifica as possibilidades de vitória e empate
int check_winner() {
    // Verifica todas as linhas e colunas
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }
    // Verifica diagonais
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    // Verifica empate
    if (num_plays == BOARD_SIZE * BOARD_SIZE) {
        return 2;
    }
    return 0;
}

// Realiza as jogadas e diz se ganhou ou empatou
void play_game() {
    int row, col;
    int winner = 0;
    while (winner == 0) {
        print_board();
        get_move(&row, &col);
        while (!is_valid_move(row, col)) {
            printf("\nJogada invalida. Tente novamente.\n\n");
            get_move(&row, &col);
        }
        make_move(row, col);
        winner = check_winner();
        if (current_player == 'X') {
            current_player = 'O';
        } else {
            current_player = 'X';
        }
    }
    print_board();
    if (winner == 1) {
        printf("Parabens, %s! Voce venceu!\n", current_player == 'X' ? player2 : player1);
    } else {
        printf("Empate!\n");
    }
}

// Chama todas as funções e inicia o jogo com X
int main() {
    initialize_board();
    get_player_names();
    current_player = 'X';
    num_plays = 0;
    play_game();
    return 0;
}
