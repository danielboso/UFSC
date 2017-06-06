package mapeadores;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import modelo.Endereco;
import modelo.propriedade.Propriedade;

public class MapeadorPropriedade {
	
	private Connection con;
	
	private MapeadorEndereco mapeadorEndereco;
	
	public MapeadorPropriedade(Connection con) {
		this.con = con;
		this.mapeadorEndereco = new MapeadorEndereco(this.con);
	}
	
	public void insereNovaPropriedade(Propriedade propriedade) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("INSERT INTO PROPRIEDADE (ID_PROPRIETARIO, ID_ENDERECO, DESCRICAO, CAPACIDADE, PRECO_DIARIA, AREA) " +
													  "VALUES(?,?,?,?,?,?)");
		try {
			stmt.setInt   (1, propriedade.getIDProprietario());
			stmt.setInt   (2, propriedade.getEndereco().getId());
			stmt.setString(3, propriedade.getDescricao());
			stmt.setInt   (4, propriedade.getCapacidade());
			stmt.setInt   (5, propriedade.getPrecoDiaria());
			stmt.setInt	  (6, propriedade.getArea());
			stmt.execute();
		} finally {
			stmt.close();
		}
	}
	
	public Propriedade get(Integer idPropriedade) throws SQLException {
		Propriedade propriedade;
		PreparedStatement stmt = con.prepareStatement("SELECT ID_PROPRIETARIO, ID_ENDERECO, DESCRICAO, CAPACIDADE, PRECO_DIARIA, AREA " + 
													  "FROM PROPRIEDADE " + "WHERE ID_PROPRIEDADE = ?");
		stmt.setInt(1, idPropriedade);
		ResultSet rs = stmt.executeQuery();
		try {
			if(rs.next()) {
				Integer idProprietario = rs.getInt(1);
				Endereco endereco = mapeadorEndereco.get(rs.getInt(2));
				String descricao = rs.getString(3);
				Integer capacidade = rs.getInt(4);
				Integer precoDiaria = rs.getInt(5);
				Integer area = rs.getInt(6);
				propriedade = new Propriedade(idPropriedade, idProprietario, descricao, capacidade, precoDiaria, area, endereco);
				return propriedade;
			} else {
				return null;
			}
		} finally {
			rs.close();
			stmt.close();
		}
	}
	
	public void remove(Integer idPropriedade) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("DELETE FROM ENDERECO WHERE ID_PROPRIEDADE = ?");
		stmt.setInt(1, idPropriedade);
		stmt.execute();
	}
}
