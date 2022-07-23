# Brainstorming

Tabuleiro, interface para inserir novos cartões, cartões, sistema de resposta, multiplayer, pontuação.

# Peças

## Tabuleiro
### Real
134 casas comuns, 20 casas centrais (dicas), 4 marcações de tipo.
?: O jogador que chegar a uma dessas casas - excluindo através de instruções - recebe uma cartela bonus

### Projeto
134 casas comuns: guarda a posição no struct player, MAX 134, MIN 1.
20 casas centrais: # de dicas armazenadas em um vetor.
4 marcações de tipo: categoria armazenada como string, exibida no topo. 
?: Casas especiais são armazenadas em um vetor.


## Cartões
### Real
Possui objeto, categoria e 20 dicas, algumas podem ser instruções

### Projeto
São armazenadas em um arquivo. Formato:
'obj'n_objeto_categoria
n_dica
n_dica
...

Formatação instrução:
n_!pv === perca a vez === 3_!pv
n_!ax === avance x casas === 10_!a3
n_!vx === volte x casas === 13_!v3
n_!pqh === palpite a qualquer hora === 18_!pqh
n_!jax === escolha um jogador para avançar x casas === 19_!ja2
n_!jvx === escolha um jogador para voltar x casas === 20_!jv2


### Interface para inserir novos cartões
Objeto do cartão [50]: 
Categoria [pessoa/lugar/coisa/ano]: 

ATENÇÃO: 
Formato|                   Ação                    | Exemplo
!pv   === perca a vez                             === !pv
!ax   === avance x casas                          === !a3
!vx   === volte x casas                           === !v3
!pqh  === palpite a qualquer hora                 === !pqh
!jax  === escolha um jogador para avançar x casas === !ja2
!jvx  === escolha um jogador para voltar x casas  === !jv2

Dicas [150 por dica]:
1: 
2: 
3: 
4: 
5: 
...

Salvar cartão? [S/n]


## Sistema de resposta
Ao receber a dica, o jogador pode escrever uma resposta.
Se ela estiver correta, ele recebe a pontuação e o randomizer pega uma nova carta.
Se não, passa ao próximo jogador
Se o jogador não digitar, passa ao próximo jogador
Se um jogador tem uma ficha azul, ele pode digitar !pqh nome a qualquer momento de prompt

## Multiplayer
No começo do jogo, pede-se o número de jogadores e seus nomes em ordem de jogo.
Struct jogador:

odem, nome, casa, ficha_pqh, mediador


## Pontuação

O mediador da rodada ganha pontos por cada dica lida.
O acertador ganha pontos por cada dica não lida.



## Visualizações

//////////////////////////////////cls

Menu inicial...

1 Jogar
2 Menu de cartões
3 Sair
`1`

//////////////////////////////////cls

Quantos jogadores vão participar? [1-6] `3`

###Primeiro jogador### \\ordem 1, casa 1, ficha 0, mediador 1
Nome: `Dione`

###Segundo jogador### \\ordem 2, casa 1, ficha 0, mediador 0
Nome: `Leo`

###Terceiro jogador### \\ordem 3, casa 1, ficha 0, mediador 0
Nome: `Valéria`

O jogo está prestes a começar...

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Leo(1)
Próximo jogador: Valéria(1)

Eu sou... um lugar!
Dicas: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Pronto, jogador Leo... Que dica você quer? `2`
Atenção, mesa... Não tenho satélites.

Jogador Leo, qual é seu palpite? ` `
...

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Valéria(1)
Próximo jogador: Leo(1)

Eu sou... um lugar!
Dicas: 1 X 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Pronto, jogador Valéria... Que dica você quer? `14`
Atenção, mesa... Jogador Valéria avança 3 espaços

Jogador Valéria, qual é seu palpite? `Plutão`
... Incorreto!

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Leo(1)
Próximo jogador: Valéria(4)

Eu sou... um lugar!
Dicas: 1 X 3 4 5 6 7 8 9 10 11 12 13 X 15 16 17 18 19 20

Pronto, jogador Leo... Que dica você quer? `4`
Atenção, mesa... Jogador Leo perde sua vez

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Valéria(4)
Próximo jogador: Leo(1)

Eu sou... um lugar!
Dicas: 1 X 3 X 5 6 7 8 9 10 11 12 13 X 15 16 17 18 19 20

Pronto, jogador Valéria... Que dica você quer? `17`
Atenção, mesa... Tenho várias crateras.

