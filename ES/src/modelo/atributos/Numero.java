package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Numero {
	
	private Integer numero;
	
	public Numero(String numeroEmString) {
		this.numero = Integer.parseInt(numeroEmString);
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (numero < 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return numero.toString();
	}
}	