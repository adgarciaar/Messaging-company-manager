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
		list<RegionReparto> regiones;
		
	public:
		//constructor
		OficinaReparto();
		OficinaReparto(std::string codigo, std::string nombre, std::string direccion, std::string ciudad);
	
		//getters
		std::string getCodigo();
		std::string getNombre();
		std::string getDireccion();
		std::string getCiudad();
		list<RegionReparto> getRegiones();
	
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);
		void setDireccion(std::string direccion);
		void setCiudad(string std::ciudad);
		void setRegiones(list<RegionReparto> regiones);
		
		//funciones
		void agregarRegion(RegionReparto regionReparto);
 
	private:	
	
};

#endif
