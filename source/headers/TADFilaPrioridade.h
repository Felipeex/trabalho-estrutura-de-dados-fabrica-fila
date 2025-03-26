#define MAXFILA 1000

struct TpTarefa {
    char tipo[10];
    char DescricaoTarefa[50];
    int prioridade;
    int tempo;
};

struct TpFilaPrioridade  {
    int inicio;
    int quantidade;
    int fim;
    TpTarefa FILA[MAXFILA];
};

void Inicializar(TpFilaPrioridade &fila);
void Inserir(TpFilaPrioridade &fila, TpTarefa elemento);
TpTarefa RetirarCircular(TpFilaPrioridade &fila);
TpTarefa ElementoInicio(TpFilaPrioridade fila, TpTarefa &elemento);
TpTarefa ElementoFim(TpFilaPrioridade fila, TpTarefa &elemento);
char FilaVazia(int quantidade);
char FilaCheia(int quantidade);

void Inicializar(TpFilaPrioridade &fila) {
    fila.fim = -1;
    fila.inicio = 0;
    fila.quantidade = 0;
}

TpTarefa ElementoInicio(TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.inicio];
}

TpTarefa ElementoFimPrioridade(TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.fim];
}

char FilaVazia(int quantidade) {
    return quantidade == 0;
}

char FilaCheia(int quantidade) {
    return quantidade == MAXFILA;
}

int gerarPrioridade(char tipo[10]) {
    if (!strcasecmp(tipo, "Urgente")) return 1;
    if (!strcasecmp(tipo, "Normal")) return 2;
    
    return 3;
}


void Inserir(TpFilaPrioridade &fila, TpTarefa elemento ) {
    TpTarefa Aux;
    int i, fim, qtdAux;

    fila.FILA[++fila.fim] = elemento;
    qtdAux = ++fila.quantidade;
    fim = fila.fim;

    if(fila.fim > fila.inicio) {
        i = fila.fim-1;
        while(i>=fila.inicio && elemento.prioridade < fila.FILA[i].prioridade) {
            Aux = fila.FILA[i];
            fila.FILA[i] = elemento;
            fila.FILA[i+1] = Aux;
            i--;
        }
    } else {
        if(fila.fim > 0)
            i = fila.fim-1;
        while(qtdAux > 0 && elemento.prioridade < fila.FILA[i].prioridade) {
            if(i >= 0) {
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

TpTarefa RetirarCircular(TpFilaPrioridade &fila) {
    TpTarefa aux;

    aux = fila.FILA[fila.inicio];

    if(fila.inicio == MAXFILA-1)
        fila.inicio = 0;
    else
        fila.inicio++;
    fila.quantidade--;
    return aux;
}