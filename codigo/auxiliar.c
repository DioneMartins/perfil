#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int markd(char *dica){
    if(dica[0]=='!'){
        switch(dica[1]){
            case 'p':
                if(dica[2]=='v') return 1;
                else return 2;
                break;
            case 'a':
                return 3;
                break;
            case 'v':
                return 4;
                break;
            case 'j':
                if(dica[2]=='a') return 5;
                else return 6;
                break;
        }
    }
    else return 0;
    return 0;
}

void printd(int i, char *dica, int printnum){
    int x=0;
    if(printnum) printf("%d. ", i);
    x=markd(dica);
    switch(x){
        case 0: puts(dica);
        case 1: printf("Perca a vez.\n\n"); break;
        case 2: printf("Um palpite a qualquer hora.\n\n"); break;
        case 3: printf("Avance %c espacos.\n\n", dica[2]); break;
        case 4: printf("Volte %c espacos.\n\n", dica[2]); break;
        case 5: printf("Escolha um jogador para avancar %c espacos.\n\n", dica[3]); break;
        case 6: printf("Escolha um jogador para voltar %c espacos.\n\n", dica[3]); break;
    }
}

int randint(int n) {
    int r, p=RAND_MAX/n, x=0, y=x+p, i=0;
    srand(time(NULL));
    r=rand();
    while(x<RAND_MAX){
        if(r>x && r<y) break;
        i++;
        x=y;
        y=x+p;
    }
    return i;
}

void uppercase(char *string, int n){
    int i=0; char *pointer;
    for(i=0; i<n; i++){
        pointer=string+i;
        *pointer=toupper(*pointer);
    }
}