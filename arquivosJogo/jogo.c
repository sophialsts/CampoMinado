#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define tamCampo 8

// ponteiro para armazenar quantidade de casas que o jogador conseguiu revelar
// struct para toda parte de arquivo, alocar memória pra ele e liberar depois de fechar o arquivo

enum casas {Vazio = 0, umaProx = 1, duasProx = 2, tresProx = 3, quatroProx = 4, naoRevelado = 5, Bomba = 6};
int lose = 1;
int (*M)[tamCampo] = NULL; //(*M) ponteiro para array
int revelados[tamCampo][tamCampo];

/*typedef struct{
        char nome[40];
        int dificuldade;
        int pontuação;
        int tempo;
    } Infos;*/

void alocaMemória() {
    M = malloc(tamCampo * sizeof(*M));

    if (M == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    return;
}


void liberaMemoria() {
    if (M != NULL) {
        free(M);
    }
}


void clean(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

/*int timer(){

    int segundos = 0;

    while(lose){ 
        sleep(1);
        segundos++;
    };

    return segundos;
}*/


void menu(){

    char start;

    printf("\n");
    printf("                                                         B E M     V I N D O      A O     C A M P O     M I N A D O\n");
    printf("                                                         ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
    printf("                                                                                         _❈ \n");
    printf("                                                                                        /\n");
    printf("                                                                                   ✩✩✩✩✩✩\n");
    printf("                                                                                 ✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                ✩✩✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                 ✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                  ✩✩✩✩✩✩✩\n\n");
    printf("                                                                         Clique enter para começar!");
    
    scanf("%c", &start);
    if(start == '\n') return;
    
}

int verificaCoordenadas(int linha, int coluna) {
    if (linha < 0 || linha >= tamCampo || coluna < 0 || coluna >= tamCampo) return 0; 
    return 1; 
}

void verificaVizinhos(int linha, int coluna){

    int i,j;
    int quantBomb = 0;


    for (i = linha - 1; i <= linha + 1; i++) {
        for (j = coluna - 1; j <= coluna + 1; j++) {
            if(M[i][j] == Bomba && verificaCoordenadas(i,j) == 1) quantBomb++;
            if(i == linha && j == coluna) continue;
        }
    }

    switch(quantBomb){
        case 0:
            M[linha][coluna] = Vazio;
            break;
        case 1:
            M[linha][coluna] = umaProx;
            break;
        case 2:
            M[linha][coluna] = duasProx;
            break;
        case 3:
            M[linha][coluna] = tresProx;
            break;
        case 4:
            M[linha][coluna] = quatroProx;
            break;
        default:
            M[linha][coluna] = Vazio;
            break;
    }
    

}

void preencheCampo(){

    int i;
    int j;

     for (int i = 0; i < tamCampo; i++) {
        for (int j = 0; j < tamCampo; j++) {
            if (verificaCoordenadas(i, j) && M[i][j] != Bomba) verificaVizinhos(i, j);
        }
     }

}

int plantaBomba(){

    int quantBombT = 0;
    int linBomb;
    int colBomb;

    srand(time(NULL));

    while(quantBombT < tamCampo-2){

        do{
            linBomb = ((rand() % tamCampo)); //antes tava mod 5 + 1, o que poderia gerar índice fora da matriz
            colBomb = ((rand() % tamCampo));
            }
        while((M[linBomb][colBomb] == Bomba)); //não plantar 2 bombas no mesmo lugar
    
        quantBombT++;
        M[linBomb][colBomb] = Bomba;
        
    }

    return quantBombT;

}

void revela(int linha, int coluna){

    if (M[linha][coluna] == Vazio) {
        revelados[linha][coluna] = Vazio;
    } else {
        return; //não chegar a recursão em células diferentes das vazias
    }

    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
                if(!verificaCoordenadas(i,j)) continue;
                if (revelados[i][j] != Vazio) revela(i, j);
                /*revelados[i][j] != Vazio, para não chamar recursão de novo em células já vazias e reveladas,
                se essa condição for verdadeira, os revelados[i][j] == naoRevelados entrarão, sobre números revelados, nem chegarão aqui*/
            }
        }
    
}

void prtMatriz(){
    printf("\n                                                                      |");
        for (int i = 0; i < tamCampo; i++) printf(" %d |",i);
        printf("\n                                                                   ———————————————————————————————————");
        for (int i = 0; i < tamCampo; i++) {
            printf("    \n");
            printf("                                                                    %d |",i);
            for (int j = 0; j < tamCampo; j++) {
                if(j == tamCampo -1){
                    if(revelados[i][j] != naoRevelado){
                        if(revelados[i][j] == Vazio) printf("   |\n");
                        else printf(" %d |\n", revelados[i][j]);
                        printf("                                                                   ———————————————————————————————————");
                    }
                    else {
                        printf("▆▆▆|\n");
                        printf("                                                                   ———————————————————————————————————");
                    }
                }
                else if (revelados[i][j] == naoRevelado){
                    printf("▆▆▆|"); 
                    }
                else {
                    if(revelados[i][j] == Vazio) printf("   |");
                    else printf(" %d |", revelados[i][j]);
                }
            }
        }
    }

int win(){

int cont = 0;

for (int i = 0; i < tamCampo; i++) {
    for (int j = 0; j < tamCampo; j++) {
        if(revelados[i][j] != naoRevelado) cont++; 
    }
}

if(cont == ((tamCampo*tamCampo) - (tamCampo-2))) return 1;
else return 0;

}

void game(){

    int linha, coluna;

    plantaBomba();
    preencheCampo();
    clean();

    while(lose == 1 && win() == 0){

        prtMatriz();

        do{
            printf("\n\n                                                                       Digite a linha que deseja:");
            scanf("%d", &linha);
            printf("                                                                       Digite a coluna que deseja:");
            scanf("%d", &coluna);
            if(!verificaCoordenadas(linha,coluna)) {
                printf("                                                                       Digite coordenadas válidas\n");
                sleep(1);
                }
            else if(revelados[linha][coluna] != naoRevelado){
                printf("                                                                       Essa célula já foi selecionada.\n");
            }
        }
        while(!verificaCoordenadas(linha,coluna) || revelados[linha][coluna] != naoRevelado);

        switch(M[linha][coluna]){
            case Bomba:
                printf("                                                                  Você selecionou um local com bomba :c\n");
                sleep(3);
                clean();
                printf("\n\n\n\n\n\n\n\n");
                printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
                printf("                                                                    ⎰                                  ⎱\n");
                printf("                                                                    ⟪  D    E     F     E     A     T  ⟫\n");
                printf("                                                                    ⎱                                  ⎰\n");
                printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
                sleep(3);
                lose = 0;
                clean();
                break; 
            case Vazio:
                revela(linha,coluna);
                break;
            default:
                revelados[linha][coluna] = M[linha][coluna];
        }

        if(win()) {
            clean();
            printf("\n\n\n\n\n\n\n\n");
            printf("                                                                                    P A R A B É N S !\n");
            printf("                                                                     V O C Ê     E N C E R R O U     O     J O G O!\n");
            sleep(3);
            clean();
            printf("\n\n\n\n\n\n\n\n");
            printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
            printf("                                                                    ⎰                                  ⎱\n");
            printf("                                                                    ⟪  V   I    C    T    O    R    Y  ⟫\n");
            printf("                                                                    ⎱                                  ⎰\n");
            printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
            sleep(3); 
            return;
        }
            clean();

    }
    printf("\n\n");

}

/*void player(Infos *user, int time){

    char nome[20];
    char sobrenome[20];
    char name[50];
    int nível;

    printf("Digite seu 1º nome:\n");
    scanf("%s",&nome);
    printf("Digite seu sobrenome:\n");
    scanf("%s",&sobrenome);

    strcpy(name,nome);
    strcat(name," ");
    strcpy(name,sobrenome);

    do {
    printf("Selecione um nível de jogo: / 1 / 2 / 3 /\n");
    scanf("%d", &nível);
    } while (nível > 3 || nível < 1);

    strcpy(user->nome, name);
    user->dificuldade = nível;
    user->tempo = time;
    
} */

int main(){

    for(int i = 0; i < tamCampo ; i++){
        for(int j = 0; j < tamCampo ; j++){
            revelados[i][j] = naoRevelado;
        }
    } 

    /*Infos *user;
    user = (Infos *)malloc(sizeof(Infos));
    
    int tempo = timer();

    player(user,tempo); 

    printf("Nome: %s\n", user->nome);
    printf("Dificuldade: %d\n", user->dificuldade);
    printf("Tempo: %d\n", user->tempo);

    free(user);*/

    //timer();
    alocaMemória();
    menu();
    game();
    liberaMemoria();

    return 0;

}
