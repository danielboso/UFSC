package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Rua {
	
	private String rua;
	
	public Rua(String rua) {
		this.rua = rua;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (rua.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return rua.toString();
	}
}