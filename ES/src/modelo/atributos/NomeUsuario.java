package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;
import excecoes.ExcecaoEntradaNaoPermitida;
import excecoes.ExcecaoIdJaEstaEmUso;
import modelo.Fachada;

public class NomeUsuario {
	
private String nomeUsuario;
	
	public NomeUsuario(String idCliente) {
		this.nomeUsuario = idCliente;
	}

	public void verificaExcecoes() throws ExcecaoEntradaNaoPermitida, ExcecaoEntradaInvalida, ExcecaoIdJaEstaEmUso {
		if (nomeUsuario.length() == 0) {
			throw new ExcecaoEntradaInvalida();
		}

		if (Fachada.getInstance().verificaSeIdEstaCadastrado(nomeUsuario) == true) {
			throw new ExcecaoIdJaEstaEmUso();
		}
	}
	
	@Override
	public String toString() {
		return nomeUsuario.toString();
	}
}
