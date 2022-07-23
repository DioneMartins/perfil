#include <stdio.h>
#include "auxiliar.c"
#include "cartao.c"
#include "game.c"

void v_menu();

int main() {
    char c;
    while(1){
        v_menu();
        c=getc(stdin);
        flush();
        clear();
        if(c=='1') i_jogo();
        else if(c=='2') m_cartoes();
        else if(c=='3') break;
    }
    printf("Espero que tenha se divertido!\n");
    return 0;
}

void v_menu(){
    printf("Menu inicial...\n"
        "1 Jogar\n"
        "2 Menu de cartoes\n"
        "3 Sair\n"
    );
}