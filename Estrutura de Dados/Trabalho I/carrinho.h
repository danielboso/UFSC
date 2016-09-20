#include <stdlib.h>

class Carrinho : LinkedStack<int> {

public:
	carrinho() {
		setaQuantidadeProdutos();
		setaPrecoProdutos();
	}
	~carrinho();

	int quantidadeProdutos;

	void setaQuantidadeProdutos() {
		quantidadeProdutos = rand() %100 + 2;
	}

	void setaPrecoProdutos() {
		for (int i = 0; i < quantidadeProdutos; i ++) {
			Carrinho::push(rand()%89 + 1);
		}
	}
};