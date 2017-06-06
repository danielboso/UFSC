package controle;

import java.sql.Date;

import excecoes.ExcecaoCpfJaEstaCadastrado;
import excecoes.ExcecaoEntradaInvalida;
import excecoes.ExcecaoEntradaNaoPermitida;
import excecoes.ExcecaoIdJaEstaEmUso;
import modelo.Fachada;
import modelo.atributos.Cpf;
import modelo.atributos.Email;
import modelo.atributos.Nome;
import modelo.atributos.NomeUsuario;
import modelo.atributos.Senha;
import modelo.atributos.Sexo;
import modelo.atributos.Sobrenome;
import modelo.usuario.Cliente;
import visao.JanelaPrincipal;

public class Controle {

	@SuppressWarnings("deprecation")
	public static void main(String[] args) {
		JanelaPrincipal janela = new JanelaPrincipal();

		Date dataNascimento = new Date(1, 1, 1);
		
		Cpf cpf = null;
		try {
			cpf = new Cpf("2");
			cpf.verificaExcecoes();
		} catch (ExcecaoCpfJaEstaCadastrado | ExcecaoEntradaInvalida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Nome nome = null;
		try {
			nome = new Nome("nome");
			nome.verificaExcecoes();
		} catch (ExcecaoEntradaInvalida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ExcecaoEntradaNaoPermitida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Sobrenome sobrenome = null;
		try {
			sobrenome = new Sobrenome("sobrenome");
			sobrenome.verificaExcecoes();
		} catch (ExcecaoEntradaInvalida | ExcecaoEntradaNaoPermitida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Sexo sexo = Sexo.Masculino;
		Email email = null;
		try {
			email = new Email("a@b.com");
			email.verificaExcecoes();
		} catch (ExcecaoEntradaInvalida | ExcecaoEntradaNaoPermitida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		NomeUsuario nomeUsuario = null;
		try {
			nomeUsuario = new NomeUsuario("a");
			nomeUsuario.verificaExcecoes();
		} catch (ExcecaoIdJaEstaEmUso e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ExcecaoEntradaNaoPermitida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ExcecaoEntradaInvalida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Senha senha = null;
		try {
			senha = new Senha("a");
			senha.verificaExcecoes();
		} catch (ExcecaoEntradaInvalida e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Cliente cliente = new Cliente(cpf, nome, sobrenome, dataNascimento, sexo, email, nomeUsuario, senha);

		Fachada.getInstance().cadastrarCliente(cliente);
	}
}
