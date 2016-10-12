//  !	Classe SuperMercado.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_SUPERMERCADO_H_
#define SUPERMERCADO_SUPERMERCADO_H_

//#include <string>

#include "./caixa.h"
#include "structures/circular_list.h"

namespace supermercado {

class SuperMercado {
 public:
	SuperMercado(std::string, unsigned, unsigned, unsigned);

	~SuperMercado();

	void adiciona_caixa(std::string, unsigned, unsigned);

  structures::CircularList<Caixa*> caixas();

  std::string nome_mercado();

  unsigned numero_desistencias();

  unsigned valor_perdido();

  void adiciona_tempo_relogio();

  unsigned relogio();

  void atualiza_caixas();

	void gera_cliente();

  Caixa* menor_fila();

 private:

	void calcula_perda(Cliente*);

	Caixa* menos_produtos();

	bool lugar_fila();

	structures::CircularList<Caixa*> caixas_;
	std::string nome_mercado_;
	unsigned tempo_simulacao_;
	unsigned tempo_medio_chegada_;
	unsigned total_caixas_;
	unsigned clientes_desistentes_{0u};
	unsigned valor_perdido_{0u};
	unsigned relogio_{0u};
};

}

#endif
