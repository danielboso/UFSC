package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;

public class Senha {
	
	private String senha;

	public Senha(String senha) {
		this.senha = senha;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida {
		if (senha.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}
	}

	@Override
	public String toString() {
		return senha.toString();
	}
}