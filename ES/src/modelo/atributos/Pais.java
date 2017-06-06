package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Pais {
	
	private String pais;

	public Pais(String pais) {
		this.pais = pais;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (pais.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return pais.toString();
	}
}