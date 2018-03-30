#ifndef OFICINA_REPARTO_H
#define OFICINA_REPARTO_H 

#include <string>
#include <list>
#include "region_reparto.h"

class OficinaReparto{
	
    private:
 
		std::string codigo;
		std::string nombre;
		std::string direccion;
		std::string ciudad;
		std::list<RegionReparto> regiones;
		
	public:
		//constructor
		OficinaReparto();
		OficinaReparto(std::string codigo, std::string nombre, std::string direccion, std::string ciudad);
		//getters
		std::string getCodigo();
		std::string getNombre();
		std::string getDireccion();
		std::string getCiudad();
		std::list<RegionReparto> getRegiones();
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);
		void setDireccion(std::string direccion);
		void setCiudad(std::string ciudad);
		void setRegiones(std::list<RegionReparto> regiones);
		
		void agregarRegion(RegionReparto regionReparto);
 
	private:	
	
};

#include "oficina_reparto.hxx"

#endif