#define MAXFILA 1000

struct TpTarefa {
    char DescricaoTarefa[50];
    int tempo;
    char prioridade[10];
};

struct TpFilaPrioridade  {
    int fim;
    TpTarefa FILA[MAXFILA];
};

void Inicializar (TpFilaPrioridade &fila);
void Inserir (TpFilaPrioridade &fila, TpTarefa elemento);
void Retirar (TpFilaPrioridade &fila);
void ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento);
void ElementoFim (TpFilaPrioridade fila, TpTarefa &elemento);
char FilaVazia (int fim);
char FilaCheia (int fim);

void Inicializar (TpFilaPrioridade &fila) {
    fila.fim = -1;
}

void Inserir (TpFilaPrioridade &fila, TpTarefa elemento) {
    TpTarefa Aux;
    int i=fila.fim;

    fila.FILA[++fila.fim] = elemento;
    while (i>=0 && elemento.prioridade < fila.FILA[i].prioridade) {
        Aux = fila.FILA[i];
        fila.FILA[i] = elemento;
        fila.FILA[i+1] = Aux;
        i--;
    }
}

void Retirar (TpFilaPrioridade &fila, TpTarefa &elemento) {
    int i;

    elemento = fila.FILA[0];
    for (i=0;i<fila.fim;i++) 
        fila.FILA[i] = fila.FILA[i+1];
    fila.fim--;
}

void ElementoInicio (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[0];
}

void ElementoFimPrioridade (TpFilaPrioridade fila, TpTarefa &elemento) {
    elemento = fila.FILA[fila.fim];
}

char FilaVazia (int fim) {
    return fim == -1;
}

char FilaCheia (int fim) {
    return fim == MAXFILA-1;
}

