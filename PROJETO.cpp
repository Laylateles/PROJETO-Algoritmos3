/*
Mariana Bissaro Weiss, 2281
Layla Vict�ria Sousa Teles, 2426
livia oliveira santos, 2290
Maria Clara Freitas Soares, 712
Miguel Borges Magalh�es, 978
Ruan Carlo Martins Garcia,487
*/

#include <iostream>
#include <locale.h>
#include <list>
#include <string>
//biblioteca locale.h permite usar os caracteres da lingua portuguesa
using namespace std;

// para adicionar um novo item
struct inserirObj{
	string nomeItem, nomeDono, propMagica;
	int id, raridade; // raridade = numero de 0 a 100 onde 0=comum,100=raríssimo
};

// Struct que representa uma aresta do grafo de similaridade
struct Aresta{
	int destino, peso; // não precisa de origem pois o id do item ja nos dá à origem, destino = id do item relacionado, peso = valor de similaridade
};

list<inserirObj> itens; // criei uma lista para adicionar os itens cadastrados, cada posição da lista é um item
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

	itens.push_back(novo);// adicionei na minha lista de itens o meu novo item, eu adiciono o item no final da lista

	cout << "Item adicionado!\n";
}

list<Aresta> adj[1000]; // lista de adjacência do grafo (índice = id do item)
void cadastrarSimilaridades(){
	int id1, id2, s;
	cout << "Digite o ID do item 1: " << endl;
	cin >> id1;
	cout << "Digite o ID do item 2: " << endl;
	cin >> id2;
	cout << "Similaridade entre eles: " << endl;
	cin >> s;

	adj[id1].push_back( {id2, s}); // // aresta de id1 ? id2 com peso s
	adj[id2].push_back( {id1, s}); // se for um grafo não orientado

	cout << "Similaridade cadastrada!\n";
}

void buscarItens(){
	int idC;// o item que eu quero analisar --- o id dele
	double X; // a similaridade entre os itens tem que ser maior que esse valor X
	string jogadorJ;// vou olhar os itens que não são desse jogador
	list<Aresta>::iterator it;
	list<inserirObj>::iterator it2;
	
	cout << "Digite o c�digo do item:" << endl;
	cin >> idC;
	cout << "Digite o valor minimo de similaridade:" << endl;
	cin >> X;
	cout << "Digite o nome do jogador:" << endl;
	cin >> jogadorJ;

	bool encontrou = false;
	for(it = adj[idC].begin(); it != adj[idC].end(); it++){ // aqui ele percorre todos os vizinhos do item C,  porque na lista de adjacencia é armazenado os vizinhos de cada id
		if(it->peso > X){ // verifica se a similaridade é maior que X
			for(it2 = itens.begin(); it2 != itens.begin(); it2++){ //aqui ele percorre a lista com os itens
				if(it2->id == it->destino && it2->nomeDono != jogadorJ){ //aqui ele verifica se o id do item é igual o id do item que eu quero verificar
					cout << "ID: " << it2->id;
					cout << " | Nome: " << it2->nomeItem;
					cout << " | Dono: " << it2->nomeDono;
					cout << " | Similaridade: " << it->peso << "\n";
					encontrou = true;
				}
			}
		}
	}
	if(!encontrou)
		cout << "Item n�o encontrado!" << endl;
}

void verificarItem(){
	cout << "Funcionalidade em construcao" << endl;
}

void listarItemA(){  //listar item em ordem alfabética

	cout << "Funcionalidade em construcao" << endl;
}

void listarItemR(){  //listar itens em ordem decrescente de raridade
	cout << "Funcionalidade em construcao" << endl;
}

void contarItens(){
	cout << "Funcionalidade em construcao" << endl;
}

void remover(){  //remover itens menos raros
	cout << "Funcionalidade em construcao" << endl;
}


int main (){

	setlocale(LC_ALL, "Portuguese");
//função da biblioteca locale

	int opcao;
	do{
		cout << "================== BOLSA DEVORADORA =================" << endl;
		cout << "| 1. Inserir item                                   |" << endl;
		cout << "| 2. Cadastrar similaridade entre itens;            |" << endl;
		cout << "| 3. Buscar itens similares;                        |" << endl;
		cout << "| 4. Verificar a existencia de um item;             |" << endl;
		cout << "| 5. Listar itens (ordem alfabetica de nome);       |" << endl;
		cout << "| 6. Listar itens (ordem decrescente de raridade)   |" << endl;
		cout << "| 7. Contar itens com mesma propriedade magica;     |" << endl;
		cout << "| 8. Remover itens menos raros;                     |" << endl;
		cout << "| 9. Sair                                           |" << endl;
		cout << "=====================================================" << endl;
		cout << "Escolha uma opcao: " << endl;
		cin >> opcao;


		switch (opcao){
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
	}
	while(opcao != 9);


	return 0;
}
