/*
Mariana Bissaro Weiss, 2281
Layla Victória Sousa Teles, 2426
livia oliveira santos, 2290
Maria Clara Freitas Soares, 712
Miguel Borges Magalhães, 978
Ruan Carlo Martins Garcia,487
*/

#include <iostream>
#include <locale.h>
#include <list>
//biblioteca locale.h permite usar os caracteres da lingua portuguesa
using namespace std;

struct inserirObj{
	string nomeItem,nomeDono,propMagica;
	int id,raridade; // raridade = numero de 0 a 100 onde 0=comum,100=raríssimo
};

struct grafo{//grafo para a similaridade entre os itens
	int destino,peso; // para apontar as arestas do grafo, não precisa de origem pois o id do item ja nos dá à origem
};

struct No{
    inserirObj item;
    No* esq;
    No* dir;
};


list<Aresta> adj[1000];
No* raiz = NULL;
list<inserirObj> itens; // criei uma lista para adicionar os itens, cada posição da lista é um item

No* inserirABB(No* raiz, inserirObj novo){
    if(raiz == NULL){
        No* novoNo = new No;
        novoNo->item = novo;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        return novoNo;
    }

    if(novo.id < raiz->item.id)
        raiz->esq = inserirABB(raiz->esq, novo);
    else if(novo.id > raiz->item.id)
        raiz->dir = inserirABB(raiz->dir, novo);

    return raiz;
}

No* buscarABB(No* raiz, int id){
    if(raiz == NULL || raiz->item.id == id)
        return raiz;

    if(id < raiz->item.id)
        return buscarABB(raiz->esq, id);
    else
        return buscarABB(raiz->dir, id);
}


void inserirItem(){
	inserirObj novo;// criei uma variavel do tipo da struct

	cout << "Nome do Item: " << endl;
	cin >> novo.nomeItem;

	cout << "Nome do Dono: " << endl;
	cin >> novo.nomeDono;

	cout << "Propriedade mágica do item: " << endl;
	cin >> novo.propMagica;

	cout << "ID: " << endl;
	cin >> novo.id;

	cout << "Raridade(0 a 100): " << endl;
	cin >> novo.raridade;

	itens.push_back(novo);// adicionei na minha lista de itens o meu novo item
	raiz = inserirABB(raiz, novo);

	cout << "Item adicionado!\n";
}

void cadastrarSimilaridades(){
	cout << "Funcionalidade em construção" << endl;
}

void buscarItens(){
	limparTela();
	cout << "=== BUSCAR ITENS ===" << endl;

	int idC;
	double X;
	string jogador;

	cout << "Digite o código do item:" << endl;
	cin >> idC;

	cout << "Digite o valor minimo de similaridade:" << endl;
	cin >> X;

	cout << "Digite o nome do jogador:" << endl;
	cin >> jogadorJ;

	bool encontrou = false;

	for(auto it = adj[idC].begin(); it != adj[idC].end(); it++){
		if(it->peso > X){
			No* encontrado = buscarABB(raiz, it->destino);
			if(encontrado != NULL && encontrado->item.nomeDono != jogadorJ){
				cout << "ID: " << encontrado->item.id;
				cout << " | Nome: " << encontrado->item.nomeItem;
				cout << " | Dono: " << encontrado->item.nomeDono;
				cout << " | Similaridade: " << it->peso << endl;

				encontrou = true;
			}
		}
	}

	if(!encontrou)
		cout<< "Item nao encontrado!" << endl;

	esperarESC();
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
