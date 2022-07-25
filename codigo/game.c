#include <stdio.h>
#include <stdlib.h>

typedef struct _JOGADOR {
    char nome[50];
    int ordem, casa, ficha;
} JOGADOR;

typedef struct _CARTAO {
    char nome[51], categoria[10], dicas[20][102];
    int dicas_usadas[20];
} CARTAO;

typedef struct _RODADA {
    int vencedor; /*Numero do vencedor no array*/
    int nd; /*Numero de dicas usadas*/
    CARTAO cartao; /*Cartao da rodada*/
} RODADA;

int i_jogo(); int m_jogo(JOGADOR jog[], int count);
JOGADOR cadastra_jogador(int i);
CARTAO escolhe_cartao(FILE *f, int r);
void exibe_dicas(int dicas_usadas[], size_t n); int dica_ja_usada(int dicas_usadas[], int dica);
void palpite_a_qualquer_hora(JOGADOR jog[], int n, char *input, int jog_atual, RODADA rodada);
void palpite(JOGADOR jogador, RODADA rodada, char *input, int pontua, int *vence, int exibe);
int final_rodada(RODADA rodada, JOGADOR jogadores[], int n, int *med);
void tela_final(JOGADOR jogadores[], int n);
int is_okay(int r, int cartoes[5]);

int i_jogo(){
    JOGADOR *jog;
    int c=0; int i;

    printf("Quantos jogadores vao participar? [2-10] ");
    scanf("%d", &c); flush();
    if(c<2 && c>10) {
        printf("Valor invalido.\n");
        return 1;
    }

    jog = calloc(c, sizeof(JOGADOR));
    if(!c) {
        printf("Erro de alocacao, tente novamente.\n");
        return 1;
    }
    clear();

    for(i=0; i<c; i++) {
        jog[i]=cadastra_jogador(i);
        if(jog[i].nome[0]=='\0'){
            printf("Nome em branco.\n");
            flush();
            return 1;
        }
    }

    m_jogo(jog, c);
    free(jog);
    return 0;
}

