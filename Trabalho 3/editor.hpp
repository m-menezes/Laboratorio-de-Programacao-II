// editor.hpp
// Arquivo com declaração da estrutura Editor
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

#include <vector>
#include <string>

#include "Tela.hpp"
#include "geom.hpp"

// Estados de edição do Editor
enum class Estado { nada, editando };

struct Editor {
  char *nome;     // nome do arquivo de entrada
  std::vector<std::string> linhas;  // as linhas do texto
  int nlinhas;    // total de linhas do texto
  int lin1;       // linha do texto na 1a linha da tela 
  int col1;       // coluna do texto na 1a coluna da tela
  int lin2;       // linha do texto na última linha da tela
  int col2;       // coluna do texto na última coluna da tela
  int colcur;     // a atual coluna do cursor
  int lincur;     // a atual linha do cursor

  Estado estado;        // indica o estado do editor
  tela::Tela tela;      // tela do editor
  Tamanho fonte;  // tamanho (pixels) de uma letra da fonte usada

  // Abaixo estão as funções básicas do editor.
  // Se achar necessário, pode-se inserir outras funções. 

  // Inicia o editor.
  // O editor sempre inicia em estado de não edição.
  void inicia(void);

  // destroi o editor
  void destroi(void);

  // Desenha toda a tela. A primeira linha a ser desenhada é lin1. A
  // primeira coluna a ser desenhada em cada linha é col1. Deve ser
  // completada baseada no exemplo dado.
  // IMPORTANTE: cuidado com o desenho do cursor, pois caracteres tem
  // diferentes tamanhos em pixels.
  void desenha(void);

  // Atualiza a tela fazendo os passos seguintes:
  // - desenha a tela
  // - mostra a tela
  // - faz espera (para não ficar lento)
  void atualiza(void);

  // Desenha o cursor na tela, como se fosse uma linha
  void desenha_cursor(void);

  // Lê comandos do teclado e executa funções de acordo. Possui
  // exemplos de comandos esperados. Implementar uma função por
  // comando.
  // Retorna 'true' para continuar execução.
  bool processa_comandos(void);
 
  // Inicializa a estrutura com o conteúdo do arquivo
  // chamado nome.  Deve ler cada linha do arquivo, alocar memória
  // suficiente para essa linha (sem o '\n' final e com um '\0').
  // A função deve ainda inicializar os demais campos da estrutura.
  void le_arquivo(const char* _nome);

  // Salva conteúdo do texto no arquivo 'nome'
  void salvar(void);

  // Devem ser completadas nos exemplos dados.  Move a posição do
  // cursor na direção indicada pelo nome da função. Para a esquerda,
  // para cima e para baixo, não deve sair dos limites do texto. Para a
  // direita, não há limite. Editor pode estar em modo edição.
  void move_cima(void);
  void move_baixo(void);
  void move_dir(void);
  void move_esq(void);

  // Insere o caractere c na posição do cursor.  Caso a linha do
  // cursor seja mais curta que a posição do cursor, devem ser
  // inseridos espaços no final da linha, para que o caractere
  // inserido fique na posição correta.  Após a inserção, o cursor
  // deve ser movido uma coluna à direita (usar a função
  // acima).
  // Editor deve estar em modo edição.
  void insere_char(const char c);

  // Remove o caractere na posição do cursor no texto. Caso o cursor
  // esteja além do final da linha, a função não deve fazer nada. A
  // posição do cursor não deve ser alterada.
  // Editor deve estar em  modo edição.
  void remove_char(void);

  // Se o cursor não estiver na última linha do texto, anexa a linha
  // seguinte à do cursor ao final da linha do cursor, e remove a
  // linha abaixo do cursor da lista.
  // Editor não pode estar em modo edição.
  void gruda_linha(void);

  // Quebra a linha do cursor na posição do cursor. A linha com o
  // cursor terminará com o caractere logo antes do cursor, e a linha
  // seguinte conterá os caracteres a partir da posição do cursor.  Se
  // o cursor estiver além do final da linha, a linha do cursor
  // permanece inalterada e é inserida uma linha vazia após o cursor.
  // Editor não pode estar em modo edição.
  void quebra_linha(void);
};
