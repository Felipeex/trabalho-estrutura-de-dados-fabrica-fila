#define MAXFILA 1000

struct TpTarefa {
    char DescricaoTarefa[50];
    int tempo;
    char prioridade[10];
};

struct TpFilaPrioridade  {
    int inicio;
    int qtde;
    int fim;
    TpTarefa FILA[MAXFILA];
};

void Inicializar (TpFilaPrioridade &fila);
void Inserir (TpFilaPrioridade &fila, TpTarefa elemento);
TpTarefa Retirar (TpFilaPrioridade &fila);
void ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento);
void ElementoFim (TpFilaPrioridade fila, TpTarefa &elemento);
char FilaVazia (int qtd);
char FilaCheia (int qtd);

void Inicializar (TpFilaPrioridade &fila) {
    fila.fim = -1;
    fila.inicio = 0;
    fila.qtde = 0;
}


void ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.inicio];
}

void ElementoFimPrioridade (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.fim];
}

char FilaVazia (int qtd) {
    return qtd == 0;
}

char FilaCheia (int qtd) {
    return qtd == MAXFILA;
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

TpTarefa Retirar (TpFilaPrioridade &fila) {
    TpTarefa aux;

    aux = fila.FILA[fila.inicio];

    if (fila.inicio == MAXFILA-1)
        fila.inicio = 0;
    else
        fila.inicio++;
    fila.qtde--;
    return aux;
}