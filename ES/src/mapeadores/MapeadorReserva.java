package mapeadores;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import modelo.propriedade.Reserva;

public class MapeadorReserva {
	
	private Connection con;
	
	public MapeadorReserva(Connection con) {
		this.con = con;
	}
	
	public void insereNovaReserva(Reserva reserva) throws SQLException {
		PreparedStatement stmt = con.prepareStatement("INSERT INTO RESERVA (ID_PROPRIEDADE, ID_CLIENTE, INICIO, FIM) " +
				  "VALUES(?,?,?,?)");
		try {
			stmt.setInt (1, reserva.getIdPropriedade());
			stmt.setInt (2, reserva.getIdCliente());
			stmt.setDate(2, new java.sql.Date(reserva.getInicio().getTime()));
			stmt.setDate(3, new java.sql.Date(reserva.getFim().getTime()));
			stmt.execute();
		} finally {
			stmt.close();
		}
	}
	
	public Reserva get(Integer idReserva) {
		
	}
	
}
