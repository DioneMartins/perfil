#include <stdio.h>

int cadastra_c(); int exclui_c(); int conta_c();

void m_cartoes(){
    char c='0';
    while(1){
        printf("Menu de cartoes...\n"
            "1 Cadastrar cartao\n"
            "2 Excluir cartao\n"
            "3 Numero de cartoes\n"
            "4 Voltar\n"
        );
        c=getc(stdin);
        flush();
        clear();
        if(c=='1') cadastra_c();
        else if(c=='2') exclui_c();
        else if(c=='3') conta_c();
        else if(c=='4') break;
        else printf("Opcao invalida.\n");
    }
}

int cadastra_c(){
    FILE *file;
    char nome[51], categoria[7], dicas[20][101], opcao='0';
    int i=1;

    file = fopen("banco.txt", "a+");
    if (file==NULL){
        printf("Erro abrindo o arquivo.\n");
        return 1;
    }

    /*Recebe nome e categoria*/
    while(1){
        printf("Objeto do cartao [50]: ");
        fgets(nome, 50, stdin);
        printf("Categoria[pessoa/lugar/coisa/ano]: ");
        fgets(categoria, 7, stdin);
        categoria[strlen(categoria)-1] = '\0'; /*Remove \n no final*/
        for(i=0; i<strlen(categoria); i++) categoria[i]=tolower(categoria[i]);
        if(strcmp(categoria, "pessoa")==0 || strcmp(categoria, "lugar")==0 ||
            strcmp(categoria, "coisa")==0 || strcmp(categoria, "ano")==0) break;
        else printf("Categoria incorreta.\n");
    }
    clear();
    i=0;

    /*Recebe as 20 dicas*/
    while(i<20){
        printf("ATENÇÃO:\n\n"
        "Formato|                   Ação                    | Exemplo\n"
        "!pv   === perca a vez                             === !pv\n"
        "!ax   === avance x casas                          === !a3\n"
        "!vx   === volte x casas                           === !v3\n"
        "!pqh  === palpite a qualquer hora                 === !pqh\n"
        "!jax  === escolha um jogador para avançar x casas === !ja2\n"
        "!jvx  === escolha um jogador para voltar x casas  === !jv2\n");
        printf("Dica %d [100]: ", i+1);
        fgets(dicas[i], 100, stdin);
        if(dicas[i][0]!='\n') i++;
        else {printf("Texto invalido\n"); flush();}
        clear();
    }

    printf("Eu sou ");
    puts(nome);
    printf("Diga aos jogadores que eu sou "); printc(categoria);
    for(i=0; i<20; i++) printd(i+1, dicas[i]);
    printf("Salvar cartao? [S/n]\n");
    opcao=getc(stdin);
    flush();
    if(opcao=='N' || opcao=='n') return 1;

    /*Armazena em arquivo*/
    nome[strlen(nome)-1] = '\0'; /*Remove \n no final*/
    fprintf(file, "cartao_%s_%s\n", nome, categoria);
    for(i=0; i<20; i++){
        dicas[i][strlen(dicas[i])-1] = '\0'; /*Remove \n no final*/
        fprintf(file, "%d_%s\n", i+1, dicas[i]);
    }
    fclose(file);

    printf("Salvo com sucesso. Pressione qualquer tecla para voltar ao menu.\n");
    return 0;
}

int exclui_c(){
    printf("exclui\n");
    return 0;
}

int conta_c(){
    printf("conta\n");
    return 0;
}