Jogador Valéria, qual é seu palpite? `Lua`
... Incorreto!

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Leo(1)
Próximo jogador: Valéria(4)

Eu sou... um lugar!
Dicas: 1 X 3 X 5 6 7 8 9 10 11 12 13 X 15 16 X 18 19 20

Pronto, jogador Leo... Que dica você quer? `10`
Atenção, mesa... Jogador Leo ganha um palpite a qualquer hora.

Jogador Leo, qual é seu palpite? `Sol`
... Incorreto!

//////////////////////////////////cls

Mediador: Dione(1)
Jogador da vez: Valéria(4)
Próximo jogador: Leo(1) O

Eu sou... um lugar!
Dicas: 1 X 3 X 5 6 7 8 9 X 11 12 13 X 15 16 X 18 19 20

Pronto, jogador Valéria... Que dica você quer? `1`
Atenção, mesa... Fico a 108 milhões de quilômetros do Sol.

Jogador Valéria, qual é seu palpite? `México`
... Incorreto `!pqh Leo`
Jogador Leo, qual é seu palpite? `Vênus`
... Correto!

//////////////////////////////////cls

Atenção à contagem de pontos...
Foram lidas 6 dicas...
Mediador Dione avança 6 casas...
Jogador Leo avança 14 casas...

Nova pontuação:
Leo(15)
Dione(7)
Valéria(4)

O próximo mediador é... Leo!

[...]

//////////////////////////////////cls

Atenção à contagem de pontos...
Foram lidas 13 dicas...
Mediador Leo avança 13 casas...
Jogador Valéria avança 7 casas...

Nova pontuação:
Leo(28)
Dione(7)
Valéria(11)

O próximo mediador é... Valéria!
... Mas espere! O Jogador Valéria está sobre uma casa especial!

//////////////////////////////////cls

Cartela bônus: Jogador Valéria

Eu sou... Uma pessoa!
Dicas: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Dicas restantes: 5

Pronto, jogador Valéria... Que dica você quer? `6`
Atenção, jogador... Morri em 1980.

Jogador Valéria, qual é seu palpite? ` `
...

//////////////////////////////////cls

Cartela bônus: Jogador Valéria
Eu sou... Uma pessoa!
Dicas: 1 2 3 4 5 X 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Dicas restantes: 4

Pronto, jogador Valéria... Que dica você quer? `13`
Atenção, jogador... Fui assassinado por um fã.

Jogador Valéria, qual é seu palpite? `John Lennon`
... Correto!

//////////////////////////////////cls

Atenção à contagem de pontos...
Foram lidas 2 dicas...
Jogador Valéria avança 8 casas...

Nova pontuação:
Leo(28)
Dione(7)
Valéria(19)

O próximo mediador é... Valéria!

[...]

//////////////////////////////////cls

Atenção à contagem de pontos...
Foram lidas 3 dicas...
Mediador Dione avança 3 casas...
Jogador Leo avança 17 casas...

Nova pontuação:
Leo(134)
Dione(133)
Valéria(130)

... Temos um vencedor!

//////////////////////////////////cls

Parabéns, jogador Leo!

Posições finais:

Leo(134)
Dione(133)
Valéria (130)

//////////////////////////////////cls

Menu inicial...

1 Jogar
2 Menu de cartões
3 Sair
`2`

//////////////////////////////////cls

Menu de cartões...

1 Cadastrar cartão
2 Excluir cartão
3 Número de cartões
4 Voltar

//////////////////////////////////cls

Objeto do cartão [50]: LAB3
Categoria [pessoa/lugar/coisa/ano]: Lugar

ATENÇÃO: 

Formato|                   Ação                    | Exemplo
!pv   === perca a vez                             === !pv
!ax   === avance x casas                          === !a3
!vx   === volte x casas                           === !v3
!pqh  === palpite a qualquer hora                 === !pqh
!jax  === escolha um jogador para avançar x casas === 19_!ja2
!jvx  === escolha um jogador para voltar x casas  === 20_!jv2

Dicas [150 por dica]:
1: !pv
2: Eu sou parte de uma universidade.
3: !a4
...

//////////////////////////////////cls

Eu sou LAB3
Diga aos jogadores que eu sou um lugar.
1: Perca sua vez.
2: Eu sou parte de uma universidade.
3: Avance 4 casas.
...

Salvar cartão? [S/n] `S`

//////////////////////////////////cls

Menu inicial...

1 Jogar
2 Menu de cartões
3 Sair
`3`

Até mais!