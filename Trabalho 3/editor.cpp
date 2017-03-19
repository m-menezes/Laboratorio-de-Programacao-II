// editor.cpp
// Arquivo com funções da estrutura Editor
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
#include <string>


#include "editor.hpp"
#include "Tela.hpp"

// Utiliza as funções de tela
using namespace tela;
using namespace std;

void Editor::inicia(void)
{
	// esta função está pronta
	tela.inicia(800, 600, "Editor de texto");
	lin1 = 0;
	col1 = 0;
	lin2 = 0;
	col2 = 0;
	colcur = 0;
	lincur = 0;

	// apenas calcula o tamanho de uma letra em pixels
	const char* texto{ "A" };
	fonte = tela.tamanho_texto(texto);
}

void Editor::destroi(void) ///verificar
{
	/*while(linhas.empty()!= true){
        delete[] linhas[linhas.size()-1];
	}*/
	// TODO terminar
	tela.finaliza();
}

void Editor::desenha(void)
{
	// TODO terminar
	Cor preto = { 0.0, 0.0, 0.0 };
	Ponto pt;

	// primeiro, limpamos a tela
	tela.limpa();
	// cor do texto é preta
	tela.cor(preto);
	for (auto i = 0; i < linhas.size(); i++) {
		// calcula posicao da nova linha
		pt.x = 1;
		pt.y = i*fonte.alt + 1;

		/* muda cor e desenha linha */

		tela.texto(pt, linhas[i].c_str());
	}

	// chama função para desenhar cursos no texto
	desenha_cursor();
}

void Editor::atualiza(void)
{
	// TODO terminar
	desenha();
	tela.mostra();
	tela.espera(30);
}

void Editor::desenha_cursor(void)
{
	// TODO terminar
	Cor preto = { 0.0, 0.0, 0.0 };
	Ponto pt1, pt2;

	/* posicao x (horizontal) do cursor */
	pt1.x = fonte.larg*colcur + 1;
	/* posicao y (vertical) do cursor */
	pt1.y = lincur * fonte.alt;
	pt2.x = pt1.x;
	pt2.y = pt1.y + fonte.alt;
	tela.cor(preto);
	tela.linha(pt1, pt2);
}

bool Editor::processa_comandos(void)
{
	int tecla = tela.tecla();
	int modificador = tela.tecla_modif();
	/* apertou CRTL + Q ? */
	if (tecla == ALLEGRO_KEY_Q && (modificador & ALLEGRO_KEYMOD_CTRL)) {
		cout << "CTRL+Q SAIR\n";
		return false;
	}
	if (tecla == ALLEGRO_KEY_S && (modificador & ALLEGRO_KEYMOD_CTRL)) {
		salvar();
		// muda estado na variável para não editar
		estado = Estado::nada;
	}
	if (tecla == ALLEGRO_KEY_E && (modificador & ALLEGRO_KEYMOD_CTRL)) {
		cout << "CTRL+E EDITAR\n";
		// muda estado na variável para editando
		estado = Estado::editando;
		return true;
	}
    if (estado == Estado::editando){
        if (tecla == ALLEGRO_KEY_J && (modificador & ALLEGRO_KEYMOD_CTRL)) {
            gruda_linha();
            cout << "CTRL+J GRUDAR (JUNTAR) LINHAS\n";
            // muda estado na variável para editando
            return true;
        }
        if (tecla == ALLEGRO_KEY_N && (modificador & ALLEGRO_KEYMOD_CTRL)) {
            quebra_linha();
            cout << "CTRL+N QUEBRAR LINHAS\n";
            // muda estado na variável para editando
            return true;
        }
	}

	/* teclas direcionais
	ALLEGRO_KEY_LEFT
	ALLEGRO_KEY_RIGHT
	ALLEGRO_KEY_UP
	ALLEGRO_KEY_DOWN
	*/
	if (tecla == ALLEGRO_KEY_LEFT)
		move_esq();
	if (tecla == ALLEGRO_KEY_RIGHT)
		move_dir();
	if (tecla == ALLEGRO_KEY_UP)
		move_cima();
	if (tecla == ALLEGRO_KEY_DOWN)
		move_baixo();

	if ((tecla >= ALLEGRO_KEY_A) && (tecla <= ALLEGRO_KEY_Z) || (tecla == ALLEGRO_KEY_BACKSPACE)){
		if (estado == Estado::editando)
		    if(tecla == ALLEGRO_KEY_BACKSPACE) {
                remove_char();
            }
            else
			insere_char(static_cast<char>(tecla + 96));
    }
	return true;
}


void Editor::le_arquivo(const char* nome){
	string linha; /// recebe linha para depois copiar para struct
	ifstream entrada{ nome }; /// abre arquivo com nome passado por parametro
	if (entrada.is_open() == false) { ///verificação de arquivo abriu ou não
		cout << "Nao foi possivel abrir arquivo!" << endl;
		exit(-1);
	}
	while (entrada.eof() == false) {
		getline(entrada, linha); ///copia linha inteira do arquivo para variavel "linha"
		linhas.push_back(linha); ///enviar conteudo linha para vetorna sua ultima posição
	}
	entrada.close(); ///fechar arquivo
}

void Editor::move_cima(void)
{
    if (lin1 > 0 ){
        lin1 --;
        lin2 --;
    }
	lincur--;
}

void Editor::move_baixo(void)
{
	if(lin2 < 20){
        lin2 ++;
        lin1 ++;
	}
	lincur++;
}

void Editor::move_esq(void)
{
	if(col2 < 50){
        col2 ++;
        col1 ++;
	}
	colcur--;
}

void Editor::move_dir(void)
{
    if (col1 > 0 ){
        col1 --;
        col2 --;
    }
	colcur++;
}

void Editor::insere_char(const char c){

	if (lincur > linhas.size()){
        linhas.resize(linhas.size() - lincur);
        if(colcur != 0){
            string& linha = ref(linhas[lincur]);
            linha.insert(0, colcur-1, ALLEGRO_KEY_SPACE);
        }
        return;
	}
	string& linha = ref(linhas[lincur]);
	linha.insert(colcur, 1, c);
    move_dir();
}

void Editor::remove_char(void){
    if(colcur == 0){
        return;
    }
	string& linha = ref(linhas[lincur]);
	linha.erase(colcur-1,1);
    move_esq();
}

void Editor::gruda_linha(void){
	string& linha_ant = ref(linhas[lincur-1]);
    string& linha_atu = ref(linhas[lincur]);
    linha_ant.append(linha_atu);
    linhas.erase(lincur);
    }

void Editor::quebra_linha(void){
    string& linha = ref(linhas[lincur]);
    string nova_linha;
    nova_linha.copy(linhas, colcur, linha.size() - colcur);
    linhas.insert(lincur, nova_linha);
}

void Editor::salvar(void){
    cout << "CTRL+S SALVAR e PARAR DE EDITAR\n";
    ofstream entrada{"entrada.txt"};	    ///open arquivo apenas para saida
    for (auto x = 0; x<linhas.size();x++)	///loop pelo vetor
        entrada << linhas[x] << endl;	    ///passa vetor para arquivo
    entrada.close();                        ///fechar arquivo
}
