#include <stdio.h>
#include <stdlib.h>

void flush(){
    while(getchar() != '\n');
}

void clear(){
    system("clear");
}

void printc(char *categoria){
    if(strcmp(categoria,"ano")==0 || strcmp(categoria,"lugar")==0) printf("um ");
    else printf("uma ");
    puts(categoria);
}

void printd(int i, char *dica){
    printf("%d. ", i);
    if(dica[0]=='!'){
        switch(dica[1]){
            case 'p':
                if(dica[2]=='v') printf("Perca a vez.\n\n");
                else printf("Um palpite a qualquer hora.\n\n");
                break;
            case 'a':
                printf("Avance %c espacos.\n\n", dica[2]);
                break;
            case 'v':
                printf("Volte %c espacos.\n\n", dica[2]);
                break;
            case 'j':
                if(dica[2]=='a') printf("Escolha um jogador para avancar %c espacos.\n\n", dica[3]);
                else printf("Escolha um jogador para voltar %c espacos.\n\n", dica[3]);
                break;
        }
    }else puts(dica);
}