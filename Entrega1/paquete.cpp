#include "paquete.h" 

//constructor
Paquete::Paquete(Persona remitente, Persona destinatario, int peso, string tipoContenido, string numeroGuia){
	this->remitente = remitente;
	this->destinatario = destinatario;
	this->peso = peso;
	this->tipoContenido = tipoContenido;
	this->numeroGuia = numeroGuia;
}

//getters

Persona getRemitente(){
	return this->remitente;
}

Persona getDestinatario(){
	return this->destinatario;
}

int getPeso(){
	return this->peso;
}

string getTipoContenido(){
	return this->tipoContenido;
}

string getNumeroGuia(){
	return this->numeroGuia;
}
		
//setters

void setRemitente(Persona remitente){
	this->remitente = remitente;
}

void setDestinatario(Persona destinatario){
	this->destinatario = destinatario;
}

void setPeso(int peso){
	this->peso = peso;
}

void setTipoContenido(string tipoContenido){
	this->tipoContenido = tipoContenido;
}

void setNumeroGuia(string numeroGuia){
	this->numeroGuia = numeroGuia;
}