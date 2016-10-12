//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CAIXA_H_
#define SUPERMERCADO_CAIXA_H_

#include <fstream>
#include <string>

#include "./cliente.h"
#include "structures/linked_queue.h"

namespace supermercado {

class Caixa {

public:
	Caixa(std::string, unsigned, unsigned);

	~Caixa();

	void recebe_cliente(Cliente*);

	void retira_cliente(const unsigned&);

	void processa_compras(Cliente*);

	const std::ostream& operator<<(std::ostream&) const;

	const std::string identificador() const;

	const unsigned eficiencia() const;

	const unsigned salario() const;

	const unsigned produtos_pendentes() const;

	const unsigned clientes_fila() const;

	const unsigned clientes_atendidos() const;

	void faturamento_medio(int);

	const double faturamento_medio() const;

	const double faturamento_total() const;

	void tempo_espera_medio(unsigned);

	const unsigned tempo_espera_medio() const;

	unsigned clientes_atendidos();

private:
	structures::LinkedQueue<Cliente*> *clientes_;

	std::string identificador_;

	unsigned eficiencia_;

	unsigned salario_;

	unsigned produtos_pendentes_{0u};

	unsigned clientes_atendidos_{0u};

	double faturamento_medio_{0.0};

	double faturamento_total_{0.0};

	unsigned tempo_espera_medio_{0u};

	double lucro_caixa;

};

}  // namespace supermercado

#endif
