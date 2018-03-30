#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>

class RegionReparto{
	
    private:
 
		std::string codigo;
		std::string nombre;
		
	public:
		//constructor
		RegionReparto();
		RegionReparto(std::string codigo, std::string nombre);
		//getters
		std::string getCodigo();
		std::string getNombre();
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);
 
	private:	
		
	
};

#include "region_reparto.hxx"

#endif