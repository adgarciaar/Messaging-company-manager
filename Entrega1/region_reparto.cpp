# include "region_reparto.h"

#include <string>

using namespace std;

RegionReparto::RegionReparto(){}

RegionReparto::RegionReparto(string codigo, string nombre){
	this->codigo = codigo;
	this->nombre = nombre;
}

//getters

string RegionReparto::getCodigo(){
	return this->codigo;
}

string RegionReparto::getNombre(){
	return this->nombre;
}

//setters

void RegionReparto::setCodigo(string codigo){
	this->codigo = codigo;
}

void RegionReparto::setNombre(string nombre){
	this->nombre = nombre;
}