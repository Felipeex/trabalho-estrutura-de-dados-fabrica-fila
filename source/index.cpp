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
    while(!FilaVazia(fila.fim)) {
        aux = RetirarCircular(fila);
        printf ("%s - %d - %s\n", aux.prioridade, aux.tempo, aux.DescricaoTarefa);
    }
}

void Executar (void) {
    FILE * PtrTarefas = fopen("tarefas.txt", "r");
    TpTarefa tarefaAux;
    TpFilaPrioridade fila;
    int tempo;
    Inicializar(fila);
    if (PtrTarefas != NULL) {
        printf ("ENTROU");
        getch();
        fscanf(PtrTarefas, "%[^,],%d,%[^,]\n", tarefaAux.prioridade, &tarefaAux.tempo, tarefaAux.DescricaoTarefa);
        while (!feof(PtrTarefas)) {
            // printf ("ENTROU");
            // getch();
            printf ("%s - %d - %s\n", tarefaAux.prioridade, tarefaAux.tempo, tarefaAux.DescricaoTarefa);
            getch();

            if (!FilaCheia(fila.fim)){
                // printf ("ENTROU");
                // getch();
                InserirCircular(fila, tarefaAux);
            }
            if(!FilaVazia(fila.fim)) {
                RetirarCircular(fila);
                ExibirFila(fila);
                sleep(1);
         
             fscanf(PtrTarefas, "%[^,],%d,%[^,]\n", tarefaAux.prioridade, &tarefaAux.tempo, tarefaAux.DescricaoTarefa);
            }
        }

        if (!FilaVazia(fila.fim)) {
            printf ("ENTROU");
            getch();
            ExibirFila(fila);
            sleep(1);
        }
    }
    fclose(PtrTarefas);
 
}

int main(){
    clrscr();
    PainelPrincipal();
    Executar();
    return 0;
}