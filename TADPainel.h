
// limpar uma área retangular da tela
void limparArea(int x, int y, int largura, int altura) {
    for (int i = 0; i < altura; i++) {
        gotoxy(x, y + i); 
        for (int j = 0; j < largura; j++) {
            printf(" "); 
        }
    }
}
void limparLinha(int x, int y, int largura) {
    gotoxy(x, y); 
    for (int i = 0; i < largura; i++) {
        printf(" "); 
    }
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
    int i;
    textcolor(CorT);
    textbackground(CorF);

    // Desenha os cantos
    gotoxy(CI, LI); printf("%c", 201);  // Canto superior esquerdo.
    gotoxy(CF, LI); printf("%c", 187);  // Canto superior direito.
    gotoxy(CI, LF); printf("%c", 200);  // Canto inferior esquerdo.
    gotoxy(CF, LF); printf("%c", 188);  // Canto inferior direito.

    // Desenha as linhas horizontais (superior e inferior).
    for (i = CI + 1; i < CF; i++) {
        gotoxy(i, LI); printf("%c", 205);
        gotoxy(i, LF); printf("%c", 205);
    }

    // Desenha as linhas verticais (esquerda e direita).
    for (i = LI + 1; i < LF; i++) {
        gotoxy(CI, i); printf("%c", 186);
        gotoxy(CF, i); printf("%c", 186);
    }

    // Desenha o sombreamento para um efeito 3D
    textcolor(8); // Cor cinza para a sombra
    for (i = CI; i <= CF; i++) {
        gotoxy(i, LF + 1); printf("%c", 223); // Linha inferior sombreamento
    }
    for (i = LI; i <= LF; i++) {
        gotoxy(CF + 1, i); printf("%c", 219); // Linha direita sombreamento
    }

    // Reseta a cor do texto e fundo
    textcolor(7);
    textbackground(0);
}

// FunÃ§Ã£o que define o layout do painel principal com melhorias visuais.
void PainelPrincipal(void)
{
    // Moldura principal com fundo cinza escuro e bordas verdes
    Moldura(10, 1, 115, 30, 15, 8);  // Verde para o texto, cinza escuro para o fundo

    // Moldura secundÃ¡ria com fundo preto e bordas cinza claro
    Moldura(11, 2, 114, 4, 7, 0);   // Branco para o texto, fundo preto
    
    textcolor(15); // Define a cor do texto para o tÃ­tulo.
    gotoxy(50, 3); printf("Projeto"); // TÃ­tulo no painel.

    // Molduras internas
    Moldura(11, 5, 50, 26, 10, 0); // Verde claro para o texto, fundo preto
    Moldura(11, 27, 114, 29, 15, 7); // Cinza para o texto, fundo cinza claro

    // Campo de mensagem com fundo preto e borda cinza claro
    textcolor(14);
    gotoxy(12, 28);
    printf("MENSAGEM:"); // Campo de mensagem no painel.
}
