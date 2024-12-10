#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define RESET "\033[0m"
#define CIANO "\033[36m"
#define PRETO "\033[30m"
#define AZUL "\033[34m"
#define CINZA "\033[37m"
#define VERDE "\033[32m"
#define MAGENTA "\033[35m"
#define VERMELHO "\033[31m"
#define tamCampo 7
#define numMaxPlayers 20

// ponteiro para armazenar quantidade de casas que o jogador conseguiu revelar

enum casas {Vazio = 0, umaProx = 1, duasProx = 2, tresProx = 3, quatroProx = 4, naoRevelado = 5, Bomba = 6};
int lose = 1;
int revelados[tamCampo][tamCampo];
int M[tamCampo][tamCampo];

typedef struct{
        char nome[40];
        int dificuldade;
        int pontuação;
    } Infos;

void clean(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

void menu(){

    char start;

    printf("\n");
    printf(MAGENTA "                                                         B E M     V I N D O      A O     C A M P O     M I N A D O\n" RESET);
    printf(PRETO "                                                         ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n" RESET);
    printf("                                                                                         _❈ \n");
    printf("                                                                                        /\n");
    printf("                                                                                   ✩✩✩✩✩✩\n");
    printf("                                                                                 ✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                ✩✩✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                 ✩✩✩✩✩✩✩✩✩\n");
    printf("                                                                                  ✩✩✩✩✩✩✩\n\n");
    printf(MAGENTA"                                                                         Clique enter para começar!" RESET);
    
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
            revelados[i][j] = naoRevelado;
            if (verificaCoordenadas(i, j) && M[i][j] != Bomba) verificaVizinhos(i, j);
        }
     }

}

