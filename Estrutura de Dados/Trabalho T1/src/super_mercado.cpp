//  !	Classe SuperMercado.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "./super_mercado.h"

namespace supermercado {

//! Construror
/*!
 *	Construtor que é responsável por inicializar o supermercado.
 */
SuperMercado::SuperMercado(std::string nome_mercado, unsigned tempo_simulacao, unsigned tempo_medio_chegada, unsigned total_caixas) :
		nome_mercado_{nome_mercado},
		tempo_simulacao_{tempo_simulacao},
		tempo_medio_chegada_{tempo_medio_chegada},
		total_caixas_{total_caixas}
{
	caixas_ = *(new structures::CircularList<Caixa*>());
}

//! Destrutor
SuperMercado::~SuperMercado() {}

//! Função adiciona_caixa
/*!
 *	Função responsável por adicionar um caixa no supermercado.
 */
void SuperMercado::adiciona_caixa(std::string identificador , unsigned eficiencia, unsigned salario) {
	Caixa* caixa = new Caixa(identificador, eficiencia, salario);
	caixas_.push_front(caixa);
}

//! Função caixas_
/*!
 *	Função responsável por retornar a lista circular de caixas.
 */
structures::CircularList<Caixa*> SuperMercado::caixas() {
	return caixas_;
}

//! Função atualiza_caixas
/*!
 *	Função responsável por atualizar caixas. Vai percorrer cada caixa e verificar
 * 	se há clientes que precisam sair da fila pois já terminaram de realizar sua compra.
 */
void SuperMercado::atualiza_caixas() {
	for (auto i = 0u; i != caixas_.size(); ++i) {
		caixas_.at(i)->retira_cliente(relogio_);
	}
}

//! Função gera_cliente
/*!
 *	Função responsável por instanciar um cliente e adicioná-lo na fila do caixa.
 *	A função irá chamar outras funções para que possa se achar a fila onde o cliente
 * 	prefere ir.
 */
void SuperMercado::gera_cliente() {
	Cliente* cliente = new Cliente(relogio_);
	if (lugar_fila()) {
		if (cliente->tipo() == MENOS_PRODUTOS) {
			menos_produtos()->recebe_cliente(cliente);
		} else {
			menor_fila()->recebe_cliente(cliente);
		}
	} else {
		calcula_perda(cliente);
	}
}

//! Função calcula_perda
/*!
 *	Função responsável pelo cálculo dos prejuízos causados pelos clientes que
 * 	desistiram da compra.
 */
void SuperMercado::calcula_perda(Cliente* cliente) {
	++clientes_desistentes_;
	valor_perdido_ += cliente->valor_total() * 3;
	delete cliente;
}

//! Função menos_produtos
/*!
 *	Função responsável por procurar uma fila de caixa onde há menos produtos que
 * 	que devem ser passados até chegar a sua hora de ser atendido.
 */
Caixa* SuperMercado::menos_produtos() {
	Caixa* caixa = caixas_.at(0u);
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->produtos_pendentes() < caixa->produtos_pendentes()) {
			caixa = caixas_.at(i);
		}
	}
	return caixa;
}

//! Função menor_fila
/*!
 *	Função responsável por procurar uma fila de caixa onde há menos clientes na
 *	na fila.
 */
Caixa* SuperMercado::menor_fila() {
	Caixa* caixa = caixas_.at(0u);
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->clientes_fila() < caixa->clientes_fila()) {
			caixa = caixas_.at(i);
		}
	}
	return caixa;
}

//! Função lugar_fila
/*!
 *	Função que verifica se há lugar na fila, ou seja, se o cliente vai pra fila.
 *	Caso o cliente não queira ir para a fila, ele desistirá da compra e seus produtos_pendentes
 * 	do carrinho serão contabilizados como prejuízo.
 */
bool SuperMercado::lugar_fila() {
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->clientes_fila() < 10) {
			return true;
		}
	}
	return false;
}

//! Função nome_mercado
/*!
 *	Função responsável por retornar o nome do supermercado.
 */
std::string SuperMercado::nome_mercado() {
	return nome_mercado_;
}

//! Função numero_desistencias
/*!
 *	Função responsável por retornar o número de desistências ocorridas no
 * 	supermercado.
 */
unsigned SuperMercado::numero_desistencias() {
	return clientes_desistentes_;
}

//! Função valor_perdido
/*!
 *	Função responsável por retornar o valor perdido (prejuízo).
 */
unsigned SuperMercado::valor_perdido() {
	return valor_perdido_;
}

//! Função adiciona_tempo_relogio
/*!
 *	Função responsável por incrementar o valor do relógio.
 */
void SuperMercado::adiciona_tempo_relogio() {
	++relogio_;
}

//! Função relogio
/*!
 *	Função responsável por retornar o tempo atual de simulação.
 */
unsigned SuperMercado::relogio() {
	return relogio_;
}

}
