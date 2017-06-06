package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Complemento {
	
	private String complemento;
	
	public Complemento(String complemento) {
		this.complemento = complemento;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (complemento.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return complemento.toString();
	}
}