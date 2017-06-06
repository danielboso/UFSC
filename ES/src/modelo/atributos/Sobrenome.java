package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;
import excecoes.ExcecaoEntradaNaoPermitida;

public class Sobrenome {
	
private String sobrenome;
	
	public Sobrenome(String sobrenome) {
		this.sobrenome = sobrenome;
	}
	
	public void verificaExcecoes() throws ExcecaoEntradaInvalida, ExcecaoEntradaNaoPermitida {
		if (sobrenome.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	public String toString() {
		return sobrenome.toString();
	}
}
