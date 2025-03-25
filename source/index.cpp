#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "./headers/TADFilaPrioridade.h"

#ifdef WIN32
    #include "./headers/conio-dos.h"
    #include "./headers/meu-conio.h"
#else
    #include "./headers/conio-unix.h"
    #include "./headers/cores.h"
#endif

void ExibirFila (TpFilaPrioridade fila) {
    TpTarefa aux;
    while(!FilaVazia(fila.qtde)) {
        aux = RetirarCircular(fila);
        printf("%s - %d - %s\n", aux.tipo, aux.tempo, aux.DescricaoTarefa);
    }
}

void InserindoTarefa(TpFilaPrioridade &fila) {
    FILE * Ptr = fopen("./source/assets/tarefas.txt", "r");
    TpTarefa TarefaAux;

    do {
        fscanf(Ptr, "%[^,],%d,%[^\n]\n", TarefaAux.tipo, &TarefaAux.tempo, TarefaAux.DescricaoTarefa);
        TarefaAux.prioridade = gerarPrioridade(TarefaAux.tipo);
        
        if (!FilaCheia(fila.qtde)) {
            Inserir(fila, TarefaAux);
        } 
    } while(!feof(Ptr));

    fclose(Ptr);
}

void Operadores(TpFilaPrioridade &fila) {
    TpTarefa VetorAux[MAXFILA], aux;
    int operadores, tlVetAux=0, i, tempoOperacao, j, contTarefasConcluidas=0;
    printf("QUANTIDADE DE OPERADORES: ");
    scanf ("%d", &operadores);
    printf ("TEMPO DE OPERACAO: ");
    scanf("%d", &tempoOperacao);

    while(operadores > 0) {
        if (!FilaVazia(fila.qtde)) {
            VetorAux[tlVetAux] = RetirarCircular(fila);
            tlVetAux++;
            operadores--;
        }
    }
    for (i=0;i<tlVetAux;i++)
        printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
    getch();

    while (tempoOperacao > 0) {
        for (i=0;i<tlVetAux;i++){
            if (VetorAux[i].tempo == 0) {
                contTarefasConcluidas++;
                for (j=i;j<tlVetAux;j++) 
                    VetorAux[j] = VetorAux[j+1];
                if (!FilaVazia(fila.qtde))
                    VetorAux[tlVetAux] = RetirarCircular(fila);
            }
            VetorAux[i].tempo--;
        }
        clrscr();
        for (i=0;i<tlVetAux;i++)
            printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
        ExibirFila(fila);
        printf ("\nTEMPO: %d\n", tempoOperacao);
        sleep(1);
        tempoOperacao--;
    }
    printf ("TAREFAS CONCLUIDAS: %d\n", contTarefasConcluidas);
    getch();
    clrscr();
    for (i=0;i<tlVetAux;i++)
        printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
    getch();
}

int main(){
    TpFilaPrioridade fila;
    clrscr();

    Inicializar(fila);
    InserindoTarefa(fila);
    Operadores(fila);
    getch();
    ExibirFila(fila);
    return 0;
}