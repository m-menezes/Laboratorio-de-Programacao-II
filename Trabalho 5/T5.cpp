#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

void printErro(void){
    cout << "Errado" << endl;
}

void printAcerto(void){
    cout << "Certo" << endl;
}

int main(int argc, char* argv[]){
    string aux;
    stack<string> myStack;

    ifstream entrada {argv[1]}; /// abre arquivo
    if(entrada.is_open() == false){ ///verificação de arquivo abriu ou não
        cout << "Nao foi possivel abrir arquivo!" << endl;
        exit(-1);
    }
    while(entrada >> aux){
        if (aux.compare("program") == 0){
            myStack.push(aux);
        }
        else if (aux.compare("begin") == 0){
            myStack.push(aux);
        }
        else if (aux.compare("repeat") == 0){
            myStack.push(aux);
        }
        else if (aux.compare("case") == 0){
            myStack.push(aux);
        }
        else if (aux.compare("of") == 0){
            myStack.push(aux);
        }
        else if (aux.compare("else") == 0){ // se achar um else necessita achar um possuir no top um of e apos um case
            if(myStack.top() == "of"){
                myStack.pop();
                if(myStack.top() == "case"){
                    myStack.pop();
                }
                else{
                    printErro();
                    exit(0);
                }
            }
            else if(myStack.top() != "of"){
                printErro();
                exit(0);
            }
        }
        else if (aux.compare("until") == 0){ // se achar um until necessita ter um repeat no top
            if(myStack.top() != "repeat"){
                printErro();
                exit(0);
            }
            else if(myStack.top() == "repeat"){
                myStack.pop();
            }
        }
        else if (aux.compare("end") == 0 || aux.compare("end;")== 0 || aux.compare("end.") == 0){ // se achar um end retira um do top
            myStack.pop();
        }
    }
    if(myStack.size() != 1){///verifica se o ultimo elemento na stack é o nome do programa (program nome)
        printErro();
        exit(0);
    }
    else if(myStack.size() == 1){
        if (myStack.top() != "program"){
            printErro();
            exit(0);
        }
        else if (myStack.top() == "program"){
            myStack.pop();
            printAcerto();
        }
    }
    exit(0);
}
