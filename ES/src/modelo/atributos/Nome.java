package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;
import excecoes.ExcecaoEntradaNaoPermitida;

public class Nome {
	
	private String nome;
	
	public Nome(String nome) {
		this.nome = nome;
	}
	
	public void verificaExcecoes() throws ExcecaoEntradaInvalida, ExcecaoEntradaNaoPermitida {
		if (nome.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	public String toString() {
		return nome.toString();
	}
}