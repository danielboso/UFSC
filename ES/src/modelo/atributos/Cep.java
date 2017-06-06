package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Cep {

	private Integer cep;

	public Cep(String cepEmString) {
		cep = Integer.parseInt(cepEmString);
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (cep <= 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}

	@Override
	public String toString() {
		return cep.toString();
	}
}