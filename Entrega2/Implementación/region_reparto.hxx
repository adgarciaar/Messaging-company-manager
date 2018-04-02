#include "region_reparto.h"

#include <string>

using namespace std;

//constructor
RegionReparto::RegionReparto(string codigo, string nombre){
	this->codigo = codigo;
	this->nombre = nombre;
}

//destructor
RegionReparto::~RegionReparto(){}