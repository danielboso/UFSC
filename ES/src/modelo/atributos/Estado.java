package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Estado {
	
	private String estado;
	
	public Estado(String estado) {
		this.estado = estado;
	}
	
	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (estado.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	@Override
	public String toString() {
		return estado;
	}
}
