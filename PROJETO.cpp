/*
Mariana Bissaro Weiss, 2281
Layla Victória Sousa Teles, 2426
Livia Oliveira Santos, 2290
Maria Clara Freitas Soares, 712
Miguel Borges Magalhães, 978
Ruan Carlo Martins Garcia,487
*/

#include <iostream>
#include <locale.h>
#include <list>
#include <string>
//biblioteca locale.h permite usar os caracteres da lingua portuguesa

#include <cstdlib>
#include <conio.h>
//bicliotecas para limpar o terminal e utilizar teclas especiais

#define RESET     "\033[0m"
#define VERDE     "\033[32m"
#define VERDE_ESC "\033[92m"  // verde mais brilhante
#define NEGRITO   "\033[1m"
//variaveis para decoracao do menu

using namespace std;

void centralizar(string texto, bool quebrarLinha = true){ //funcao que centraliza o texto
    int larguraTela = 80;
    int espacos = (larguraTela - texto.length()) / 2;

    for(int i = 0; i < espacos; i++)
        cout << " ";

    cout << texto;

    if(quebrarLinha)
        cout << endl;
}

//função para limpar a tela
void limparTela(){
    system("cls");
}

// função para poder utilizar ESC
void esperarESC(){
    cout << endl;
    cout << VERDE;

    centralizar("+-------------------------------------+");
    centralizar("Pressione ESC para voltar ao menu");
    centralizar("+-------------------------------------+");

    cout << RESET;
    char tecla;
    
    while(true){
        tecla = getch();
        if(tecla == 27) break;
    }
}

// para adicionar um novo item
struct inserirObj{
	string nomeItem, nomeDono, propMagica;
	int id, raridade; // raridade = numero de 0 a 100 onde 0=comum,100=raríssimo
};

// Struct que representa uma aresta do grafo de similaridade
struct Aresta{
	int destino, peso; // não precisa de origem pois o id do item ja nos dá á origem, destino = id do item relacionado, peso = valor de similaridade
};

struct Node{// struct arvore binaria
    inserirObj item;//herda as variaveis da struct inserirObj
    Node * esq;
    Node * dir;
};

list<Aresta> adj[1000];
Node * raiz = NULL;// nó raiz começa null
list<inserirObj> itens; // criei uma lista para adicionar os itens, cada posição da lista é um item

void inserirABB(Node *& raiz, inserirObj novo){// ja estou inserindo na arvore pelo nome
    if(raiz == NULL){
        raiz = new Node;
        raiz->item = novo;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }else{
    	if(novo.nomeItem < raiz->item.nomeItem){
        	inserirABB(raiz->esq, novo);
		}else if(novo.nomeItem >= raiz->item.nomeItem){
        	inserirABB(raiz->dir, novo);
		}
	}
}

void inserirABBRaridade(Node *& raizR, inserirObj novo){
    if(raizR == NULL){
        raizR = new Node;
        raizR->item = novo;
        raizR->esq = NULL;
        raizR->dir = NULL;
    }else{
        if(novo.raridade < raizR->item.raridade){
            inserirABBRaridade(raizR->esq, novo);
        }else{
            inserirABBRaridade(raizR->dir, novo);
        }
    }
} // função de inserir arvore binaria diretamente adaptada do material de codigos nosso sobre ABB

void mostrarRaridadeDecrescente(Node * raizR){
    if(raizR != NULL){
        mostrarRaridadeDecrescente(raizR->dir);

        cout << "Nome: " << raizR->item.nomeItem
             << " | ID: " << raizR->item.id
             << " | Dono: " << raizR->item.nomeDono
             << " | Raridade: " << raizR->item.raridade << endl;

        mostrarRaridadeDecrescente(raizR->esq);
    }
} // função mostrarArvore adaptada

void destruirArvore(Node *& raiz){
    if(raiz != NULL){
        destruirArvore(raiz->esq);
        destruirArvore(raiz->dir);
        delete raiz;
        raiz = NULL;
    }
} // função destruct adaptada
	
void reconstruirArvore(){
    destruirArvore(raiz); // apaga toda a arvore

    list<inserirObj>::iterator it; // percorre a lista de itens restantes
    for(it = itens.begin(); it != itens.end(); it++){
    	
        inserirABB(raiz, *it); // insere denovo cada item na arvore
    }
}

