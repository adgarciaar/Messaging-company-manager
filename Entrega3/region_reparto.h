#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>

class RegionReparto{
	
    private:
 
		std::string codigo;
		std::string nombre;
		float distanciaAOficinaPadre;
		
	public:
		//constructor
		RegionReparto();
		RegionReparto(std::string codigo, std::string nombre, float distanciaAOficinaPadre);
		//getters
		std::string getCodigo();
		std::string getNombre();
		float getDistanciaAOficinaPadre();
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);
		void setDistanciaAOficinaPadre(float distanciaAOficinaPadre);
	
};

#include "region_reparto.hxx"

#endif