//!	Classe estatistica.
/*!
 *  \Copyright (C) 2016  Adan Pereira Gomes e Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SRC_ESTATISTICA_H_
#define SRC_ESTATISTICA_H_

namespace supermercado {

class Estatistica {
public:
	Estatistica();

	~Estatistica();

	void gerarEstatisticas();

private:

	void calculaFaturamentoTotal();

};

} /* namespace supermercado */

#endif /* SRC_ESTATISTICA_H_ */
