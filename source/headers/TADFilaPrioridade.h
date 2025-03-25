#define MAXFILA 1000

struct TpTarefa {
    char DescricaoTarefa[50];
    int tempo;
    char tipo[10];
    int prioridade;
};

struct TpFilaPrioridade  {
    int inicio;
    int qtde;
    int fim;
    TpTarefa FILA[MAXFILA];
};

void Inicializar (TpFilaPrioridade &fila);
void Inserir (TpFilaPrioridade &fila, TpTarefa elemento);
void Retirar (TpFilaPrioridade &fila);
TpTarefa ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento);
TpTarefa ElementoFim (TpFilaPrioridade fila, TpTarefa &elemento);
char FilaVazia (int fim);
char FilaCheia (int fim);

void Inicializar (TpFilaPrioridade &fila) {
    fila.fim = -1;
    fila.inicio = 0;
    fila.qtde = 0;
}

TpTarefa ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.inicio];
}

TpTarefa ElementoFimPrioridade (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.fim];
}

char FilaVazia (int fim) {
    return fim == -1;
}

char FilaCheia (int fim) {
    return fim == MAXFILA-1;
}

<<<<<<< Updated upstream:source/headers/TADFilaPrioridade.h
void InserirCircular (TpFilaPrioridade &fila, TpTarefa elemento ) {
=======
void Prioridade (TpFilaPrioridade &fila) {
    if (strcasecmp(fila.FILA[fila.fim].tipo, "Urgente") == 0)
    fila.FILA[fila.fim].prioridade = 1;
    else  
        if (strcasecmp(fila.FILA[fila.fim].tipo, "Normal") == 0)
            fila.FILA[fila.fim].prioridade = 2;
        else
            fila.FILA[fila.fim].prioridade = 3;
}

void Inserir (TpFilaPrioridade &fila, TpTarefa elemento ) {
>>>>>>> Stashed changes:TADFilaPrioridade.h
    TpTarefa Aux;
    int i, fim, qtdAux;

    fila.FILA[++fila.fim] = elemento;
    qtdAux = ++fila.qtde;
    fim = fila.fim;

    Prioridade(fila);
    if (fila.fim > fila.inicio) {
        i = fila.fim-1;
        while (i>=fila.inicio && elemento.prioridade < fila.FILA[i].prioridade) {
            Aux = fila.FILA[i];
            fila.FILA[i] = elemento;
            fila.FILA[i+1] = Aux;
            i--;
        }
    } else {
        if(fila.fim > 0)
            i = fila.fim-1;
        while (qtdAux > 0 && elemento.prioridade < fila.FILA[i].prioridade) {
            if (i >= 0) {
                Aux = fila.FILA[i];
                fila.FILA[i] = elemento;
                fila.FILA[i+1] = Aux;
            }
            else {
                i = MAXFILA-1;
                Aux = fila.FILA[i];
                fila.FILA[i] = elemento;
                fila.FILA[0] = Aux;
            }
            i--;
            qtdAux--;
        }
    }
}

TpTarefa RetirarCircular (TpFilaPrioridade &fila) {
    TpTarefa aux;

    aux = fila.FILA[fila.inicio];

    if (fila.inicio == MAXFILA-1)
        fila.inicio = 0;
    else
        fila.inicio++;
    return aux;
}