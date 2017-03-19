#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

struct Posicao {
  int linha;
  int coluna;
};

struct Palavra {
    string palavra; // a palavra
    int contagem;        // palavras encontradas
    list<Posicao> lista; // lista com a posição de cada palavra
    Palavra *esq;
    Palavra *dir;
    //Função cortar palavras
    Palavra* split(Palavra *galho, string linha, int lin);

    //Função inserção de valores nos nodos
    Palavra* inserir(Palavra *galho, string valor, int lin, int col);

    //Função impressão em Ordem
    void emOrdem(Palavra* no);
};
