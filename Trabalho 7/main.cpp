#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <list>
#include <map>

using namespace std;

struct Vertice {
    string nome;
    list<string> adj;
};

void insereChave(string str, map<string, Vertice>& grafo){
    string nome;
    string chave;
    char * cstr = new char [str.length()+1];
    strcpy (cstr, str.c_str());
    //CSTR contem uma copia char da string str


    char * p = strtok (cstr," ");
    chave = string(p);
    while (p!=NULL){//por ser dois parametros apenas, o segundo é ate o final da linha.
        nome = string(p);
        p = strtok(NULL,"");
    }
    // Adicionando vertices
    grafo[chave] = Vertice();
    grafo[chave].nome = string{nome};
    delete[] cstr;
}

void insereVertice(string str, map<string, Vertice>& grafo){
    string chave1;
    string chave2;
    char * cstr = new char [str.length()+1];
    strcpy (cstr, str.c_str());
    //CSTR contem uma copia char da string str
    char * p = strtok (cstr," ");
    chave1 = string(p);
    while (p!=NULL){
        chave2 = string(p);
        p = strtok(NULL," ");
    }
      // Cria vertice SM <-> POA com a lista
    grafo[chave1].adj.push_back(chave2);
    grafo[chave2].adj.push_back(chave1);
    delete[] cstr;
}

void leArquivo(const char* nome, map<string, Vertice>& grafo){
    string str;
    int linha = 0;
    int param1 = 0;


    ifstream entrada {nome}; // abre arquivo
    if(entrada.is_open() == false){ //verificação de arquivo abriu ou não
        cout << "Nao foi possivel abrir arquivo!" << endl;
        exit(EXIT_FAILURE);
    }
    while(entrada.eof() == false){
        linha++;
        getline(entrada, str);
        char * cstr = new char [str.length()+1];
        strcpy (cstr, str.c_str());
        //CSTR contem uma copia char da string str

        if(linha == 1){
            char * p = strtok (cstr," ");
            param1 = atoi(p);           //recebimento parametro 1
            while (p!=NULL){
                p = strtok(NULL," ");
            }
        }
        if(linha>1 && linha < param1+2)
            insereChave(str, grafo);
        if(linha>param1+1)
            insereVertice(str, grafo);
        delete[] cstr;
    }
}

void imprimir(map<string, Vertice>& grafo){
        for (auto& x: grafo){
        cout << x.first << " -> ";
        //cout << x.second.nome << "\t";
        for(auto& a: x.second.adj){
            cout << a << " ";
        }
        cout << endl;
    }
}


int main(int argc, char *argv){
    // Definicao do grafo: string -> Vertice
    map<string, Vertice> grafo;

    //Recebimento dados arquivo
    leArquivo("grafo.txt", grafo);
    //Impressão dos dados
    imprimir(grafo);
    //Remove todos elementos do grafo
    //Removes all elements from the map container (which are destroyed), leaving the container with a size of 0. >> CPLUSPLUS
    grafo.clear();

    return 0;
}
