#ifndef OFICINA_REPARTO_H
#define OFICINA_REPARTO_H 

#include <string>
#include <list>
#include "lugar_reparto.h"
#include "region_reparto.h"

class OficinaReparto : public LugarReparto{
	
    private:
 
		std::string direccion;
		std::string ciudad;
		
	public:
		//constructor
		OficinaReparto(std::string codigo, std::string nombre, std::string direccion, std::string ciudad);
		//destructor
		~OficinaReparto();
		//getters
		std::string getDireccion();
		std::string getCiudad();
		//setters
		void setDireccion(std::string direccion);
		void setCiudad(std::string ciudad);
	
};

#include "oficina_reparto.hxx"

#endif