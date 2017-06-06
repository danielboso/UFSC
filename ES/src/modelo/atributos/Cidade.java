package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Cidade {
	
	private String cidade;
	
	public Cidade(String cidade) {
		this.cidade = cidade;
	}
	
	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (cidade.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return cidade;
	}
}
