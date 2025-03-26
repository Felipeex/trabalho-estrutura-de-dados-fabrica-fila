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
#endif

#include "./headers/cores.h"

void tituloRelatorio(void);
void tituloFabrica (void);
void tituloOperadores (void);
void tituloFila(void);
void tituloNome(void);

void ExibirFila (TpFilaPrioridade fila) {
    TpTarefa aux;
    int linha=7;
    while(!FilaVazia(fila.quantidade)) {
        aux = RetirarCircular(fila);
        gotoxy(80, linha); printf("%ds | (%s) %s\n", aux.tempo, aux.tipo, aux.DescricaoTarefa);
        linha++;
    }
}

void InserindoTarefa(TpFilaPrioridade &fila, FILE * Ptr) {
    TpTarefa TarefaAux;
    int cont=0;


    do {
        fscanf(Ptr, "%[^,],%d,%[^\n]\n", TarefaAux.tipo, &TarefaAux.tempo, TarefaAux.DescricaoTarefa);
        TarefaAux.prioridade = gerarPrioridade(TarefaAux.tipo);
        
        if (!FilaCheia(fila.quantidade)) {
            Inserir(fila, TarefaAux);
            cont++;
        } 
    } while(cont < 30);
}

void InsereDepois(TpFilaPrioridade &fila, FILE * Ptr) {
    TpTarefa TarefaAux;
    fscanf(Ptr, "%[^,],%d,%[^\n]\n", TarefaAux.tipo, &TarefaAux.tempo, TarefaAux.DescricaoTarefa);
    TarefaAux.prioridade = gerarPrioridade(TarefaAux.tipo);
    
    if (!FilaCheia(fila.quantidade)) {
        Inserir(fila, TarefaAux);
    } 
}

