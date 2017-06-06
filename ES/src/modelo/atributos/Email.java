package modelo.atributos;

import excecoes.ExcecaoEntradaInvalida;
import excecoes.ExcecaoEntradaNaoPermitida;

public class Email {
	
	private String email;
	
	public Email(String email) {
		this.email = email;
	}

	public void verificaExcecoes() throws ExcecaoEntradaInvalida, ExcecaoEntradaNaoPermitida {
		if (email.length() <= 6) {
			throw new ExcecaoEntradaNaoPermitida();
		}
		
		String parteEmailVerificarPresencaArroba = email.substring(0,
				email.length() - 4);
		if (!email.substring(email.length() - 4, email.length())
				.equals(".com")) {
			throw new ExcecaoEntradaInvalida();
		}
		
		verificaArroba(parteEmailVerificarPresencaArroba);

		if (!verificaSeTemArrobaEstaCorreto(parteEmailVerificarPresencaArroba)) {
			throw new ExcecaoEntradaInvalida();
		}
	}
	
	private void verificaArroba(String parteEmailVerificarPresencaArroba) throws ExcecaoEntradaInvalida {
		Integer contadorNumeroArroba = 0;
		for (int contador = 0; contador < parteEmailVerificarPresencaArroba
				.length(); contador++) {
			if (parteEmailVerificarPresencaArroba.charAt(contador) == '@') {
				contadorNumeroArroba++;
			}
		}

		if (contadorNumeroArroba > 1) {
			throw new ExcecaoEntradaInvalida();
		}
	}

	private boolean verificaSeTemArrobaEstaCorreto(
			String parteEmailASerConferido) {
		boolean comecaComArroba = true;
		boolean terminaComArroba = true;
		boolean temArroba = false;
		if (!parteEmailASerConferido.substring(0, 1).equals("@")) {
			comecaComArroba = false;
		}
		if (!parteEmailASerConferido.endsWith("@")) {
			terminaComArroba = false;
		}
		if (!(parteEmailASerConferido.indexOf("@") == -1)) {
			temArroba = true;
		}
		return !comecaComArroba && !terminaComArroba && temArroba;
	}
	
	@Override
	public String toString() {
		return email;
	}
}	