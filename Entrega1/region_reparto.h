#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>

using namespace std;

class OficinaReparto{
	
    private:
 
		string codigo;
		string nombre;
		
	public:
		//constructores
		OficinaReparto();
		OficinaReparto(string codigo, string nombre);
		//getters
		string getCodigo();
		string getNombre();
		//setters
		void setCodigo(string codigo);
		void setNombre(string nombre);
 
	private:	
		
	
};

#endif