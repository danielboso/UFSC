package modelo.atributos;

import excecoes.ExcecaoCpfJaEstaCadastrado;
import excecoes.ExcecaoEntradaInvalida;
import modelo.Fachada;

public class Cpf {
	
	private Integer cpf;
	
	public Cpf(String cpfEmString) {
		cpf = Integer.parseInt(cpfEmString);
	}
	
	public void verificaExcecoes() throws ExcecaoEntradaInvalida, ExcecaoCpfJaEstaCadastrado {
		if (cpf < 0) {
			throw new ExcecaoEntradaInvalida();
		}
		
		if (Fachada.getInstance().verificaSeCpfEstaCadastrado(cpf)) {
			throw new ExcecaoCpfJaEstaCadastrado();
		}
	}
	
	@Override
	public String toString() {
		return cpf.toString();
	}
}