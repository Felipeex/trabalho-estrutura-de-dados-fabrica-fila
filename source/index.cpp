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
        fscanf(Ptr, "%[^,],%d,%[^,]\n", &TarefaAux.tipo, &TarefaAux.tempo, &TarefaAux.DescricaoTarefa);
        TarefaAux.prioridade = gerarPrioridade(TarefaAux.tipo);

        printf("%s - %d - %s\n", TarefaAux.tipo, TarefaAux.tempo, TarefaAux.DescricaoTarefa);
        getch();
        
        if (!FilaCheia(fila.qtde)) {
            Inserir(fila, TarefaAux);
        }
    } while(Ptr != NULL);

    fclose(Ptr);
}

int main(){
    TpFilaPrioridade fila;
    clrscr();

    Inicializar(fila);
    InserindoTarefa(fila);
    // ExibirFila(fila);
    return 0;
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