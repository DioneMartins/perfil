#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.c"
#include "cartao.c"
#include "game.c"

void v_menu(); void tutorial();

int main() {
    char c='0';
    while(1){
        v_menu();
        c=getc(stdin);
        flush();
        clear();
        if(c=='1') i_jogo();
        else if(c=='2') tutorial();
        else if(c=='3') m_cartoes();
        else if(c=='4') break;
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

void tutorial(){
    printf(
        "Tela de jogo:\n"
        "Mediador: <--- O Jogador que nao da palpites, mas ganha pontos por cada dica nao lida.\n"
        "Jogador da vez: <--- O Jogador jogando agora. Ganha pontos se acertar ou por instrucoes.\n"
        "jogador(0) <--- O nome de um jogador e sua posicao no tabuleiro/placar.\n"
        "Dicas:  1 2 3 4 5 6 7 8 9 X X X X X X X X X X X <--- Dicas do cartao. Dicas ja usadas sao\n"
        "marcadas por um x.\n"
    );
    printf(
        "\n\nPalpite a qualquer hora: Se o jogador tiver uma ficha (se tiver, naquela rodada,\n"
        "pego uma dica de 'Palpite a qualquer hora'), ele pode digitar:\n"
        "!pqh nome\n"
        "Onde nome e o nome do jogador. Voce pode digitar o comando no seguinte momento:\n"
        "Jogador ... Qual e o seu palpite? [50]\n"
        "Isso nao remove a vez do jogador atual e ele pode fazer isso logo depois.\n"
        "E isso.\n"
    );
    flush();
    clear();
}