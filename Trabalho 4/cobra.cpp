// editor.cpp
// Arquivo com funções da estrutura Cobra
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

#include <iostream>
#include <fstream>
#include <functional>
#include <memory>
#include <chrono>
#include <list>     /// LISTA PONTO DE CURVA
#include <time.h>   /// TIME SRAND
#include <random>   /// RAND
#include <cstdlib>  /// UTILIZADO NO MAX_RAND

#include "cobra.hpp"
#include "Tela.hpp"
#define TAM 10
#define TELA_LARGURA 600
#define TELA_ALTURA 400

// Utiliza as funções de tela
using namespace tela;

// estruturas geométicas
using namespace geom;

void Cobra::inicia(const int x, const int y){
    // esta função está pronta (pode ser alterada)
    tela.inicia(TELA_LARGURA, TELA_ALTURA, "Jogo da Cobra");

    //Seed Random
    srand(time(NULL));

    // apenas calcula o tamanho de uma letra em pixels
    const char* texto { "A" } ;
    fonte = tela.tamanho_texto(texto);

    // tamanho de um pedaço
    tam.larg = TAM;
    tam.alt = TAM;

    Pedaco* pcs = new Pedaco;
    pcs->p.x = x;
    pcs->p.y = y;
    pcs->cor = {0.0, 0.0, 0.0}; // inicia com cor preta
    pcs->dir = Direcao::direita;
    pedacos.push_front(pcs);
    // direção inicial
    dir = Direcao::direita;

    // inicia o tempo
    crono_mov = std::chrono::system_clock::now();
    crono_insere = std::chrono::system_clock::now();

    // calcula tempo dado uma frequencia (Hz): 4x por segundo
    t_mov = std::chrono::microseconds(int(100000));
    // tempo para inserção de novos pedaços
    t_insere = std::chrono::milliseconds(500);
}

void Cobra::destroi(void){
    std::cout << "PONTUACAO FINAL:" << pedacos.size() << std::endl;//mostra no terminal(code::blocks)
    for(auto itr1 = begin(pedacos); itr1 != end(pedacos); ++itr1){
        auto* pcs1 = *itr1;
        delete pcs1;
    }
    for(auto itr2 = begin(curva); itr2 != end(curva); ++itr2){
        auto* pcs2 = *itr2;
        delete pcs2;
    }
    pedacos.clear();
    curva.clear();
    tela.finaliza();
}

void Cobra::desenha(void){
  // Função pronta
  // primeiro, limpamos a tela
  tela.limpa();

  // Laço for do c++11 sobre uma lista
  for(auto psc : pedacos){
    Retangulo r;
    r.pos = psc->p;
    r.tam = tam;
    tela.cor(psc->cor);
    tela.retangulo(r);
  }
}

void Cobra::atualiza(void){
  // Função pronta (se quiser, alterar)
  movimenta();
  insere();
  desenha();
  tela.mostra();
  tela.espera(30);
}

void Cobra::insere(void){
  auto t_agora = std::chrono::system_clock::now();

  // conta quanto tempo passou e converte para milisegundos
  auto t_passado = std::chrono::duration_cast<std::chrono::milliseconds>(t_agora - crono_insere);

  if(t_passado > t_insere) {
    //Gera 3 numeros randomicos
    auto r = ((float)(rand())/RAND_MAX);
    auto g = ((float)(rand())/RAND_MAX);
    auto b = ((float)(rand())/RAND_MAX);


    auto psc = pedacos.back();
    Pedaco* novo = new Pedaco;
    novo->dir = dir;
    novo->cor = {r,g,b};

    switch (dir){
        case (Direcao::baixo): {
            novo->p.x = psc->p.x;
            novo->p.y = psc->p.y + TAM;
            break;
        }
        case (Direcao::cima): {
            novo->p.x = psc->p.x;
            novo->p.y = psc->p.y - TAM;
            break;
        }
        case (Direcao::direita): {
            novo->p.x = psc->p.x + TAM;
            novo->p.y = psc->p.y;
            break;
        }
        case (Direcao::esquerda): {
            novo->p.x = psc->p.x - TAM;
            novo->p.y = psc->p.y;
            break;
        }

    }
    pedacos.push_back(novo);
    crono_insere = std::chrono::system_clock::now();
  }
}

