#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define tamCampo 5

// ponteiro para armazenar quantidade de casas que o jogador conseguiu revelar
// struct para toda parte de arquivo, alocar memória pra ele e liberar depois de fechar o arquivo

enum casas {Vazio = 0, umaProx = 1, duasProx = 2, tresProx = 3, quatroProx = 4, naoRevelado = 5, Bomba = 6};

int M[tamCampo][tamCampo];
int revelados[tamCampo][tamCampo] = {naoRevelado,naoRevelado,naoRevelado,naoRevelado,naoRevelado,
                                    naoRevelado,naoRevelado,naoRevelado,naoRevelado,naoRevelado,
                                    naoRevelado,naoRevelado,naoRevelado,naoRevelado,naoRevelado,
                                    naoRevelado,naoRevelado,naoRevelado,naoRevelado,naoRevelado,
                                    naoRevelado,naoRevelado,naoRevelado,naoRevelado,naoRevelado};

void clean(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

/*void timer(parametro encontrou bomba ou ganhou)

    int segundos = 0;

    while(parametro encontrou bomba ou ganhou verdadeiro segundos < 20){ // segundos < 20 só de teste
        printf("Your time: %d\r",segundos);
        fflush(stdout);

        sleep(1);

        segundos++;
    };
*/

void menu(){

    char start;

    printf("");
    printf("                                   B E M     V I N D O      A O     C A M P O     M I N A D O\n\n");
    printf("                                                                   _`´ \n");
    printf("                                                                  /\n");
    printf("                                                             ******\n");
    printf("                                                           *********\n");
    printf("                                                          ***********\n");
    printf("                                                           *********\n");
    printf("                                                            *******\n\n");
    printf("                                                   Clique enter para começar");
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
            if(i == linha && j == coluna) continue;
            if(M[i][j] == Bomba && verificaCoordenadas(i,j) == 1) quantBomb++;
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
            if(M[i][j] != Bomba) verificaVizinhos(i,j);
        }
     }

}

void plantaBomba(){

    int quantBombT = 0;
    int linBomb;
    int colBomb;

    srand(time(NULL));

    while(quantBombT < 3){

        do{
            linBomb = ((rand() % tamCampo)); //antes tava mod 5 + 1, o que poderia gerar índice fora da matriz
            colBomb = ((rand() % tamCampo));
            }
        while((M[linBomb][colBomb] == Bomba)); //não plantar 2 bombas no mesmo lugar
    
        quantBombT++;
        M[linBomb][colBomb] = Bomba;
        
    }

}

void revela(int linha, int coluna){

    if (!verificaCoordenadas(linha, coluna)) return; //desnecessário já que ocorre essa verificação antes de chamar essa função

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

    printf("\n                                                    |");
        for (int i = 0; i < tamCampo; i++) printf(" %d |",i);
        printf("\n                                                 -------------------------");
        for (int i = 0; i < tamCampo; i++) {
            printf("    \n");
            printf("                                                  %d |",i);
            for (int j = 0; j < tamCampo; j++) {
                if(j == tamCampo -1){
                    if(revelados[i][j] != naoRevelado){
                        printf(" %d |\n", revelados[i][j]);
                        printf("                                                 ------------------------");
                    }
                    else {
                        printf("   |\n");
                        printf("                                                 ------------------------");
                    }
                }
                else if (revelados[i][j] == naoRevelado){
                    printf("   |"); 
                    }
                else {
                    printf(" %d |", revelados[i][j]);
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

if(cont == ((tamCampo*tamCampo) - 3)) return 1;
else return 0;

}

void game(){

    int linha, coluna;
    int lose = 1;

    plantaBomba();
    preencheCampo();
    clean();

    while(lose == 1){

        prtMatriz();

        do{
            printf("\n\n                                                Digite a linha que deseja:");
            scanf("%d", &linha);
            printf("                                                Digite a coluna que deseja:");
            scanf("%d", &coluna);
            if(!verificaCoordenadas(linha,coluna)) {
                printf("                                                Digite coordenadas válidas\n");
                sleep(1);
                }
            else if(revelados[linha][coluna] != naoRevelado){
                printf("                                                Essa célula já foi selecionada.\n");
            }
        }
        while(!verificaCoordenadas(linha,coluna) || revelados[linha][coluna] != naoRevelado);

        switch(M[linha][coluna]){
            case Bomba:
                printf("                                                Você selecionou um local com bomba :c\n");
                sleep(3);
                clean();
                printf("\n\n\n\n\n\n\n\n");
                printf("                                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("                                  |    D     E     F     E     A     T     |\n");
                printf("                                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                sleep(2);
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
            printf("                                                  P A R A B É N S !\n");
            printf("                                     V O C Ê     E N C E R R O U     O     J O G O!\n");
            sleep(3);
            clean();
            printf("\n\n\n\n\n\n\n\n");
            printf("                                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("                                      |    V    I    C    T    O    R    Y     |\n");
            printf("                                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            sleep(3); 
            return;
        }
        clean();

    }
    printf("\n\n");

}

int main(){

    //timer();
    menu();
    game();

    return 0;

}
