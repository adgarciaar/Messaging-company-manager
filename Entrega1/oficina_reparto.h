#ifndef OFICINA_REPARTO_H
#define OFICINA_REPARTO_H 

#include <string>
#include <list>
#include "region_reparto.h"

using namespace std;

class OficinaReparto{
	
    private:
 
		string codigo;
		string nombre;
		string direccion;
		string ciudad;
		list<RegionReparto> regiones;
		
	public:
		//constructores
		OficinaReparto();
		OficinaReparto(string codigo, string nombre, string direccion, string ciudad);
		//getters
		string getCodigo();
		string getNombre();
		string getDireccion();
		string getCiudad();
		list<RegionReparto> getRegiones();
		//setters
		void setCodigo(string codigo);
		void setNombre(string nombre);
		void setDireccion(string direccion);
		void setCiudad(string ciudad);
		void setRegiones(list<RegionReparto> regiones);
 
	private:
	
		
	
};

#endif