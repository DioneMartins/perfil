#include <stdlib.h>

typedef struct _JOGADOR {
    char nome[50];
    int ordem, casa, ficha, mediador;
} JOGADOR;

int i_jogo(); void m_jogo(); JOGADOR cadastra_jogador(int i);

int i_jogo(){
    JOGADOR *jog;
    int c=0; int i;

    printf("Quantos jogadores vao participar? [1-6] ");
    scanf("%d", &c);
    if(c<1 && c>6) {
        printf("Valor invalido.\n");
        return 1;
    }

    jog = calloc(c, sizeof(JOGADOR));
    if(!c) {
        printf("Erro de alocacao, tente novamente.\n");
        return 1;
    }
    clear();

    for(i=0; i<c; i++) jog[i]=cadastra_jogador(i);

    m_jogo();
    free(jog);
    return 0;
}

void m_jogo(){
    printf("Jogo\n");
}

JOGADOR cadastra_jogador(int i){
    JOGADOR jogador;
    clear();
    printf("%dº jogador\n", i);
    printf("Nome: ");
    fgets(jogador.nome, 50, stdin);
    jogador.ordem=i;
    jogador.casa=1;
    jogador.ficha=0;
    if(i==1) jogador.mediador=1;
    else jogador.mediador=0;
    return jogador;
}