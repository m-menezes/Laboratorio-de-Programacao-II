/*  Nome: Marcelo Menezes
    Algoritmo: Trabalho 1
    Data: 10/08/16 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
struct Aluno {
    int matricula;
    float nota1;
    float nota2;
    string nome;
};


int main(void){
    int matricula, flag {0};
    float nota1, nota2;
    string nome;
    string busca;
    vector<Aluno> alunos;             // vetor de alunos

    ifstream entrada {"alunos.txt"};
    while( entrada >> matricula ) {        // le matricula primeiro parametro
        entrada >> nota1 >>nota2;       //le nota 1 e 2
        getline(entrada, nome);       // le o resto da linha (nome do aluno)
        alunos.push_back( Aluno{matricula, nota1, nota2, nome} ); // envia para a struct em ordem
    }
    cout << "Digite um nome: ";//Input nome
    getline(cin, busca);//recebe o nome completo com espaços
    for(Aluno& v: alunos){ //loop pelo vetor
        if (v.nome.find(busca) != string::npos){ //verifica se encontrou algo identico retorna string::npos se nao encontrou
            /*cout.precision(2);
            cout.setf(ios::fixed );*/ // Definir casas apos virgula
            cout << "Media: "<< ((v.nota1+v.nota2)/2) << " Nome:" << v.nome <<endl; //envia(tela) ao encontrar
            flag++;// incrementa na flag se encontrar algum
        }
    }
    if (flag == 0){ //se flag estiver 0 entao nada foi encontrado
        cout << "Não Encontrado" << endl; //mensagem e nova linha
    }
    return 0;
}
