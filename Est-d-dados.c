#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[50];
    char cor[30];
    int tropas;
};

int main(){

    struct Territorio t[5];

    printf("========================================================================\n");
    printf("\n Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    //ENTRADA DE DADOS
    for(int i = 0; i < 5; i++){
        printf("\n--- Cadastrar Territorio %d ---\n", i+1);

        printf("Nome do territorio: ");
        fgets(t[i].nome, 50, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0'; // remove o \n

        printf("Cor do exercito: ");
        fgets(t[i].cor, 30, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Numero de tropas (de 1 a 5): ");
        scanf("%d", &t[i].tropas);
        getchar();
    }

    // SAÍDA DOS DADOS
    printf("\n================ ESTADO ATUAL DO MAPA ================\n");

    for(int i = 0; i < 5; i++){
        printf("\nTerritorio %d:\n", i+1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor do exercito: %s\n", t[i].cor);
        printf("Numero de tropas: %d\n", t[i].tropas);
    }

    return 0;
}
