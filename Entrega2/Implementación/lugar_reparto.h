#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>

//abstract class
class LugarReparto{
	
    private:
 
		std::string codigo;
		std::string nombre;
		
	public:
		//constructor
		LugarReparto();
		//getters
		std::string getCodigo();
		std::string getNombre();
		//setters
		void setCodigo(std::string codigo);
		void setNombre(std::string nombre);		
		//destructor
		virtual ~LugarReparto() = 0;  //pure virtual function
	
};

#include "lugar_reparto.hxx"

#endif