void inserirItem(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|          >> INSERIR ITEM <<         |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    inserirObj novo;

    centralizar("Nome do Item: ", false);
    cin.ignore();
    getline(cin, novo.nomeItem);

    centralizar("Nome do Dono: ", false);
    getline(cin, novo.nomeDono);

    centralizar("Propriedade magica do item: ", false);
    getline(cin, novo.propMagica);

    centralizar("ID: ", false);
    cin >> novo.id;

    centralizar("Raridade (0 a 100): ", false);
    cin >> novo.raridade;

    itens.push_back(novo);
    inserirABB(raiz, novo);

	cout << VERDE << NEGRITO;
    centralizar("+-------------------------------------+");
    centralizar("|        >> Item adicionado! <<       |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;

    esperarESC();
}

void cadastrarSimilaridades(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> CADASTRAR SIMILARIDADE <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int id1, id2, s;
    centralizar("ID do item 1: ", false);
    cin >> id1;
    centralizar("ID do item 2: ", false);
    cin >> id2;
    centralizar("Similaridade entre eles: ", false);
    cin >> s;

    adj[id1].push_back({id2, s});
    adj[id2].push_back({id1, s});

    cout << endl;
    centralizar("+-------------------------------------+");
    centralizar("|    >> Similaridade cadastrada! <<   |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;

    esperarESC();
}

void buscarItens(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> BUSCAR ITENS SIMILARES <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int idC;
    double X;
    string jogadorJ;
    list<Aresta>::iterator it;
    list<inserirObj>::iterator it2;

    centralizar("Codigo do item: ", false);
    cin >> idC;
    centralizar("Similaridade minima: ", false);
    cin >> X;
    centralizar("Nome do jogador: ", false);
    cin >> jogadorJ;

    cout << endl;
    centralizar("+-------------------------------------+");
    centralizar("|          >> RESULTADOS <<           |");
    centralizar("+-------------------------------------+");

    bool encontrou = false;
    for(it = adj[idC].begin(); it != adj[idC].end(); it++){
        if(it->peso > X){
            for(it2 = itens.begin(); it2 != itens.end(); it2++){
                if(it2->id == it->destino && it2->nomeDono != jogadorJ){
                    cout << "| ID: "         << it2->id       << endl;
                    cout << "| Nome: "       << it2->nomeItem << endl;
                    cout << "| Dono: "       << it2->nomeDono << endl;
                    cout << "| Similaridade: " << it->peso   << endl;
                    centralizar("+-------------------------------------+");
                    encontrou = true;
                }
            }
        }
    }

    if(!encontrou)
        centralizar("| >> Nenhum item encontrado! <<       |");

    cout << RESET << endl;
    esperarESC();
}
Node * buscar(Node * raiz, string nome){// retorna um ponteiro para o nó encontrado ou retorna null
	if(raiz == NULL) // quer dizer que não encontrou o nó
		return NULL;
	if(nome == raiz->item.nomeItem){ // se o nó que eu to encontrando for igual ao nó que o ponteiro ja esta apontando, retorna ele
		return raiz;
	} else {
		if(nome > raiz->item.nomeItem){// se o nó que eu to procurando é mais que o nó que o ponteiro esta apontando
			return buscar(raiz->dir, nome);// eu aponto para a direita deste nó
		} else if(nome < raiz->item.nomeItem){// se for menor 
			return buscar(raiz->esq, nome);// aponto o ponteiro para a esquerda deste nó
		}
	}
	return NULL;
}


void verificarItem(){ //verificar se o item existe
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|   >> VERIFICAR EXISTENCIA ITEM <<   |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;
    
    string nomeBusca;
    centralizar("Digite o nome do item: ", false);
    cin.ignore();
    getline(cin, nomeBusca);

    cout << endl;
	Node * encontrado = buscar(raiz,nomeBusca);
    if(encontrado != NULL) {
        centralizar("+-------------------------------------+");
        centralizar("|         >> ITEM ENCONTRADO! <<      |");
        centralizar("+-------------------------------------+");
    } else {
        centralizar("+-------------------------------------+");
        centralizar("|       >> ITEM NAO ENCONTRADO! <<    |");
        centralizar("+-------------------------------------+");
    }

    cout << RESET << endl;
    esperarESC();
}

void mostrarArvore(Node * raiz){// mostra a árvore inteira 
	if(raiz->esq != NULL)// se tiver nó a esquerda
		mostrarArvore(raiz->esq);// mostro o nó da esquerda
		cout << "Nome: " << raiz->item.nomeItem 
             << " | ID: " << raiz->item.id 
             << " | Dono: " << raiz->item.nomeDono 
			 << " | Propriedade Magica: " << raiz->item.propMagica 
             << " | Raridade: " << raiz->item.raridade << endl;
	if(raiz->dir != NULL) // se tiver nó na direita
		mostrarArvore(raiz->dir);// mostro os valores do nó a direita
}


void listarItemA(){ //listar item em ordem alfabética
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|   >> LISTAR ITENS (ALFABETICA) <<   |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;
    
    mostrarArvore(raiz);
    cout << RESET << endl;
    esperarESC();
}

void listarItemR(){ //listar itens em ordem decrescente de raridade
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|        >> LISTAR (RARIDADE) <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    Node * raizR = NULL;

    list<inserirObj>::iterator it;
    for(it = itens.begin(); it != itens.end(); it++){
        inserirABBRaridade(raizR, *it);
    }

    if(raizR == NULL){
        centralizar("|        >> Nenhum item cadastrado! <<|");
    }else{
        mostrarRaridadeDecrescente(raizR);
    }

    destruirArvore(raizR);

    cout << RESET << endl;
    esperarESC();
}

void contarItens(){

    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> CONTAR POR PROPRIEDADE <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    string prop;
    int cont = 0;

    centralizar("Digite a propriedade magica: ", false);
    cin.ignore();
    getline(cin, prop);

    list<inserirObj>::iterator it;
    for(it = itens.begin(); it != itens.end(); it++){
		
        if(it->propMagica == prop){ // aqui faz a verificação da propriedade
            cont++;
        }
    }

    cout << endl;
    cout << "Quantidade de itens com essa propriedade: " << cont << endl;

    cout << RESET << endl;
    esperarESC();
}

void remover(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      >> REMOVER MENOS RAROS <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int R;
    centralizar("Remover itens com raridade menor que: ", false);
    cin >> R;

    int removidos = 0;

    list<inserirObj>::iterator it = itens.begin(); // iterador q percorre a lista de itens

    while(it != itens.end()){
        if(it->raridade < R){  // verificação de raridade
            it = itens.erase(it);
            removidos++;
        } else {
            it++;
        }
    }

    reconstruirArvore(); // atualiza a arvore binaria

    cout << endl;
    cout << "Quantidade de itens removidos: " << removidos << endl;

    cout << RESET << endl;
    esperarESC();
}


// cabecalho estilizado
void cabecalhoDecorado() {
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      ***  BOLSA DEVORADORA  ***     |");
    centralizar("+=====================================+");
    cout << RESET << endl;
}


int main (){

	setlocale(LC_ALL, "Portuguese");
	//função da biblioteca locale

	int opcao;
	do{
		limparTela();
		
		cabecalhoDecorado();

		cout << VERDE;
    	centralizar("+-------------------------------------+");
    	centralizar("|            -- ACOES --              |");
    	centralizar("+-------------------------------------+");
    	centralizar("¦  [1] >> Inserir item                ¦");
    	centralizar("¦  [2] >> Cadastrar similaridade      ¦");
    	centralizar("¦  [3] >> Buscar itens similares      ¦");
    	centralizar("¦  [4] >> Verificar existencia        ¦");
    	centralizar("¦  [5] >> Listar (alfabetica)         ¦");
    	centralizar("¦  [6] >> Listar (raridade)           ¦");
    	centralizar("¦  [7] >> Contar por propriedade      ¦");
    	centralizar("¦  [8] >> Remover menos raros         ¦");
    	centralizar("¦  [9] >> Sair                        ¦");
    	centralizar("+-------------------------------------+");
    	cout << RESET << endl;

		centralizar("Escolha uma opcao: ", false);
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
    		centralizar("Saindo...");
    		cout << RESET << endl;
			break;
		}
	}
	while(opcao != 9);


	return 0;
} 