int m_jogo(JOGADOR jogadores[], int count){
    /*Declaracao de variaveis*/
    int med=0, vez=med+1;/*Mediador da rodada e jogador da vez*/
    int fim_do_jogo=0;
    int total_c=0, cartao_da_vez=0; /*Numero total de cartoes e numero do cartao escolhido randomicamente*/
    int uso=0, comando=0; /*Bool para o cartao ja ter sido usado e numero do comando*/
    int x=0; /*Int generico*/
    int andou=0; /*Boll para se o jogador ja andou*/
    char string_input[50]; int int_input=0; /*Inputs genericos*/
    int ultimos_cartoes[5];
    RODADA rodada;
    FILE *file;

    /*Preparacao para o jogo*/
    file=fopen("banco.txt", "r");
    if(file==NULL){
        printf("Erro abrindo arquivo.\n");
        return 1;
    }
    total_c=conta_c();
    if(total_c<6) {
        printf("Nao e possivel iniciar um jogo com esse numero de cartoes.\n");
        printf("Por favor, considere recuperar o arquivo inicial ou cadastrar novos cartoes.\n");
        printf("Pressione enter para voltar ao menu inicial.\n");
        flush();
        return 1;
    }
    for(x=0; x<4; x++){
        ultimos_cartoes[x]=0;
    }

    printf("Perssione enter para comecar...\n");
    flush();

    /*Loop do jogo*/
    while(fim_do_jogo==0){
        /*Nova rodada*/
        printf("Aguarde...\n");
        while(1){
            cartao_da_vez=randint(total_c);
            if(is_okay(cartao_da_vez, ultimos_cartoes)){
                for(x=0; x<4; x++){
                    ultimos_cartoes[x]=ultimos_cartoes[x+1];
                }
                ultimos_cartoes[4]=cartao_da_vez;
                rodada.cartao=escolhe_cartao(file, cartao_da_vez);
                break;
            }
        }

        for(x=0; x<20; x++) rodada.cartao.dicas_usadas[x]=0; /*Reseta o array de dicas usadas*/
        rodada.nd=0; /*Reseta o numero de dicas usadas*/

        vez=med+1; if(vez>=count) vez=0;

        rodada.vencedor=-1;

        for(x=0; x<count; x++) jogadores[x].ficha=0;

        clear();
        while(1){
            uso=0;
            if(vez!=med){
                comando=0;
                printf("Mediador: %s(%d)\n", jogadores[med].nome, jogadores[med].casa);
                printf("Jogador da vez: %s(%d)\n", jogadores[vez].nome, jogadores[vez].casa);
                printf("\nEu sou... "); printc(rodada.cartao.categoria);
                exibe_dicas(rodada.cartao.dicas_usadas, (sizeof(rodada.cartao.dicas_usadas)/sizeof(int)));
                printf("\nPronto, jogador %s... Que dica voce quer? [1-20] ", jogadores[vez].nome);
                scanf("%d", &int_input); flush();
                uso=dica_ja_usada(rodada.cartao.dicas_usadas, int_input);
                if(int_input<1 || int_input>20 || uso){
                    if(!uso) printf("Opcao invalida\n");
                    else printf("Dica ja pedida.\n");
                    uso=1;
                }
                else{
                    printf("Atencao, mesa... ");
                    printd(0, rodada.cartao.dicas[int_input-1], 0);
                    rodada.cartao.dicas_usadas[rodada.nd]=int_input;
                    rodada.nd++;
                    if(rodada.cartao.dicas[int_input-1][0]=='!'){
                        comando=markd(rodada.cartao.dicas[int_input-1]);
                        switch(comando){
                            case 2:
                                jogadores[vez].ficha=1;
                                break;
                            case 3:
                                jogadores[vez].casa+=((rodada.cartao.dicas[int_input-1][2])-'0');
                                break;
                            case 4:
                                jogadores[vez].casa-=((rodada.cartao.dicas[int_input-1][2])-'0');
                                if(jogadores[vez].casa<1) jogadores[vez].casa=1;
                                break;
                            case 5:
                                while(1){
                                    andou=0;
                                    printf("Que jogador você escolhe? (exceto si mesmo) \n");
                                    fgets(string_input, 50, stdin);
                                    string_input[strlen(string_input)-1] = '\0';
                                    if(strcmp(string_input, jogadores[vez].nome)==0) printf("Voce nao pode escolher a si mesmo!");
                                    else {
                                            for(x=0; x<count; x++){
                                            if(strcmp(string_input, jogadores[x].nome)==0) {
                                                jogadores[x].casa+=((rodada.cartao.dicas[int_input-1][3])-'0');
                                                andou=1;
                                                break;
                                            }
                                        }
                                        if(!andou) printf("Jogador nao encontrado.\n");
                                        else break;
                                    }
                                }
                                break;
                            case 6:
                                while(1){
                                    andou=0;
                                    printf("Que jogador você escolhe? (exceto si mesmo) \n");
                                    fgets(string_input, 50, stdin);
                                    string_input[strlen(string_input)-1] = '\0';
                                    if(strcmp(string_input, jogadores[vez].nome)==0) printf("Voce nao pode escolher a si mesmo!\n");
                                    else {
                                            for(x=0; x<count; x++){
                                            if(strcmp(string_input, jogadores[x].nome)==0) {
                                                jogadores[x].casa-=((rodada.cartao.dicas[int_input-1][3])-'0');
                                                if(jogadores[x].casa<1) jogadores[x].casa=1;
                                                andou=1;
                                                break;
                                            }
                                        }
                                        if(!andou) printf("Jogador nao encontrado.\n");
                                        else break;
                                    }
                                }
                                break;
                        }
                    }
                    if(comando!=1){
                        printf("\nJogador %s... Qual e o seu palpite? [50] ", jogadores[vez].nome);
                        fgets(string_input, 50, stdin);
                        string_input[strlen(string_input)-1] = '\0'; /*Remove \n*/
                        if(string_input[0]=='!')
                            palpite_a_qualquer_hora(jogadores, count, string_input, vez, rodada);
                        else palpite(jogadores[vez], rodada, string_input, vez, &rodada.vencedor, 0);
                    }
                }
                if(rodada.vencedor!=-1) {
                    printf("Fim da rodada...\n"); 
                    printf("\nPressione enter para continuar.\n"); flush(); clear();
                    break;
                }
                else if(rodada.nd==20) {
                    printf("Fim da rodada...\n"); 
                    printf("\nPressione enter para continuar.\n"); flush(); clear();
                    break;
                }
                else{
                    printf("\nPressione enter para continuar.\n"); flush(); clear();
                }
            }
            if(!uso) {vez++; if(vez>=count) vez=0;}
        }
        fim_do_jogo = final_rodada(rodada, jogadores, count, &med);
        if(fim_do_jogo) break;
    }
    tela_final(jogadores, count);
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

void palpite_a_qualquer_hora(JOGADOR jog[], int n, char *input, int jog_atual, RODADA rodada){
    int i=0, encontrado=0;
    char nome[50];
    if(input[5]=='\0') printf("Formato: !pqh jogador\n");
    else{
        for(i=0; i<strlen(input)-5; i++){
            nome[i]=input[i+5];
        }
        nome[i]='\0';
        for(i=0; i<n; i++){
            if(strcmp(nome, jog[i].nome)==0){
                encontrado=1;
                if(jog[i].ficha==1) {
                    jog[i].ficha=0;
                    palpite(jog[i], rodada, input, jog_atual, &rodada.vencedor, 1);
                    if(rodada.vencedor==-1) palpite(jog[jog_atual], rodada, input, jog_atual, &rodada.vencedor, 1);
                }
                else {
                    printf("Voce nao tem palpites.\n"); flush();
                    palpite(jog[jog_atual], rodada, input, jog_atual, &rodada.vencedor, 0);
                }
                break;
            }
        }
    }
    if(!encontrado){
        printf("Jogador nao encontrado ou formato incorreto.\n"); flush();
        palpite(jog[jog_atual], rodada, input, jog_atual, &rodada.vencedor, 0);
    }
}

void palpite(JOGADOR jogador, RODADA rodada, char *input, int pontua, int *vence, int exibe){
    if(exibe){
        printf("\nJogador %s... Qual e o seu palpite? [50] ", jogador.nome);
        fgets(input, 50, stdin);
        input[strlen(input)-1]='\0';
    }
    uppercase(input, strlen(input)); /*Passa tudo para maiuscula*/
    if(strcmp(input, rodada.cartao.nome)==0) {
        printf("... Correto!\n");
        *vence=pontua;
    }
    else {
        if(input[0]!='\0') printf("... Incorreto!\n");
    }
}

int final_rodada(RODADA rodada, JOGADOR jogadores[], int n, int *med){
    int i=0; int vencido=0;
    printf("Atencao a contagem de pontos...\n");
    printf("Foram lidas %d dicas...\n", rodada.nd);
    printf("Mediador %s avanca %d casas...\n", jogadores[*med].nome, rodada.nd);
    jogadores[*med].casa+=rodada.nd;
    if(rodada.vencedor!=-1) {
        printf("Jogador %s avanca %d casas...\n", jogadores[rodada.vencedor].nome, 20-rodada.nd);
        jogadores[rodada.vencedor].casa+=20-rodada.nd;
    }
    printf("\nNova pontuacao: \n");
    for(i=0; i<n; i++){
        printf("%s(%d)\n", jogadores[i].nome, jogadores[i].casa);
        if(jogadores[i].casa>=134) vencido=1;
    }
    *med=*med+1; if(*med==n) *med=0;
    if(vencido) printf("Temos um vencedor!\n");
    else printf("\nO proximo mediador e... %s\n", jogadores[*med].nome);
    printf("\nPressione enter para continuar...\n"); flush(); clear();

    /*Resetando tudo*/
    rodada.nd=0;
    rodada.vencedor=-1;

    return vencido;
}

void tela_final(JOGADOR jogadores[], int n){
    JOGADOR temp;
    int i=0, j=0;
    for(i=0; i<n; i++){
        for(j=0; j<n-1-i; j++){
            if(jogadores[j].casa < jogadores[j+1].casa){
                temp=jogadores[j];
                jogadores[j]=jogadores[j+1];
                jogadores[j+1]=temp;
            }
        }
    }
    printf("Parabens, jogador %s\n\n", jogadores[0].nome);
    printf("Posicoes finais:\n\n");
    for(i=0; i<n; i++){
        printf("%s(%d)\n", jogadores[i].nome, jogadores[i].casa);
    }
    printf("\nPressione enter para voltar ao menu principal...\n"); flush(); clear();
}

int is_okay(int r, int cartoes[5]){
    int i=0, is_ok=1;
    for(i=0; i<5; i++){
        if(r==cartoes[i]) is_ok=0;
    }
    return is_ok;
}