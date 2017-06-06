package modelo.usuario;

import java.util.Date;

import modelo.atributos.Cpf;
import modelo.atributos.Email;
import modelo.atributos.Nome;
import modelo.atributos.NomeUsuario;
import modelo.atributos.Senha;
import modelo.atributos.Sexo;
import modelo.atributos.Sobrenome;

public class Cliente {
	
	private Cpf cpf;
	private Nome nome;
	private Sobrenome sobrenome;
	private Date dataNascimento;
	private Sexo sexo;
	private Email email;
	private NomeUsuario nomeUsuario;
	private Senha senha;
	
	private Anfitriao anfitriao;
	private Hospede hospede;

	public Cliente(Cpf cpf, Nome nome, Sobrenome sobrenome, Date dataNascimento, Sexo sexo, Email email,
			NomeUsuario nomeUsuario, Senha senha) {
		this.cpf = cpf;
		this.nome = nome;
		this.sobrenome = sobrenome;
		this.dataNascimento = dataNascimento;
		this.sexo = sexo;
		this.email = email;
		this.nomeUsuario = nomeUsuario;
		this.senha = senha;
		this.anfitriao = new Anfitriao();
		this.hospede = new Hospede();
	}
	
	public NomeUsuario getUsuario() {
		return nomeUsuario;
	}

	public Senha getSenha() {
		return senha;
	}

	public Nome getNome() {
		return nome;
	}

	public Sobrenome getSobrenome() {
		return sobrenome;
	}

	public Email getEmail() {
		return email;
	}

	public Date getDataNascimento() {
		return dataNascimento;
	}

	public Sexo getSexo() {
		return sexo;
	}

	public Cpf getCpf() {
		return cpf;
	}

	public Anfitriao getAnfitriao() {
		return anfitriao;
	}

	public Hospede getHospede() {
		return hospede;
	}
}