int plantaBomba(Infos *user){

    int quantBombT = 0;
    int linBomb;
    int colBomb;
    int qBombVaria;

    srand(time(NULL));

    switch(user->dificuldade){
        case 1:
            qBombVaria = tamCampo/2;
            break;
        case 2:
            qBombVaria = tamCampo/2+tamCampo/3;
            break;
        case 3:
            qBombVaria = tamCampo;
            break;
    }

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

void revela(int linha, int coluna, Infos *user){ //chamada recursiva

    if(!verificaCoordenadas(linha,coluna) || revelados[linha][coluna] != naoRevelado){
        return;
    }

    revelados[linha][coluna] = M[linha][coluna];

    user->pontuação += 50;

    if(M[linha][coluna] == Vazio){
        for (int i = linha - 1; i <= linha + 1; i++) {
            for (int j = coluna - 1; j <= coluna + 1; j++) {
                    if(!verificaCoordenadas(i,j)) continue;
                    if(revelados[i][j] != Vazio) { //isso é diferente de M[i][j] != Vazio !!!
                        if(i == linha && j == coluna) continue;
                        revela(i, j,user);
                        }
                    /*revelados[i][j] != Vazio, para não chamar recursão de novo em células já vazias e reveladas,
                    se essa condição for verdadeira, os revelados[i][j] == naoRevelados entrarão, sobre números revelados, nem chegarão aqui*/
                }
            }
    }
}

void campoRevelado(){

   int qLinhas = ((tamCampo-3)*3)+(tamCampo-3);

    printf(AZUL "\n                                                                      |" RESET);
        for (int i = 0; i < tamCampo; i++) printf(CIANO " %d |" RESET ,i);
        printf(AZUL "\n                                                                   ————————————————" RESET);
        for(int i=0;i<qLinhas;i++) printf(AZUL "—" RESET);
        for (int i = 0; i < tamCampo; i++) {
            printf("    \n");
            printf(CIANO "                                                                    %d |"RESET ,i);
            for (int j = 0; j < tamCampo; j++) {
                if(j == tamCampo -1){
                    if(M[i][j] != naoRevelado){
                        if(M[i][j] == Vazio) printf(AZUL "   |\n" RESET);
                        else if(M[i][j] == Bomba) printf(" ⦰ |\n" RESET);
                        else printf(CINZA " %d |\n"RESET , M[i][j]);
                        printf(AZUL "                                                                   ————————————————" RESET);
                        for(int i=0;i<qLinhas;i++) printf(AZUL "—" RESET);
                    }
                }
                else {
                    if(M[i][j] == Vazio) printf(CINZA "   |" RESET);
                    else if(M[i][j] == Bomba) printf(" ⦰ |");
                    else printf(CINZA " %d |" RESET , M[i][j]);
                }
            }
        }

}

void prtMatriz(){

    int qLinhas = ((tamCampo-3)*3)+(tamCampo-3);

    printf(AZUL "\n                                                                      |" RESET);
        for (int i = 0; i < tamCampo; i++) printf(CIANO " %d |" RESET ,i);
        printf(AZUL "\n                                                                   ————————————————" RESET);
        for(int i=0;i<qLinhas;i++) printf(AZUL "—" RESET);
        for (int i = 0; i < tamCampo; i++) {
            printf("    \n");
            printf(CIANO "                                                                    %d |"RESET ,i);
            for (int j = 0; j < tamCampo; j++) {
                if(j == tamCampo -1){
                    if(revelados[i][j] != naoRevelado){
                        if(revelados[i][j] == Vazio) printf(AZUL "   |\n" RESET);
                        else if(revelados[i][j] == Bomba) printf(" o* |\n" RESET);
                        else printf(CINZA " %d |\n"RESET , revelados[i][j]);
                        printf(AZUL "                                                                   ————————————————" RESET);
                        for(int i=0;i<qLinhas;i++) printf(AZUL "—" RESET);
                    }
                    else {
                        printf("▆▆▆|\n");
                        printf(AZUL "                                                                   ————————————————" RESET);
                        for(int i=0;i<qLinhas;i++) printf(AZUL "—" RESET);
                    }
                }
                else if (revelados[i][j] == naoRevelado){
                    printf(CINZA "▆▆▆|" RESET); 
                    }
                else {
                    if(revelados[i][j] == Vazio) printf(CINZA "   |" RESET);
                    else if(revelados[i][j] == Bomba) printf(" ◯*|");
                    else printf(CINZA " %d |" RESET , revelados[i][j]);
                }
            }
        }
    }

int win(int limitaBomba){

    int cont = 0;

    for (int i = 0; i < tamCampo; i++) {
        for (int j = 0; j < tamCampo; j++) {
            if(revelados[i][j] != naoRevelado) cont++; 
        }
    }

    if(cont == ((tamCampo*tamCampo) - limitaBomba)) return 1;
    else return 0;

}

void game(Infos *user){

    
    int linha, coluna;

    int bombDefinidas = plantaBomba(user);
    preencheCampo();
    clean();

    while(lose == 1 && win(bombDefinidas) == 0){

        printf("\n\n\n\n\n");
        prtMatriz();

        do{
            printf(MAGENTA "\n\n                                                                     Digite a linha que deseja:" );
            scanf("%d", &linha);
            printf("                                                                     Digite a coluna que deseja:" RESET);
            scanf("%d", &coluna);
            if(!verificaCoordenadas(linha,coluna)) {
                printf(MAGENTA "                                                                       Digite coordenadas válidas\n" RESET);
                sleep(1);
                }
            else if(revelados[linha][coluna] != naoRevelado){
                printf(MAGENTA "                                                                       Essa célula já foi selecionada.\n" RESET);
            }
        }
        while(!verificaCoordenadas(linha,coluna) || revelados[linha][coluna] != naoRevelado);

        switch(M[linha][coluna]){
            case Bomba:
                clean();
                revelados[linha][coluna] = M[linha][coluna];
                prtMatriz();
                printf(MAGENTA "\n\n                                                                Você selecionou um local com bomba :c\n" RESET);
                sleep(7);
                clean();
                printf("\n\n\n\n\n\n\n\n");
                printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
                printf(VERMELHO"                                                                    ⎰                                  ⎱\n" );
                printf("                                                                    ⟪  D    E     F     E     A     T  ⟫\n" );
                printf("                                                                    ⎱                                  ⎰\n" RESET);
                printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n" );
                sleep(3);
                lose = 0;
                clean();
                break; 
            case Vazio:
                revela(linha,coluna,user);
                break;
            default:
                revelados[linha][coluna] = M[linha][coluna];
                user->pontuação += 50;
                break;
        }

        if(win(bombDefinidas)) {
            lose = 0;
            clean();
            printf("\n\n\n\n\n\n\n\n");
            printf(VERDE "                                                                           P A R A B É N S !\n");
            printf("                                                              V O C Ê     E N C E R R O U     O     J O G O!\n" RESET);
            campoRevelado();
            sleep(7);
            clean();
            printf("\n\n\n\n\n\n\n\n");
            printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
            printf(VERDE"                                                                    ⎰                                  ⎱\n" );
            printf("                                                                    ⟪  V   I    C    T    O    R    Y ⟫\n" );
            printf("                                                                    ⎱                                  ⎰\n" RESET);
            printf("                                                                     ⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤⪤\n");
            sleep(3); 
            return;
        }
            clean();

    }
    printf("\n\n");

}

void player(Infos *user){

    char nome[20];
    char sobrenome[20];
    char nomeCompleto[50];
    int nível;

    printf(MAGENTA "                                                                         Digite seu 1º nome:" RESET);
    gets(nome);
    printf(MAGENTA "\n                                                                         Digite seu sobrenome:" RESET);
    gets(sobrenome);

    snprintf(user->nome, sizeof(nomeCompleto), "%s %s", nome, sobrenome);

    do {
    printf(MAGENTA "\n                                                            Selecione um nível de jogo entre esses / 1 / 2 / 3 /: " RESET);
    scanf("%d", &user->dificuldade);
    } while (user->dificuldade > 3 || user->dificuldade < 1);

} 

void points(Infos *user, int *minutes){

    int intervalos[5] = {1,2,3,4,5};
    int pontuações[5] = {500,300,100,75,50};

    if(!lose) user->pontuação += 500;

    switch(user->dificuldade){
        case 1:
            break;
        case 2:
            user->pontuação +=100;
            break;
        case 3:
            user->pontuação += 300;
            break;
    }

    for(int i = 0; i < 6 ; i++){
        if(*minutes < intervalos[i]) {
            user->pontuação += pontuações[i]; //erro ta aq, ta somando tds
            break;
        }
    }

}

void formatTime(int *time, int *seg, int *min){

    *seg = *time % 60;
    *min = (*time - *seg) / 60;

}

int addPlayer(float *ranking,int *minutos, int *segundos, Infos *user){

    FILE *file = fopen("arquivo.txt", "a"); //se existir ele deleta e cria novo vazio || sobreescreve arquivo

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "|    %d    |    %d    | %d:%d  |      %d      | %s ", (int)(*ranking),user->pontuação,*minutos,*segundos,user->dificuldade,user->nome);
    fclose(file);

}

int main(){

    //wasd
    //colocar jogadas
    
    int tempo;
    int minutos;
    int segundos;
    float ranking = 1;

    Infos *user;
    user = (Infos *)malloc(sizeof(Infos) * numMaxPlayers);

    menu();
    clean();
    player(user); 
    time_t inicio = time(NULL); 
    game(user);
    time_t fim = time(NULL);
    tempo = fim-inicio;
    formatTime(&tempo,&segundos,&minutos);
    points(user,&minutos);
    
    /***********************************************************************ADIÇÃO DO JOGADOR ATUAL*****************************************************************************************/

    addPlayer(&ranking,&minutos,&segundos,user);

    /************************************************************LEITURA DO ARQUIVO PARA STRUCT LOCAL E ORDENAÇÃO***************************************************************************/



    /****************************************************************************ATUALIZAR ARQUIVO******************************************************************************************/



    free(user);

    return 0;

}
