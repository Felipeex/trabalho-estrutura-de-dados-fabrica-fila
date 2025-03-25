#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// #include "./headers/conio-unix.h"
#include "./headers/TADFilaPrioridade.h"
// #include "./headers/TADPainel.h"

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
    int operadores, tlVetAux=0, i, tempoOperacao, j, contTarefasConcluidas=0, contUrgente=0, contNormal=0,              contOpcional=0;
    float tempoUrgente=0, tempoNormal=0, tempoOpcional=0;
    do {
        printf ("MINIMO: 1 | MAXIMO 20\n");
        printf("QUANTIDADE DE OPERADORES: ");
        scanf ("%d", &operadores);
        if (operadores < 1 || operadores >= 20) {
            printf(RED "\nLIMITE DE OPERADORES NAO RESPEITADO\n" );
            printf ("DIGITE NOVAMENTE\n\n" NORMAL);
        }
        
    } while (operadores < 1 || operadores >= 20);
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

    while (tempoOperacao >= 0 && !kbhit()) {

        for (i=0;i<tlVetAux;i++){

            switch(VetorAux[i].prioridade) {
                case 1:
                    tempoUrgente++;
                    break;
                case 2:
                    tempoNormal++;
                    break;
                default:
                    tempoOpcional++;
                    break;
            }

            if (VetorAux[i].tempo == 0) {

                for (j=i;j<tlVetAux;j++) 
                    VetorAux[j] = VetorAux[j+1];
                if (!FilaVazia(fila.qtde)) {
                    VetorAux[tlVetAux] = RetirarCircular(fila);
                }
                switch(VetorAux[i].prioridade) {
                    case 1:
                        contUrgente++;
                        break;
                    case 2:
                        contNormal++;
                        break;
                    default:
                        contOpcional++;
                        break;
                }
                contTarefasConcluidas++;
            }
            VetorAux[i].tempo--;
        }
        clrscr();
        ExibirFila(fila);
        printf ("\n\n");
        for (i=0;i<tlVetAux;i++)
            printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
        printf ("\nTEMPO: %d\n", tempoOperacao);
        sleep(1);
        tempoOperacao--;
    }

    if (contUrgente > 0) 
        tempoUrgente = tempoUrgente/contUrgente;
    if (contNormal > 0) 
        tempoNormal = tempoNormal/contNormal;
    if (contOpcional > 0) 
        tempoOpcional = tempoOpcional/contOpcional;
    printf ("TEMPO MEDIO URGENTE: %.2f\n", tempoUrgente);
    printf ("TEMPO MEDIO NORMAL: %.2f\n", tempoNormal);
    printf ("TEMPO MEDIO OPCIONAL: %.2f\n", tempoOpcional);
    printf ("TAREFAS CONCLUIDAS: %d\n", contTarefasConcluidas);
    printf ("TAREFAS NAO CONCLUIDAS: %d\n", (fila.qtde+tlVetAux)-contTarefasConcluidas);
    getch();
    clrscr();
    for (i=0;i<tlVetAux;i++)
        printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
    getch();
}

int main(){
    TpFilaPrioridade fila;
    clrscr();

    // PainelPrincipal();
    // getch();
    Inicializar(fila);
    InserindoTarefa(fila);
    Operadores(fila);
    getch();
    ExibirFila(fila);
    return 0;
}