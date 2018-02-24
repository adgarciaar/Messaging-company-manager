#include "paquete.h" 
#include "persona.h"
#include <string>

using namespace std;

//constructor

Paquete::Paquete(){}

Paquete::Paquete(Persona remitente, Persona destinatario, int peso, string tipoContenido, string numeroGuia){
	this->remitente = remitente;
	this->destinatario = destinatario;
	this->peso = peso;
	this->tipoContenido = tipoContenido;
	this->numeroGuia = numeroGuia;
}

//getters

Persona Paquete::getRemitente(){
	return this->remitente;
}

Persona Paquete::getDestinatario(){
	return this->destinatario;
}

int Paquete::getPeso(){
	return this->peso;
}

string Paquete::getTipoContenido(){
	return this->tipoContenido;
}

string Paquete::getNumeroGuia(){
	return this->numeroGuia;
}
		
//setters

void Paquete::setRemitente(Persona remitente){
	this->remitente = remitente;
}

void Paquete::setDestinatario(Persona destinatario){
	this->destinatario = destinatario;
}

void Paquete::setPeso(int peso){
	this->peso = peso;
}

void Paquete::setTipoContenido(string tipoContenido){
	this->tipoContenido = tipoContenido;
}

void Paquete::setNumeroGuia(string numeroGuia){
	this->numeroGuia = numeroGuia;
}