/*
Mariana Bissaro Weiss, 2281
Layla Victória Sousa Teles, 2426
livia oliveira santos, 2290
Maria Clara Freitas Soares, 712
Miguel Borges Magalhães, 978
*/

#include <iostream>
#include <locale.h>
//biblioteca locale.h permite usar os caracteres da lingua portuguesa
using namespace std;

void inserirItem(){
	cout << "Funcionalidade em construção" << endl;
}

void cadastrarSimilaridades(){
	cout << "Funcionalidade em construção" << endl;
}

void buscarItens(){
	cout << "Funcionalidade em construção" << endl;
}

void verificarItem(){
	cout << "Funcionalidade em construção" << endl;
}

void listarItemA(){ //listar item em ordem alfabética
	 cout << "Funcionalidade em construção" << endl;
}

void listarItemR(){ //listar itens em ordem decrescente de raridade
	cout << "Funcionalidade em construção" << endl;
}

void contarItens(){
	cout << "Funcionalidade em construção" << endl;
}

void remover(){ //remover itens menos raros
	cout << "Funcionalidade em construção" << endl;
}

int main () {

setlocale(LC_ALL, "Portuguese");
//função da biblioteca locale

	int opcao;
	do{
        cout << "================== BOLSA DEVORADORA =================" << endl;
        cout << "| 1. Inserir item                                   |" << endl;
        cout << "| 2. Cadastrar similaridade entre itens;            |" << endl;
        cout << "| 3. Buscar itens similares;                        |" << endl;
        cout << "| 4. Verificar a existência de um item;             |" << endl;
        cout << "| 5. Listar itens (ordem alfabética de nome);       |" << endl;
        cout << "| 6. Listar itens (ordem decrescente de raridade)   |" << endl;
        cout << "| 7. Contar itens com mesma propriedade mágica;     |" << endl;
        cout << "| 8. Remover itens menos raros;                     |" << endl;
		cout << "| 9. Sair                                           |" << endl;
        cout << "=====================================================" << endl;
        cout << "Escolha uma opção: " << endl;
        cin >> opcao;


        switch (opcao) { 
    case 1:
		inserirItem();
        break;
    case 2:
		cadastrarSimilaridades();
        break;
    case 3:
		buscarItens();
        break;
    case 4:
        verificarItem();
        break;
    case 5:
        listarItemA();
        break;
    case 6:
        listarItemR();
        break;
    case 7:
        contarItens();
        break;
    case 8:
        remover();
        break;
    case 9:
    	cout << "Saindo..." << endl;
    	break;
}
	}while(opcao != 9);

	
	return 0;
}