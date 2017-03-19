// cobra.hpp
// Arquivo com declaração da estrutura Cobra
//
// The MIT License (MIT)
//
// Copyright (c) 2016 João V. Lima, UFSM
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// inclui este arquivo apenas uma vez
#pragma once

#include <list>
#include <string>
#include <memory>
#include <chrono>

#include "Tela.hpp"
#include "geom.hpp"

enum class Direcao { cima, direita, baixo, esquerda };

// pedaço do jogo
struct Pedaco {
  geom::Ponto p;      // ponto do pedaço
  Direcao dir;        // direção desse pedaço
  tela::Cor cor;      // cor do pedaço
};
struct p_dobra{
    float x;
    float y;
    Direcao dir;
};
struct Cobra {
  std::list<Pedaco*> pedacos;  // os pedaços da cobra
  geom::Tamanho tam;           // tamanho de um pedaço
  Direcao dir;                 // direção da cobra
  std::list<p_dobra*> curva;
  // parte de cronometragem do programa
  std::chrono::microseconds t_mov;     // tempo para movimentar pedaços
  std::chrono::microseconds t_insere;  // tempo para inserir pedaços
  // última vez que uma inserção foi feita
  std::chrono::time_point<std::chrono::system_clock> crono_insere;
  // última vez que uma movimentação foi feita
  std::chrono::time_point<std::chrono::system_clock> crono_mov;

  tela::Tela tela;      // tela do jogo
  Tamanho fonte;        // tamanho (pixels) de uma letra da fonte usada

  // Abaixo estão as funções básicas do jogo Cobra
  // Se achar necessário, pode-se inserir outras funções.

  // Inicia a cobra com um pedaço na coordenada (x,y),
  // e direção inicial direita.
  void inicia(const int x, const int y);

  // destroi o jogo
  void destroi(void);

  // Atualiza o  jogo, sendo:
  // 1 - movimenta os pedaços da cobra
  // 2 - insere novo pedaço (se preciso)
  // 3 - mostra tela
  void atualiza(void);

  // desenha os objetos da tela
  void desenha(void);

  // Testa o cronometro 'crono_insere' e insere
  // um novo pedaço na cobra.
  void insere(void);

  // Movimenta os pedaços da cobra, de acordo com
  // a direção de cada pedaço.
  void movimenta(void);

  ///CRIADAS POR MIM
  //Salva o ponto de dobra em uma fila
  void salva_ponto(Direcao dir);
  //Verifica se precisa modificar a direção dos nós
  void troca_direcao(void);
  ///ATÉ AQUI

  // Faz com que o início da cobra
  void dobra(Direcao dir);

  // Testa se o tempo para movimentar pedaços foi atingido.
  // Com o tempo, deve aumentar a velocidade.
  bool tempo_movimenta(void);

  // Lê comandos do teclado e executa funções de acordo. Possui
  // exemplos de comandos esperados. Implementar uma função por
  // comando.
  // Retorna 'true' para continuar execução.
  bool processa_comandos(void);
};
