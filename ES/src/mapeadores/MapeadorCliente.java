package mapeadores;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import modelo.atributos.Cpf;
import modelo.atributos.Email;
import modelo.atributos.Nome;
import modelo.atributos.NomeUsuario;
import modelo.atributos.Senha;
import modelo.atributos.Sexo;
import modelo.atributos.Sobrenome;
import modelo.usuario.Cliente;

public class MapeadorCliente {

	private Connection con;

	public MapeadorCliente(Connection con) {
		this.con = con;
	}

	public void insereNovoCliente(Cliente cliente) throws SQLException {
		PreparedStatement stmt = con.prepareStatement(
				"INSERT INTO CLIENTE (CPF,NOME,SOBRENOME,DATA_NASCIMENTO,SEXO,EMAIL,NOME_USUARIO,SENHA) "
						+ "VALUES (?,?,?,?,?,?,?,?)");
		try {
			stmt.setInt(1, Integer.parseInt(cliente.getCpf().toString()));
			stmt.setString(2, cliente.getNome().toString());
			stmt.setString(3, cliente.getSobrenome().toString());
			stmt.setDate(4, new java.sql.Date(cliente.getDataNascimento().getTime()));
			String sexo;
			if (cliente.getSexo() == Sexo.Masculino) {
				sexo = "M";
			} else {
				sexo = "F";
			}
			stmt.setString(5, sexo);
			stmt.setString(6, cliente.getEmail().toString());
			stmt.setString(7, cliente.getUsuario().toString());
			stmt.setString(8, cliente.getSenha().toString());
			stmt.execute();
		} finally {
			stmt.close();
		}
	}

	public Cliente get(String cpf) throws SQLException {
		Cliente cliente;
		PreparedStatement stmt = con
				.prepareStatement("SELECT NOME,SOBRENOME,DATA_NASCIMENTO,SEXO,EMAIL,NOME_USUARIO,SENHA "
						+ "FROM CLIENTE " + "WHERE CPF = ?");
		stmt.setInt(1, Integer.parseInt(cpf));
		ResultSet rs = stmt.executeQuery();
		try {
			if (rs.next()) {
				Nome nome = new Nome(rs.getString(1));
				Sobrenome sobrenome = new Sobrenome(rs.getString(2));
				Date dataNascimento = rs.getDate(3);
				String sexoStr = rs.getString(4);
				Sexo sexo;
				if (sexoStr.equals("M")) {
					sexo = Sexo.Masculino;
				} else {
					sexo = Sexo.Feminino;
				}
				Email email = new Email(rs.getString(5));
				NomeUsuario nomeUsuario = new NomeUsuario(rs.getString(6));
				Senha senha = new Senha(rs.getString(7));
				cliente = new Cliente(new Cpf(cpf), nome, sobrenome, dataNascimento, sexo, email, nomeUsuario, senha);
				return cliente;
			} else
				return null;
		} finally {
			rs.close();
			stmt.close();
		}
	}

	public void remove(String cpf) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("DELETE FROM CLIENTE WHERE CPF = ?");
		stmt.setInt(1, Integer.parseInt(cpf));
		stmt.execute();
		stmt.close();
	}

	public Cliente getPorLogin(String idUsuario) throws SQLException {
		Cliente cliente;
		PreparedStatement stmt = con.prepareStatement("SELECT CPF, NOME, SOBRENOME, DATA_NASCIMENTO, SEXO, EMAIL"
				+ "FROM CLIENTE " + "WHERE NOME_USUARIO = ?");
		stmt.setString(1, idUsuario);
		ResultSet rs = stmt.executeQuery();
		try {
			if (rs.next()) {
				Cpf cpf = new Cpf(rs.getString(1));
				Nome nome = new Nome(rs.getString(2));
				Sobrenome sobrenome = new Sobrenome(rs.getString(3));
				Date dataNascimento = rs.getDate(4);
				String sexoStr = rs.getString(5);
				Sexo sexo;
				if (sexoStr == "M") {
					sexo = Sexo.Masculino;
				} else {
					sexo = Sexo.Feminino;
				}
				Email email = new Email(rs.getString(6));
				NomeUsuario nomeUsuario = new NomeUsuario(idUsuario);
				Senha senha = new Senha(rs.getString(7));
				cliente = new Cliente(cpf, nome, sobrenome, dataNascimento, sexo, email, nomeUsuario, senha);
				return cliente;
			} else
				return null;
		} finally {
			rs.close();
			stmt.close();
		}
	}
}
