#include "oficina_reparto.h"

OficinaReparto::OficinaReparto(string codigo, string nombre, string direccion, string ciudad){
	this->codigo = codigo;
	this->nombre = nombre;
	this->direccion = direccion;
	this->ciudad = ciudad;
}

//getters

string getCodigo(){
	return this->codigo;
}

string getNombre(){
	return this->nombre;
}

string getDireccion(){
	return this->direccion;
}

string getCiudad(){
	return this->ciudad
}

list<RegionReparto> getRegiones(){
	return this->regiones;
}
		
//setters
		
void setCodigo(string codigo){
	this->codigo = codigo;
}

void setNombre(string nombre){
	this->nombre = nombre;
}

void setDireccion(string direccion){
	this->direccion = direccion;
}

void setCiudad(string ciudad){
	this->ciudad = ciudad;
}

void setRegiones(list<RegionReparto> regiones){
	this->regiones = regiones;
}