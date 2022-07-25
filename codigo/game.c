#include <stdio.h>
#include <stdlib.h>

typedef struct _JOGADOR {
    char nome[50];
    int ordem, casa, ficha, mediador;
} JOGADOR;

typedef struct _CARTAO {
    char nome[51], categoria[10], dicas[20][102];
    int dicas_usadas[20];
} CARTAO;

int i_jogo(); int m_jogo(JOGADOR jog[], int count); int s_jogo(JOGADOR jog);
JOGADOR cadastra_jogador(int i);
CARTAO escolhe_cartao(FILE *f, int r);
void exibe_dicas(int dicas_usadas[], size_t n); int dica_ja_usada(int dicas_usadas[], int dica);


int i_jogo(){
    JOGADOR *jog;
    int c=0; int i;

    printf("Quantos jogadores vao participar? [1-6] ");
    scanf("%d", &c); flush();
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

    if(c>1) m_jogo(jog, c);
    else s_jogo(jog[0]);
    free(jog);
    return 0;
}

int m_jogo(JOGADOR jog[], int count){
    int i=0, j=i+1, vencedor=-1, total_c=0, r=0, x=0, y=0, uso=0;
    char ideia[50]; int opcao_dica=0;
    FILE *file;
    CARTAO cartao;

    /*Preparacao para o jogo*/
    file=fopen("banco.txt", "r");
    if(file==NULL){
        printf("Erro abrindo arquivo.\n");
        return 1;
    }
    total_c=conta_c();

    printf("Perssione enter para comecar...\n");
    flush();

    /*Loop do jogo*/
    while(1){
        r=randint(total_c);
        cartao=escolhe_cartao(file, r);
        for(x=0; x<20; x++) cartao.dicas_usadas[x]=0;
        while(1){
            printf("Mediador: %s(%d)\n", jog[i].nome, jog[i].casa);
            printf("Jogador da vez: %s(%d)\n", jog[j].nome, jog[j].casa);
            printf("\nEu sou... "); printc(cartao.categoria);
            exibe_dicas(cartao.dicas_usadas, (sizeof(cartao.dicas_usadas)/sizeof(int)));
            printf("\nPronto, jogador %s... Que dica voce quer? [1-20] ", jog[j].nome);
            scanf("%d", &opcao_dica);
            uso=dica_ja_usada(cartao.dicas_usadas, opcao_dica);
            if(opcao_dica<1 || opcao_dica>20 || uso){
                if(!uso) printf("Opcao invalida\n");
                else printf("Dica ja pedida.\n");
            }
            else{
                printf("Atencao, mesa... ");
                printd(0, cartao.dicas[opcao_dica-1], 0);
                cartao.dicas_usadas[y]=opcao_dica;
                y++;
                j++; if(j==count) j=1;
                printf("\nJogador %s... Qual e o seu palpite? [50] ", jog[j].nome);
                fgets(ideia, 50, stdin);
                ideia[strlen(ideia)-1] = '\0';
                if(strcmp(ideia, cartao.nome)==0) {
                    printf("... Correto!\n");
                }
            }
        }
    }
    return 0;
}

/*
Mediador: Dione(1)
Jogador da vez: Leo(1)
Próximo jogador: Valéria(1)

Eu sou... um lugar!
Dicas: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Pronto, jogador Leo... Que dica você quer? `2`
Atenção, mesa... Não tenho satélites.

Jogador Leo, qual é seu palpite? ` `
...
*/

int s_jogo(JOGADOR jog){
    printf("Singleplayer\n");
    return 0;
}

JOGADOR cadastra_jogador(int i){
    JOGADOR jogador;
    clear();
    printf("%dº jogador\n", i+1);
    printf("Nome: ");
    fgets(jogador.nome, 50, stdin);
    jogador.nome[strlen(jogador.nome)-1] = '\0';
    jogador.ordem=i;
    jogador.casa=1;
    jogador.ficha=0;
    if(i==1) jogador.mediador=1;
    else jogador.mediador=0;
    return jogador;
}

CARTAO escolhe_cartao(FILE *f, int r){
    int c=0, i=0, descarte;
    CARTAO cartao;
    rewind(f);
    while(!feof(f)){
        fscanf(f, "cartao_%[^_]%*c%[^\n]", cartao.nome, cartao.categoria); fgetc(f);
        for(i=0; i<20; i++){
            fscanf(f, "%d%*c%[^\n]", &descarte, cartao.dicas[i]); fgetc(f);
        }
        c++;
        if(c==r) break;
    }
    return cartao;
}

void exibe_dicas(int dicas_usadas[], size_t n){
    int i=0, usada=0;
    printf("Dicas: ");
    for(i=1; i<=20; i++){
        usada=dica_ja_usada(dicas_usadas, i);
        if(!usada) printf(" %d", i);
        else printf(" X");
        usada=0;
    }
}

int dica_ja_usada(int dicas_usadas[], int dica){
    int i=0, usada=0;
    for(i=0; i<20; i++){
        if(dica==dicas_usadas[i]) {
            usada=1;
            break;
        }
    }
    if(usada) return 1;
    else return 0;
}