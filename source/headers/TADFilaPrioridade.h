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

char FilaVazia (int qtde) {
    return qtde == 0;
}

char FilaCheia (int qtde) {
    return qtde == MAXFILA;
}

void Prioridade (TpTarefa &tarefa) {
    if (strcasecmp(tarefa.tipo, "Urgente") == 0)
        tarefa.prioridade = 1;
    else  
        if (strcasecmp(tarefa.tipo, "Normal") == 0)
            tarefa.prioridade = 2;
        else
            tarefa.prioridade = 3;
}

void Inserir (TpFilaPrioridade &fila, TpTarefa elemento ) {
    TpTarefa Aux;
    int i, fim, qtdAux;

    fila.FILA[++fila.fim] = elemento;
    qtdAux = ++fila.qtde;
    fim = fila.fim;

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
    fila.qtde--;
    return aux;
}