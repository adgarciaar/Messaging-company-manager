#include "lugar_reparto.h"

#include <string>

using namespace std;

//constructor

LugarReparto::LugarReparto(){}

//destructor

LugarReparto::~LugarReparto(){}

//getters

string LugarReparto::getCodigo(){
	return this->codigo;
}

string LugarReparto::getNombre(){
	return this->nombre;
}

//setters

void LugarReparto::setCodigo(string codigo){
	this->codigo = codigo;
}

void LugarReparto::setNombre(string nombre){
	this->nombre = nombre;
}