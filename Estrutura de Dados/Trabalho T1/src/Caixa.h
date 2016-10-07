//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CAIXA_H_
#define SUPERMERCADO_CAIXA_H_

#include <fstream>

#include "Cliente.h"
#include "LinkedQueue.h"

namespace supermercado {

class Caixa {

public:
	Caixa(char*, unsigned, unsigned);

	~Caixa();

	void receber_cliente();

	void processar_compras();

	const std::ostream& operator<<(std::ostream&) const;

	const char* identificador() const;

	const unsigned eficiencia() const;

	const unsigned salario() const;

	const unsigned produtos_pendentes() const;

	const unsigned clientes_fila() const;

	const unsigned clientes_atendidos() const;

	void faturamento_medio(int);

	const int faturamento_medio() const;

	const int faturamento_total() const;

	void tempo_espera_medio(unsigned);

	const unsigned tempo_espera_medio() const;

private:
	structures::LinkedQueue<Cliente>* clientes_;

	char* identificador_[80];

	unsigned eficiencia_;

	unsigned salario_;

	unsigned produtos_pendentes_{0u};

	unsigned clientes_atendidos_{0u};

	int faturamento_medio_{0};

	int faturamento_total_{0};

	unsigned tempo_espera_medio_{0u};

};

}  // namespace supermercado

#endif
