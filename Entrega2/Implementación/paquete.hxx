#include "paquete.h" 
#include <string>

using namespace std;

//constructor

Paquete::Paquete(){}

Paquete::Paquete(std::string remitente, std::string destinatario, int peso, string tipoContenido, string numeroGuia,
	std::string oficinaReparto, std::string regionReparto){
	this->remitente = remitente;
	this->destinatario = destinatario;
	this->peso = peso;
	this->tipoContenido = tipoContenido;
	this->numeroGuia = numeroGuia;
	this->oficinaReparto = oficinaReparto;
	this->regionReparto = regionReparto;
}

//getters

std::string Paquete::getRemitente(){
	return this->remitente;
}

std::string Paquete::getDestinatario(){
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

std::string Paquete::getOficinaReparto(){
	return this->oficinaReparto;
}

std::string Paquete::getRegionReparto(){
	return this->regionReparto;
}
		
//setters

void Paquete::setRemitente(std::string remitente){
	this->remitente = remitente;
}

void Paquete::setDestinatario(std::string destinatario){
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

void Paquete::setOficinaReparto(std::string oficinaReparto){
	this->oficinaReparto = oficinaReparto;
}

void Paquete::setRegionReparto(std::string regionReparto){
	this->regionReparto = regionReparto;
}