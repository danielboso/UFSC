package testes;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import modelo.Endereco;
import modelo.Fachada;
import modelo.atributos.Bairro;
import modelo.atributos.Cep;
import modelo.atributos.Cidade;
import modelo.atributos.Complemento;
import modelo.atributos.Estado;
import modelo.atributos.Numero;
import modelo.atributos.Pais;
import modelo.atributos.Rua;

public class TesteEndereco {
	
	Fachada fachada = new Fachada();
	
	Endereco endereco1;
	Endereco endereco2;
	
	@Before public void cadastros() {
		fachada.apagaTodosDadosDoBD();
		
		cadastraEndereco1();
		cadastraEndereco2();
	}
	
	public void cadastraEndereco1() {
		Pais pais = new Pais("Pais1");
		Estado estado = new Estado("Estado1");
		Cidade cidade = new Cidade("Cidade1");
		Cep cep = new Cep("1");
		Bairro bairro = new Bairro("Bairro1");
		Rua rua = new Rua("Rua1");
		Numero numero = new Numero("11");
		Complemento complemento = new Complemento("Complemento1");
		Endereco endereco1 = new Endereco(pais, estado, cidade, cep, bairro, rua, numero, complemento);
		fachada.cadastrarEndereco(endereco1);
		
		this.endereco1 = fachada.retornaEndereco(1);
	}
	
	public void cadastraEndereco2() {
		Pais pais = new Pais("Pais2");
		Estado estado = new Estado("Estado2");
		Cidade cidade = new Cidade("Cidade2");
		Cep cep = new Cep("2");
		Bairro bairro = new Bairro("Bairro2");
		Rua rua = new Rua("Rua2");
		Numero numero = new Numero("12");
		Complemento complemento = new Complemento("Complemento2");
		Endereco endereco2 = new Endereco(pais, estado, cidade, cep, bairro, rua, numero, complemento);
		fachada.cadastrarEndereco(endereco2);
		
		this.endereco2 = fachada.retornaEndereco(2);
	}
	
	@Test public void recuperaPaisEndereco1() {
		assertEquals("Pais1", endereco1.getPais().toString());
	}
	@Test public void recuperaEstadoEndereco1() {
		assertEquals("Estado1", endereco1.getEstado().toString());
	}
	@Test public void recuperaCidadeEndereco1() {
		assertEquals("Cidade1", endereco1.getCidade().toString());
	}
	@Test public void recuperaCepEndereco1() {
		assertEquals("1", endereco1.getCep().toString());
	}
	@Test public void recuperaBairroEndereco1() {
		assertEquals("Bairro1", endereco1.getBairro().toString());
	}
	@Test public void recuperaRuaEndereco1() {
		assertEquals("Rua1", endereco1.getRua().toString());
	}
	@Test public void recuperaNumeroEndereco1() {
		assertEquals("11", endereco1.getNumero().toString());
	}
	@Test public void recuperaComplementoEndereco1() {
		assertEquals("Complemento1", endereco1.getComplemento().toString());
	}
	
	@Test public void recuperaPaisEndereco2() {
		assertEquals("Pais2", endereco2.getPais().toString());
	}
	@Test public void recuperaEstadoEndereco2() {
		assertEquals("Estado2", endereco2.getEstado().toString());
	}
	@Test public void recuperaCidadeEndereco2() {
		assertEquals("Cidade2", endereco2.getCidade().toString());
	}
	@Test public void recuperaCepEndereco2() {
		assertEquals("2", endereco2.getCep().toString());
	}
	@Test public void recuperaBairroEndereco2() {
		assertEquals("Bairro2", endereco2.getBairro().toString());
	}
	@Test public void recuperaRuaEndereco2() {
		assertEquals("Rua2", endereco2.getRua().toString());
	}
	@Test public void recuperaNumeroEndereco2() {
		assertEquals("12", endereco2.getNumero().toString());
	}
	@Test public void recuperaComplementoEndereco2() {
		assertEquals("Complemento2", endereco2.getComplemento().toString());
	}
}
