#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// STRUCT DOS TERRITÓRIOS
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// FUNÇÃO PARA CADASTRAR TERRITÓRIOS
void cadastrarTerritorios(struct Territorio *mapa, int quantidade){

    int i;

    for(i = 0; i < quantidade; i++){

        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &(mapa + i)->tropas);

        getchar();
    }
}

// FUNÇÃO PARA MOSTRAR O MAPA
void mostrarMapa(struct Territorio *mapa, int quantidade){

    int i;

    printf("\n================ MAPA ATUAL ================\n");

    for(i = 0; i < quantidade; i++){

        printf("\n%d. %s", i + 1, (mapa + i)->nome);
        printf(" | Exercito: %s", (mapa + i)->cor);
        printf(" | Tropas: %d\n", (mapa + i)->tropas);
    }
}

// FUNÇÃO DE ATAQUE
void atacar(struct Territorio *atacante,
             struct Territorio *defensor){

    int dadoAtaque;
    int dadoDefesa;

    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("\n%s rolou %d",
    atacante->nome,
    dadoAtaque);

    printf("\n%s rolou %d\n",
    defensor->nome,
    dadoDefesa);

    // ATACANTE VENCE
    if(dadoAtaque > dadoDefesa){

        printf("\n%s venceu a batalha!\n",
        atacante->nome);

        defensor->tropas--;

        // ganha tropa até o limite 5
        if(atacante->tropas < 5){

            atacante->tropas++;
        }

        // CONQUISTA
        if(defensor->tropas <= 0){

            printf("\n%s conquistou %s!\n",
            atacante->nome,
            defensor->nome);

            strcpy(defensor->cor, atacante->cor);

            // transferir tropas
            int tropasTransferidas;

            tropasTransferidas = atacante->tropas / 2;
            defensor->tropas = tropasTransferidas;
            atacante->tropas -= tropasTransferidas;

            // garante mínimo 1
            if(defensor->tropas < 1){

                defensor->tropas = 1;
            }
        }
    }

    // DEFENSOR VENCE
    else if(dadoDefesa > dadoAtaque){

        printf("\n%s defendeu o territorio!\n",
        defensor->nome);

        atacante->tropas--;

        // defensor ganha tropa até o limite 5
        if(defensor->tropas < 5){

            defensor->tropas++;
        }
    }

    // EMPATE
    else{

        printf("\nEmpate nos dados! Nenhum territorio perdeu tropas.\n");
    }
}

// FUNÇÃO PARA LIBERAR MEMÓRIA
void liberarMemoria(struct Territorio *mapa){

    free(mapa);

    printf("\nMemoria liberada com sucesso!\n");
}

int main(){

    int quantidade;
    int atacante;
    int defensor;

    struct Territorio *mapa;

    srand(time(NULL));

    printf("Quantos territorios deseja criar? ");
    scanf("%d", &quantidade);

    getchar();

    // ALOCAÇÃO DINÂMICA
    mapa = calloc(quantidade, sizeof(struct Territorio));

    if(mapa == NULL){

        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\n=========== CADASTRO DOS TERRITORIOS ===========\n");

    cadastrarTerritorios(mapa, quantidade);

    // LOOP PRINCIPAL
    while(1){

        mostrarMapa(mapa, quantidade);

        printf("\nEscolha o territorio atacante (1-%d) ou 0 para sair: ",
        quantidade);

        scanf("%d", &atacante);

        if(atacante == 0){

            break;
        }

        atacante--;

        printf("Escolha o territorio defensor (1-%d): ",
        quantidade);

        scanf("%d", &defensor);

        defensor--;

        // IMPEDIR AUTO ATAQUE
        if(atacante == defensor){

            printf("\nUm territorio nao pode atacar a si mesmo!\n");
            continue;
        }

        // IMPEDIR ATAQUE ENTRE MESMO EXERCITO
        if(strcmp((mapa + atacante)->cor,
                  (mapa + defensor)->cor) == 0){

            printf("\nTerritorios do mesmo exercito nao podem batalhar!\n");
            continue;
        }

        // VERIFICAR TROPAS
        if((mapa + atacante)->tropas <= 1){

            printf("\nEsse territorio nao possui tropas suficientes para atacar!\n");
            continue;
        }

        // FUNÇÃO DE ATAQUE
        atacar(&mapa[atacante], &mapa[defensor]);
    }

    // LIBERAR MEMÓRIA
    liberarMemoria(mapa);

    printf("\nJogo encerrado.\n");

    return 0;
}
