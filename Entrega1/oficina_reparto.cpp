#include "oficina_reparto.h"
#include <string>

using namespace std;

OficinaReparto::OficinaReparto(){}

OficinaReparto::OficinaReparto(string codigo, string nombre, string direccion, string ciudad){
	this->codigo = codigo;
	this->nombre = nombre;
	this->direccion = direccion;
	this->ciudad = ciudad;
}

//getters

string OficinaReparto::getCodigo(){
	return this->codigo;
}

string OficinaReparto::getNombre(){
	return this->nombre;
}

string OficinaReparto::getDireccion(){
	return this->direccion;
}

string OficinaReparto::getCiudad(){
	return this->ciudad;
}

list<RegionReparto> OficinaReparto::getRegiones(){
	return this->regiones;
}
		
//setters
		
void OficinaReparto::setCodigo(string codigo){
	this->codigo = codigo;
}

void OficinaReparto::setNombre(string nombre){
	this->nombre = nombre;
}

void OficinaReparto::setDireccion(string direccion){
	this->direccion = direccion;
}

void OficinaReparto::setCiudad(string ciudad){
	this->ciudad = ciudad;
}

void OficinaReparto::setRegiones(list<RegionReparto> regiones){
	this->regiones = regiones;
}