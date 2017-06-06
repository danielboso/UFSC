package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Bairro {
	
	private String bairro;
	
	public Bairro(String bairro) {
		this.bairro = bairro;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (bairro.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return bairro;
	}
}