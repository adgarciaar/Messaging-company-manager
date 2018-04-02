#include "oficina_reparto.h"
#include <string>

using namespace std;

//constructor

OficinaReparto::OficinaReparto(string codigo, string nombre, string direccion, string ciudad){
	this->codigo = codigo;
	this->nombre = nombre;
	this->direccion = direccion;
	this->ciudad = ciudad;
}

//destructor

OficinaReparto::~OficinaReparto(){}

//getters

string OficinaReparto::getDireccion(){
	return this->direccion;
}

string OficinaReparto::getCiudad(){
	return this->ciudad;
}
		
//setters

void OficinaReparto::setDireccion(string direccion){
	this->direccion = direccion;
}

void OficinaReparto::setCiudad(string ciudad){
	this->ciudad = ciudad;
}