#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

#include "arvore.hpp"

using namespace std;
Palavra* Palavra::split(Palavra *galho, string linha, int lin){ // corte palavra stream
    int col=0;
    string buffer; // cria um buffer para salvar a palavra temporariamente
    stringstream ss(linha); // insere a linha na stream

    while (ss >> buffer)
        col += buffer.size();
        galho = galho->inserir(galho, buffer, lin, col);
    return galho;
}

Palavra* Palavra::inserir(Palavra *galho, string str, int lin, int col){ //Valor possui a linha inteira Galho o no* da arvore


    if(galho == NULL){ // Verifica se a árvore está vazia
        Palavra *novo = new(Palavra);
        Posicao *novoPos = new (Posicao);

        /* RECEBE POSIÇÃO */
        novoPos->linha = lin;
        novoPos->coluna = col;

        /* ENVIO PARA ARVORE*/
        novo->palavra = str;
        novo->contagem = 1;
        novo->esq=NULL;
        novo->dir=NULL;
        novo->lista.push_back(novoPos);
        galho = novo;
        return galho;
    }
    /*Define para qual lado irá a palavra comparando com o pai*/
    else if(str > galho->palavra){
        galho->dir = inserir(galho->dir, str, lin, col);
        return galho;
    }
    else if (str < galho->palavra){
        galho->esq = inserir(galho->esq, str, lin, col);
        return galho;
    }
    else if (str == galho->palavra){
        Posicao *novoPos = new (Posicao);

        /* RECEBE POSIÇÃO */
        novoPos->linha = lin;
        novoPos->coluna = col;

        /* ENVIO PARA ARVORE*/
        galho->lista.push_back(novoPos);
        galho->contagem +=1;
        return galho;
    }
}

void Palavra::emOrdem(Palavra* no){
    if(no != NULL){
        emOrdem(no->esq);
        cout << no->palavra <<" ";
        cout << no->contagem << " ";
        cout << no->lista.linha << " ";
        cout << no->lista.coluna << endl;
        emOrdem(no->dir);
    }
}
