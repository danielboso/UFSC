package mapeadores;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import modelo.Endereco;
import modelo.atributos.Bairro;
import modelo.atributos.Cep;
import modelo.atributos.Cidade;
import modelo.atributos.Complemento;
import modelo.atributos.Estado;
import modelo.atributos.Numero;
import modelo.atributos.Pais;
import modelo.atributos.Rua;

public class MapeadorEndereco {

	private Connection con;

	public MapeadorEndereco(Connection con) {
		this.con = con;
	}

	public void insereNovoEndereco(Endereco endereco) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("INSERT INTO ENDERECO (PAIS,ESTADO,CIDADE,CEP,BAIRRO,RUA,NUMERO,COMPLEMENTO) " + 
													  "VALUES (?,?,?,?,?,?,?,?)");
		try {
			stmt.setString(1, endereco.getPais().toString());
			stmt.setString(2, endereco.getEstado().toString());
			stmt.setString(3, endereco.getCidade().toString());
			stmt.setInt   (4, Integer.parseInt(endereco.getCep().toString()));
			stmt.setString(5, endereco.getBairro().toString());
			stmt.setString(6, endereco.getRua().toString());
			stmt.setInt   (7, Integer.parseInt(endereco.getNumero().toString()));
			stmt.setString(8, endereco.getComplemento().toString());
			stmt.execute();
		} finally {
			stmt.close();
		}
	}
	
	public Endereco get(Integer idEndereco) throws SQLException {
		Endereco endereco;
		PreparedStatement stmt = con.prepareStatement("SELECT PAIS,ESTADO,CIDADE,CEP,BAIRRO,RUA,NUMERO,COMPLEMENTO " +
													  "FROM ENDERECO " + "WHERE ID_ENDERECO = ?");
		stmt.setInt(1, idEndereco);
		ResultSet rs = stmt.executeQuery();
		try {
			if(rs.next()) {
				Pais pais = new Pais(rs.getString(1));
				Estado estado = new Estado(rs.getString(2));
				Cidade cidade = new Cidade(rs.getString(3));
				Cep cep = new Cep(rs.getString(4));
				Bairro bairro = new Bairro(rs.getString(5));
				Rua rua = new Rua(rs.getString(6));
				Numero numero = new Numero(rs.getString(7));
				Complemento complemento = new Complemento(rs.getString(8));
				endereco = new Endereco(pais, estado, cidade, cep, bairro, rua, numero, complemento);
				endereco.setId(idEndereco);
				return endereco;
			} else {
				return null;
			}
		} finally {
			rs.close();
			stmt.close();
		}
	}
	
	public void remove(Integer idEndereco) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("DELETE FROM ENDERECO WHERE ID_CLIENTE = ?");
		stmt.setString(1, idEndereco.toString());
		stmt.execute();
		stmt.close();
	}
}
