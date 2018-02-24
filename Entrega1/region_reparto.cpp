# include "region_reparto.h"

OficinaReparto::OficinaReparto(string codigo, string nombre){
	this->codigo = codigo;
	this->nombre = nombre;
}

//getters

string getCodigo(){
	return this->codigo;
}

string getNombre(){
	return this->nombre;
}

//setters

void setCodigo(string codigo){
	this->codigo = codigo;
}

void setNombre(string nombre){
	this->nombre = nombre;
}