void Operadores(TpFilaPrioridade &fila, char nome[3][50]) {
    FILE * Ptr = fopen("./source/assets/tarefas.txt", "r");
    TpTarefa VetorAux[MAXFILA], aux;
    int operadores, tlVetAux=0, i, tempoOperacao, j, contTarefasConcluidas=0, contUrgente=0, contNormal=0,contOpcional=0, contInsere=0, contTarefasIncompletas=0;
    float tempoUrgente=0, tempoNormal=0, tempoOpcional=0;
    tituloFabrica();
    do {
        // printf ("MINIMO: 1 | MAXIMO 20\n");
        printf("Quantidade de operadores (Minimo: 1 | Maximo: 20): ");
        scanf ("%d", &operadores);
        if (operadores < 1 || operadores > 20) {
            printf(RED "\nLimite dos operadores nao respeitado\n" );
            printf ("Digite novamente!!\n\n" NORMAL);
        }
        
    } while (operadores < 1 || operadores > 20);
    printf ("TEMPO DE OPERACAO: ");
    scanf("%d", &tempoOperacao);

    InserindoTarefa(fila, Ptr);
    while(operadores > 0) {
        if (!FilaVazia(fila.quantidade)) {
            VetorAux[tlVetAux] = RetirarCircular(fila);
            tlVetAux++;
            operadores--;
        }
    }
    for (i=0;i<tlVetAux;i++)
        printf("%s - %d - %s\n", VetorAux[i].tipo, VetorAux[i].tempo, VetorAux[i].DescricaoTarefa);
    getch();

    while (tempoOperacao >= 0) {

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

            if (VetorAux[i].tempo <= 0) {

                for (j=i;j<tlVetAux-1;j++) 
                    VetorAux[j] = VetorAux[j+1];
                if (!FilaVazia(fila.quantidade)) {
                    VetorAux[j] = RetirarCircular(fila);
                } 
                // else 
                //     tlVetAux--;
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
        if(contInsere == 5) {
            InsereDepois(fila, Ptr);
            contInsere = 0;
        }
        clrscr();
        tituloOperadores();
        tituloFila();
        printf ("\n\n");
        for (i=0;i<tlVetAux;i++) {
            if (VetorAux[i].tempo < 10){
                printf(GREEN "0%ds" NORMAL " | (%s) %s\n", VetorAux[i].tempo, VetorAux[i].tipo, VetorAux[i].DescricaoTarefa);
                
            } else if(VetorAux[i].tempo < 20) {
                printf(YELLOW "%ds" NORMAL " | (%s) %s\n", VetorAux[i].tempo, VetorAux[i].tipo, VetorAux[i].DescricaoTarefa);
    
            } else { 
                printf("%ds | (%s) %s\n", VetorAux[i].tempo, VetorAux[i].tipo, VetorAux[i].DescricaoTarefa);

            }
        }
        ExibirFila(fila);
        printf ("\n\n");
        if (tempoOperacao < 10){
            gotoxy(0,30); printf ("\nTEMPO: " RED "%ds\n" NORMAL, tempoOperacao);
            
        } else if(tempoOperacao < 20) {
            gotoxy(0,30); printf ("\nTEMPO: " YELLOW "%ds\n" NORMAL, tempoOperacao);

        } else { 
            gotoxy(0,30); printf ("\nTEMPO: %ds\n", tempoOperacao);
        }
        sleep(1);
        tempoOperacao--;
        contInsere++;
    }

    for (i=0;i<tlVetAux;i++) {
        if (VetorAux[i].tempo > 0)
            contTarefasIncompletas++;
    }
    while(!FilaVazia(fila.quantidade)) {
        RetirarCircular(fila);
        contTarefasIncompletas++;
    }
    if (contUrgente > 0) 
        tempoUrgente = tempoUrgente/contUrgente;
    if (contNormal > 0) 
        tempoNormal = tempoNormal/contNormal;
    if (contOpcional > 0) 
        tempoOpcional = tempoOpcional/contOpcional;
    printf("\n\n");
    tituloRelatorio();
    gotox(60); printf ("TEMPO MEDIO URGENTE: %.2f\n", tempoUrgente);
    gotox(60); printf ("TEMPO MEDIO NORMAL: %.2f\n", tempoNormal);
    gotox(60); printf ("TEMPO MEDIO OPCIONAL: %.2f\n", tempoOpcional);
    gotox(60); printf ("TAREFAS CONCLUIDAS: %d\n", contTarefasConcluidas);
    gotox(60); printf ("TAREFAS NAO CONCLUIDAS: %d\n", contTarefasIncompletas);
    getch();

    clrscr();
    tituloNome();
    printf("\n");
    for (i=0;i<3;i++) {
        for (j=0;nome[i][j] != '\0'; j++)
            printf ("%c", nome[i][j]);
        printf ("\n\n");
    }
    
    fclose(Ptr);
}


void tituloRelatorio(void) {
    gotox(40); printf(CYAN "$$$$$$$\\            $$\\            $$\\                         $$\\           \n");
    gotox(40); printf("$$  __$$\\           $$ |           $$ |                        \\__|          \n");
    gotox(40); printf("$$ |  $$ | $$$$$$\\  $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\  $$$$$$\\  \n");
    gotox(40); printf("$$$$$$$  |$$  __$$\\ $$ | \\____$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ $$ |$$  __$$\\ \n");
    gotox(40); printf("$$  __$$< $$$$$$$$ |$$ | $$$$$$$ | $$ |    $$ /  $$ |$$ |  \\__|$$ |$$ /  $$ | \n");
    gotox(40); printf("$$ |  $$ |$$   ____|$$ |$$  __$$ | $$ |$$\\ $$ |  $$ |$$ |      $$ |$$ |  $$ | \n");
    gotox(40); printf("$$ |  $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ | \\$$$$  |\\$$$$$$  |$$ |      $$ |\\$$$$$$  | \n");
    gotox(40); printf("\\__|  \\__| \\_______|\\__| \\_______|  \\____/  \\______/ \\__|      \\__| \\______/\n\n\n\n" NORMAL);
}

void tituloFabrica (void) {
    printf(GREEN "$$$$$$$$\\       $$\\                 $$\\                    \n");
    printf("$$  _____|      $$ |                \\__|                   \n");
    printf("$$ |   $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$\\  $$$$$$$\\ $$$$$$\\  \n");
    printf("$$$$$\\ \\____$$\\ $$  __$$\\ $$  __$$\\ $$ |$$  _____|\\____$$\\ \n");
    printf("$$  __|$$$$$$$ |$$ |  $$ |$$ |  \\__|$$ |$$ /      $$$$$$$ |\n");
    printf("$$ |  $$  __$$ |$$ |  $$ |$$ |      $$ |$$ |     $$  __$$ |\n");
    printf("$$ |  \\\$$$$$$$ |$$$$$$$  |$$ |      $$ |\\$$$$$$$\\\\$$$$$$$ |\n");
    printf("\\__|   \\_______|\\_______/ \\__|      \\__| \\_______|\\_______|\n\n\n\n" NORMAL);
}


void tituloOperadores (void) {
    printf(CYAN "   ___  ____  _____ ____      _    ____   ___  ____  _____ ____  \n");
    printf("  / _ \\|  _ \\| ____|  _ \\    / \\  |  _ \\ / _ \\|  _ \\| ____/ ___| \n");
    printf(" | | | | |_) |  _| | |_) |  / _ \\ | | | | | | | |_) |  _| \\___ \\ \n");
    printf(" | |_| |  __/| |___|  _ <  / ___ \\| |_| | |_| |  _ <| |___ ___) | \n");
    printf("  \\___/|_|   |_____|_| \\_\\/_/   \\_\\____/ \\___/|_| \\_\\_____|____/ \n\n" NORMAL);
}

void tituloFila(void) {
    gotoxy(80,1); printf(CYAN "  _____ ___ _        _    \n");
    gotoxy(80,2); printf(" |  ___|_ _| |      / \\   \n");
    gotoxy(80,3); printf(" | |_   | || |     / _ \\  \n");
    gotoxy(80,4); printf(" |  _|  | || |___ / ___ \\ \n");
    gotoxy(80,5); printf(" |_|   |___|_____/_/   \\_\\" NORMAL);
}

void tituloNome(void) {
    printf(CYAN "$$\\   $$\\                                   \n");
    printf("$$$\\  $$ |                                  \n");
    printf("$$$$\\ $$ | $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\  \n");
    printf("$$ $$\\$$ |$$  __$$\\ $$  _$$  _$$\\ $$  __$$\\ \n");
    printf("$$ \\$$$$ |$$ /  $$ |$$ / $$ / $$ |$$$$$$$$ | \n");
    printf("$$ |\\$$$ |$$ |  $$ |$$ | $$ | $$ |$$   ____| \n");
    printf("$$ | \\$$ |\\$$$$$$  |$$ | $$ | $$ |\\$$$$$$$\\ \n");
    printf("\\__|  \\__| \\______/ \\__| \\__| \\__| \\_______| \n" NORMAL);
}
int main(){
    TpFilaPrioridade fila;
    char nome[3][50];
    clrscr();
    tituloNome();
    printf ("\nBryan dos Santos Cruz\n");
    printf ("\nLucas Filipe Camargo Giraldino\n");
    printf ("\nFelipe Lima Santos\n");
    strcpy(nome[0], "Bryan dos Santos Cruz");
    strcpy(nome[1], "Lucas Filipe Camargo Giraldino");
    strcpy(nome[2], "Felipe Lima Santos");
    Inicializar(fila);
    sleep(3);
    clrscr();
    Operadores(fila, nome);
    getch();
    ExibirFila(fila);
    return 0;
}