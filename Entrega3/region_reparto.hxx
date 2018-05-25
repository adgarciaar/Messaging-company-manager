# include "region_reparto.h"

#include <string>

using namespace std;

RegionReparto::RegionReparto(){}

RegionReparto::RegionReparto(string codigo, string nombre, float distanciaAOficinaPadre){
	this->codigo = codigo;
	this->nombre = nombre;
	this->distanciaAOficinaPadre = distanciaAOficinaPadre;
}

//getters

string RegionReparto::getCodigo(){
	return this->codigo;
}

string RegionReparto::getNombre(){
	return this->nombre;
}

float RegionReparto::getDistanciaAOficinaPadre(){
	return this->distanciaAOficinaPadre;
}

//setters

void RegionReparto::setCodigo(string codigo){
	this->codigo = codigo;
}

void RegionReparto::setNombre(string nombre){
	this->nombre = nombre;
}

void RegionReparto::setDistanciaAOficinaPadre(float distanciaAOficinaPadre){
	this->distanciaAOficinaPadre = distanciaAOficinaPadre;
}