void Cobra::salva_ponto(Direcao _dir){
    auto psc = pedacos.back();//primeiro pedaço da cobra para salvar o ponto(X,Y) e a direção
    auto novo = new p_dobra; // cria um novo no para fila
    novo->x = psc->p.x; // copia o ponto X
    novo->y = psc->p.y; // copia o ponto Y
    novo->dir = _dir;   // salva a direção apos o ponto
    curva.push_back(novo);//adiciona ao fim da fila
}

void Cobra::dobra(Direcao _dir){
    salva_ponto(_dir);
    auto primeiro = pedacos.back();
    primeiro->dir = _dir;//muda a posição do primeiro
    dir = _dir;
}

void Cobra::troca_direcao(void){//DON'T TOUCH ###MACUMBA###
            if (!curva.empty()){//verifica se tem ponto salvo na lista
            for(auto psc : pedacos){
                for(auto ponto_dobra : curva){
                    if(psc->p.x == ponto_dobra->x && psc->p.y == ponto_dobra->y){// se o proximo ponto passar muda a direção
                        psc->dir = ponto_dobra->dir; //muda direção se o ponto for igual
                    }
                }
            }
            auto last = pedacos.front(); // ultimo ponto da cobra
            auto first = curva.front(); // primeiro ponto da curva
            if(last->p.x == first->x && last->p.y == first->y){// se o ultimo estiver no ponto exclui o primeiro da list
                        delete first;
                        curva.pop_front(); //deleta o primeiro apos o ultimo passar
            }
        }
}

void Cobra::movimenta(void){
    if( tempo_movimenta() == false )
        return;
    else
        troca_direcao();
        for(auto psc : pedacos){ ///SWITCH CASE UTILIZA MAIS LINHAS
            if(psc->dir == Direcao::baixo){
                psc->p.y += TAM;
            }
            if(psc->dir == Direcao::cima){
                psc->p.y -= TAM;
            }
            if(psc->dir == Direcao::direita){
                psc->p.x += TAM;
            }
            if(psc->dir == Direcao::esquerda){
                psc->p.x -= TAM;
            }
        }
}

bool Cobra::tempo_movimenta(void){
  auto crono_agora = std::chrono::system_clock::now();

  // conta quanto tempo passou e converte para milisegundos
  auto t_passado = std::chrono::duration_cast<std::chrono::milliseconds>(crono_agora - crono_mov);

  // se passou meio segundo ?
  if(t_passado > t_mov) {
    crono_mov = std::chrono::system_clock::now();
    return true;
  }
  return false;
}

bool Cobra::processa_comandos(void){
  // Função pronta.
  int tecla = tela.tecla();
  int modificador = tela.tecla_modif();
  /* apertou CRTL + Q ? */
  if( tecla == ALLEGRO_KEY_Q ){
    std::cout << "SAIR\n";
    return false;
  }
  ///COLISAO EXTERNA
    auto psc = pedacos.back(); // SE BATER NA BEIRADA MORRE
    if(psc->p.y > TELA_ALTURA-10 || psc->p.y < -1 || psc->p.x > TELA_LARGURA-10 || psc->p.x < -1){
        std::cout << "GAME OVER" << std::endl;
        return false;
    }
  /* teclas direcionais
     ALLEGRO_KEY_LEFT
     ALLEGRO_KEY_RIGHT
     ALLEGRO_KEY_UP
     ALLEGRO_KEY_DOWN
  */
  if( tecla == ALLEGRO_KEY_LEFT && (dir != Direcao::direita))// NAO VOLTA SOBRE SI MESMA
    dobra(Direcao::esquerda);
  else if( tecla == ALLEGRO_KEY_RIGHT && (dir != Direcao::esquerda))
    dobra(Direcao::direita);
  else if( tecla == ALLEGRO_KEY_UP && (dir != Direcao::baixo))
    dobra(Direcao::cima);
  else if( tecla == ALLEGRO_KEY_DOWN && (dir != Direcao::cima))
    dobra(Direcao::baixo);

  return true;
}
