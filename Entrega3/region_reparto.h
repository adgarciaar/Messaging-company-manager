#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>

class RegionReparto{
	
    private:
 
		std::string codigo;
		std::string nombre;
		int distanciaAOficinaPadre;
		
	public:
		//constructor
		RegionReparto();
		RegionReparto(std::string codigo, std::string nombre, int distanciaAOficinaPadre);
		//getters
		std::string getCodigo();
		std::string getNombre();
		int getdDistanciaAOficinaPadre();
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);
		void setDistanciaAOficinaPadre(int distanciaAOficinaPadre);
	
};

#include "region_reparto.hxx"

#endif