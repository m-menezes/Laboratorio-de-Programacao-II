#include <iostream>
#include <fstream>
#include <string.h>
#include "arvore.hpp"

using namespace std;


main(int argc, char* argv[]){
    Palavra *ar=NULL;
    string linha;
    int lin = 0;

    ifstream entrada {argv[1]}; // abre arquivo
    if(entrada.is_open() == false){ //verifica��o de arquivo abriu ou n�o
        cout << "Nao foi possivel abrir arquivo!" << endl;
    }

    while(entrada.eof() == false){
        getline(entrada, linha);///pega linha ver se funciona sem enviar para ninguem
        lin += 1; /// salva quantidade de linhas do texto
        ar =ar->split(ar, linha, lin);
    }
     ar->emOrdem(ar);
}
