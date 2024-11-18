#include <stdio.h>

int main() {
    FILE *file = fopen("arquivo.txt", "w"); //se existir ele deleta e cria novo vazio || sobreescreve arquivo
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "|Ranking | Pontuação | Tempo |\n");
    // Operações em arquivo
    fclose(file);
    return 0;
}