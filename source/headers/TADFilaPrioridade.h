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

void compararEOrdernarTarefas(TpFilaPrioridade &fila, TpTarefa primeiraTarefa, TpTarefa segundaTarefa, int &fim) {
    if (segundaTarefa.prioridade > primeiraTarefa.prioridade) {
        fila.FILA[fim] = segundaTarefa;
        fila.FILA[fim - 1] = primeiraTarefa;
    }
    
    fim--;
}

void Inserir(TpFilaPrioridade &fila, TpTarefa elemento ) {
    TpTarefa auxTarefa;

    fila.FILA[++fila.fim] = elemento;
    fila.quantidade++;

    int fim = fila.fim;
    for(int i = 1; i < fila.quantidade; i++) {
        if ((fim - 1) < 0) { // Vefica se não está comparando o fim com lixo, e precisa dar a volta no vetor
            TpTarefa primeiraTarefa = fila.FILA[fim];
            TpTarefa segundaTarefa = fila.FILA[MAXFILA - 1];
            compararEOrdernarTarefas(fila, primeiraTarefa, segundaTarefa, fim);

            fim = MAXFILA - 1;
        } else { // Significa que o fim está linear ao inicio, e não precisamos dar a volta no vetor
            TpTarefa primeiraTarefa = fila.FILA[fim];
            TpTarefa segundaTarefa = fila.FILA[fim - 1];
            compararEOrdernarTarefas(fila, primeiraTarefa, segundaTarefa, fim);
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