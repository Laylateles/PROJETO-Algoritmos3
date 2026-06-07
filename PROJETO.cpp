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

struct Ponto{//para o algoritmo geometrico
    int x, y;
};
// para adicionar um novo item
struct inserirObj{
	string nomeItem, nomeDono, propMagica;
	int id, raridade; // raridade = numero de 0 a 100 onde 0=comum,100=raríssimo
    int qtdVertices;
    Ponto contorno[10];//assumindo que um item terá no maximo 20 vertices
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

const int ABERTURA_BOLSA = 15;
list<Aresta> adj[1000];
Node * raiz = NULL;// nó raiz começa null
Node * raizR = NULL;//nó raiz de raridade
list<inserirObj> itens; // criei uma lista para adicionar os itens, cada posição da lista é um item
//-----------------------------------------------------------------------------------------------------------------
int larguraPoligono(inserirObj item){//para calcular a largura do item
    int menorX = item.contorno[0].x;
	int maiorX = item.contorno[0].x;
    for(int i = 1; i < item.qtdVertices; i++){
        if(menorX > item.contorno[i].x){
            menorX = item.contorno[i].x;
		}
        if(item.contorno[i].x > maiorX){
            maiorX = item.contorno[i].x;
		}
    }
    return maiorX - menorX;//retorna a largura do item
}



//-----------------------------------------------------------------------------------------------------------
void inserirABB(Node *& raiz, inserirObj novo){//arvore binaria pelo nome do objeto
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
//-------------------------------------------------------------------------------------------------------------
void inserirABBRaridade(Node *& raizR, inserirObj novo){//arvore binaria pela raridade do objeto
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
} 
//-------------------------------------------------------------------------------------------------------------
void mostrarRaridadeDecrescente(Node * raizR){//mostra os objetos pela raridade em ordem decrescente
    if(raizR == NULL)
    	return;

    mostrarRaridadeDecrescente(raizR->dir);

    cout << "Nome: " << raizR->item.nomeItem
         << " | ID: " << raizR->item.id
         << " | Dono: " << raizR->item.nomeDono
         << " | Propriedade: " << raizR->item.propMagica
         << " | Raridade: " << raizR->item.raridade
         << endl;
         
    mostrarRaridadeDecrescente(raizR->esq);
} 

//------------------------------------------------------------------------------------------------------------
void inserirItem(){//insere um item na arvore binaria
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
	
	centralizar("Quantidade de vertices do poligono: ", false);
	cin >> novo.qtdVertices;
	if(novo.qtdVertices < 3){
	    cout << endl;
	
	    centralizar("+-------------------------------------+");
	    centralizar("| UM POLIGONO PRECISA DE 3 PONTOS!    |");
	    centralizar("+-------------------------------------+");
	
	    esperarESC();
	    return;
	}
	if(novo.qtdVertices > 10){
	    cout << endl;
	
	    centralizar("+-------------------------------------+");
	    centralizar("| MAXIMO DE 10 VERTICES!              |");
	    centralizar("+-------------------------------------+");
	
	    esperarESC();
	    return;
	}
	
	for(int i = 0; i < novo.qtdVertices; i++){
	    cout << endl;
	    
	    cout << "Vertice " << i + 1 << endl;
	
	    cout << "X: ";
	    cin >> novo.contorno[i].x;
	
	    cout << "Y: ";
	    cin >> novo.contorno[i].y;
	}
	int largura = larguraPoligono(novo);

	if(largura > ABERTURA_BOLSA){
	
	    cout << endl;
	
	    centralizar("+-------------------------------------+");
	    centralizar("| ITEM NAO PASSA PELA ABERTURA!       |");
	    centralizar("+-------------------------------------+");
	
	    esperarESC();
	    return;
	}
    itens.push_back(novo);
    inserirABB(raiz, novo);//insere na arvore binaria pelo nome
    inserirABBRaridade(raizR, novo);//insere na arvore binaria pela raridade

	cout << VERDE << NEGRITO;
    centralizar("+-------------------------------------+");
    centralizar("|        >> Item adicionado! <<       |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;

    esperarESC();
}
//--------------------------------------------------------------------------------------------------
void cadastrarSimilaridades(){//cadastra as similaridade entre os itens
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
//------------------------------------------------------------------------------------------------------
void buscarItens(){//busca os itens pela sua similaridade
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
//------------------------------------------------------------------------------------------------------------
Node * buscar(Node * raiz, string nome){// busca o item pelo nome dele
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

//--------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------
void mostrarArvore(Node * raiz){// mostra a árvore inteira -- pelo nome do item
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

//-------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------
void listarItemR(){ //listar itens em ordem decrescente de raridade
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|        >> LISTAR (RARIDADE) <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

	mostrarRaridadeDecrescente(raizR);

    cout << RESET << endl;
    esperarESC();
}
//------------------------------------------------------------------------------------------------------------
void contarItens(){//conta quantidade de itens com a mesma propriedade magica
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
    if(cont > 0){
    	cout << "Quantidade de itens com essa propriedade: " << cont << endl;
	}else{
    	cout << "Nenhum item possui essa propriedade." << endl;
	}
    cout << RESET << endl;
    esperarESC();
}
//---------------------------------------------------------------------------------------------------------
void destruirArvore(Node *& raiz){//destruo a arvore
    if(raiz != NULL){
        destruirArvore(raiz->esq);
        destruirArvore(raiz->dir);
        delete raiz;
        raiz = NULL;
    }
} 
	
void reconstruirArvore(){//reconstruo as arvore com os elementos que restaram
    destruirArvore(raiz); // apaga toda a arvore
	destruirArvore(raizR);
	
    list<inserirObj>::iterator it; // percorre a lista de itens restantes
    for(it = itens.begin(); it != itens.end(); it++){
        inserirABB(raiz, *it); // insere denovo cada item na arvore
    	inserirABBRaridade(raizR, *it);
	}
}

void remover(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      >> REMOVER MENOS RAROS <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int R = 0;
    centralizar("Remover itens com raridade menor que: ", false);
    cin >> R;

    list<inserirObj>::iterator it = itens.begin(); // iterador q percorre a lista de itens

    while(it != itens.end()){
        if(it->raridade < R){  // verificação de raridade
            it = itens.erase(it);//Ele apaga apenas o elemento para o qual o iterador está apontando naquele momento
        } else {
            it++;
        }
    }

    reconstruirArvore(); // atualiza a arvore binaria

    cout << endl;
    centralizar("+-------------------------------------+");
    centralizar("|      >> Itens removidos! <<   |");
    centralizar("+-------------------------------------+");
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
