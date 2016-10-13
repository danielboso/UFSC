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

//! classe SuperMercado
class SuperMercado {
 public:

  //! Construtor
  /*!
	 *  \param string    nome_do_mercado
   *  \param unsigned  tempo_simulacao
   *  \param unsigned  tempo_medio_chegada
   *  \param unsigned  total_caixas
	 */
	SuperMercado(std::string, unsigned, unsigned, unsigned);

  //! Destrutor
	~SuperMercado();

  //! Função adiciona_caixa
  /*!
	 *  \param string    identificador
   *  \param unsigned  eficiencia
   *  \param unsigned  salario
	 */
	void adiciona_caixa(std::string, unsigned, unsigned);

  //! Função caixas
  /*!
   *  \return CircularList<Caixa*>
   */
  structures::CircularList<Caixa*> caixas();

  //! Função nome_mercado
  /*!
   *  \return string
   */
  std::string nome_mercado();

  //! Função numero_desistencias
  /*!
   *  \return unsigned
   */
  unsigned numero_desistencias();

  //! Função valor_perdido
  /*!
   *  \return unsigned
   */
  unsigned valor_perdido();

  //! Função adiciona_tempo_relogio
  void adiciona_tempo_relogio();

  //! Função relogio
  /*!
   *  \return unsigned
   */
  unsigned relogio();

  //! Função atualiza_caixas
  void atualiza_caixas();

  //! Função gera_cliente
	void gera_cliente();

  //! Função menor_fila
  Caixa* menor_fila();

 private:

  //! Função calcula_perda
	void calcula_perda(Cliente*);

  //! Função menos_produtos
  /*!
   *  \return Caixa*
   */
	Caixa* menos_produtos();

  //! Função lugar_fila
  /*!
   *  \return bool
   */
	bool lugar_fila();

	structures::CircularList<Caixa*> caixas_; // lista circular de caixas
	std::string nome_mercado_; // nome do supermercado
	unsigned tempo_simulacao_; // tempo de simulação do supermercado
	unsigned tempo_medio_chegada_; // tempo medio de chegada de novos clientes
	unsigned total_caixas_; // total de caixas do supermercado
	unsigned clientes_desistentes_{0u}; // número de clientes que desistiram da compra
	unsigned valor_perdido_{0u}; // valor perdido com a desistência de clientes
	unsigned relogio_{0u}; // tempo simulado
};

}

#endif
