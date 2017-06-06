package modelo;

import modelo.atributos.Senha;

public class Comparador {

	public Comparador() {

	}

	public static boolean compararSenhasSaoIguais(Senha senha,
			Senha senhaRepetida) {
		if (senha.toString().equals(senhaRepetida.toString())) {
			return true;
		}
		return false;
	}
}