#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "./headers/conio.h"
#include "./headers/cores.h"
#include "./headers/TADFilaPrioridade.h"
#include "./headers/TADPainel.h"

void ExibirFila (TpFilaPrioridade fila) {
    TpTarefa aux;
    while(!FilaVazia(fila.qtde)) {
        aux = RetirarCircular(fila);
        printf ("%s - %d - %s\n", aux.tipo, aux.tempo, aux.DescricaoTarefa);
    }
}

void LeArquivo (TpFilaPrioridade &fila) {
    FILE * Ptr = fopen("./assets/tarefas.txt", "r");
    TpTarefa TarefaAux;

    
    printf ("ENTROU ARQUIVO");
    getch();
    fscanf(Ptr, "%[^,],%d,%[^,]\n", &TarefaAux.tipo, &TarefaAux.tempo, &TarefaAux.DescricaoTarefa);
    while (!feof(Ptr)) {
        Prioridade(TarefaAux);

        printf ("ENTROU");
        printf ("%s - %d - %s\n", TarefaAux.tipo, TarefaAux.tempo, TarefaAux.DescricaoTarefa);
        getch();
        if (!FilaCheia(fila.qtde)) {
            Inserir(fila, TarefaAux);
        }
        fscanf(Ptr, "%[^,],%d,%[^,]\n", &TarefaAux.tipo, &TarefaAux.tempo, &TarefaAux.DescricaoTarefa);
    }
    fclose(Ptr);
}

// void Executar (void) {
//     FILE * PtrTarefas = fopen("tarefas.txt", "r");
//     TpTarefa tarefaAux;
//     TpFilaPrioridade fila;
//     int tempo;
//     Inicializar(fila);
//     if (PtrTarefas != NULL) {
//         printf ("ENTROU");
//         getch();
//         fscanf(PtrTarefas, "%[^,],%d,%[^,]\n", tarefaAux.prioridade, &tarefaAux.tempo, tarefaAux.DescricaoTarefa);
//         while (!feof(PtrTarefas)) {
//             // printf ("ENTROU");
//             // getch();
//             printf ("%s - %d - %s\n", tarefaAux.prioridade, tarefaAux.tempo, tarefaAux.DescricaoTarefa);
//             getch();

//             if (!FilaCheia(fila.fim)){
//                 // printf ("ENTROU");
//                 // getch();
//                 InserirCircular(fila, tarefaAux);
//             }
//             if(!FilaVazia(fila.fim)) {
//                 RetirarCircular(fila);
//                 ExibirFila(fila);
//                 sleep(1);
         
//              fscanf(PtrTarefas, "%[^,],%d,%[^,]\n", tarefaAux.prioridade, &tarefaAux.tempo, tarefaAux.DescricaoTarefa);
//             }

//             tempo = fila.FILA[fila.inicio].tempo;


//         }

//         if (!FilaVazia(fila.fim) && tempo == 0) {
//             printf ("ENTROU");
//             getch();
//             ExibirFila(fila);
//             sleep(1);
//         }
//     }
//     fclose(PtrTarefas);
//     tempo = fila.FILA[fila.inicio].tempo;
//     while(tempo > 0 ){
//         printf ("Tempo restante: %d\n", tempo);
//         sleep(1);
//         tempo--;
//     }
//     printf ("Fim da execucao\n");
//     getch();
// }

void Executar (void) {
    TpFilaPrioridade fila;
    TpTarefa tarefa;
    clrscr();

    Inicializar(fila);

    LeArquivo(fila);

    ExibirFila(fila);
    getch();
}

int main(){
    // clrscr();
    // PainelPrincipal();
    Executar();
    return 0;
}