#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Editor {
    char **linhas;  // as linhas do texto
    char *nome;     // nome do arquivo de entrada
    int nlinhas;    // total de linhas do texto
    int lin1;       // linha do texto na 1a linha da tela
    int lin2;       // linha do texto na última linha da tela
    //int col1;       // coluna do texto na 1a coluna da tela
    //int col2;       // coluna do texto na última coluna da tela

    /// inicia o editor
    void inicia(void){
        nome = nullptr;
        linhas = nullptr;
        nlinhas = 0;
        lin1 = lin2 = 0;
        //col1 = col2 = 0;
    }
    ///conta numero de linhas no arquivo e cria vetor vertical
    void contagem(const char* nome){
        int tam = 0;
        string linha;
        ifstream entrada {nome}; // abre arquivo
        if(entrada.is_open() == false){ //verificação de arquivo abriu ou não
            cout << "Nao foi possivel abrir arquivo!" << endl;
            exit(-1);
        }
        while(entrada.eof() == false){
            getline(entrada, linha);///pega linha ver se funciona sem enviar para ninguem
            tam ++; /// conta linhas
        }
        entrada.close(); //fechar arquivo
        linhas = new char*[tam]; // cria vetor vertical da matriz do tamanho das linhas
    }

    /// destroi o editor
    void destroi(void){
        for(auto i = 0; i < nlinhas; i++)
            delete[] linhas[i];
        delete[] linhas;
    }

    /// Macro limpar tela
    void limpatela(void){
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            system("clear");
        #endif

        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #endif
    }

    /// desenha o texto na tela
    void desenha(void){
        limpatela();

        for(auto l= lin1; l < lin2; l++){
            cout << linhas[l] << endl;
        }
    }

    /// le um arquivo 'nome' e armazena na struct
    void le_arquivo(const char* nome){
        string linha; // recebe linha para depois copiar para struct
        ifstream entrada {nome}; // abre arquivo
        if(entrada.is_open() == false){ //verificação de arquivo abriu ou não
            cout << "Nao foi possivel abrir arquivo!" << endl;
            exit(-1);
        }
        while(entrada.eof() == false){
            getline(entrada, linha); // copia linha inteira do arquivo para variavel "linha"
            linhas[nlinhas] = new char[linha.length()+1]; //cria um vetor de char de tamanho da frase
            linha.copy(linhas[nlinhas], linha.length(), 0); // de onde vem (onde vai, tamanho e inicia em que posição)
            linhas[nlinhas][linha.length()] = '\0'; //adiciona /0 ao fim para mostrar fim de frase
            nlinhas++;
        }
    }

    /// move o texto uma linha para cima
    void move_cima(void){
        if(lin1 > 0){
            lin1 --;
            lin2 --;
        }
    }

    /// move o texto uma linha para baixo
    void move_baixo(void){
        if(lin2 < nlinhas){
            lin2 ++;
            lin1 ++;
        }
    }
};

/// inclui funções se for linux
#if defined(__linux__)
    #include <termios.h>
    #include <unistd.h>
    void termios_off(void){
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~ICANON;
        t.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }

    void termios_on(void){
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag |= ICANON;
        t.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
#endif

int main(void){
    char c;
    Editor ed;

    ed.inicia();
    ed.contagem("entrada.txt");
    ed.le_arquivo("entrada.txt");
    if (ed.nlinhas > 20){
        ed.lin2 = 20;
    }
    else
        ed.lin2 = ed.nlinhas; // define tamanho da lin2 igual a nlinhas se for menor que 20
    #if defined(__linux__)
        termios_off();
    #endif
    while(true){
        ed.desenha();
        cout << endl << " W = Subir\tS = Descer\tQ = Sair" << endl;
        c = getchar();
        if(c == 'q' || c == 'Q')
            break;
        if(c == 'w' || c == 'W')
            ed.move_cima();
        if(c == 's' || c == 'S')
            ed.move_baixo();
    }
    #if defined(__linux__)
        termios_on();
    #endif
    ed.destroi();
    return (0);
}
