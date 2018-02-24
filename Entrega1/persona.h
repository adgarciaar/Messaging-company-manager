#ifndef PERSONA_H
#define PERSONA_H 

#include <string>

class Persona{
	
    private:
 
		std::string numeroIdentificacion;
		std::string nombre;
		std::string direccion;
		std::string ciudad;
		long telefono;
		
	public:
		//constructor
		Persona();
		Persona(std::string numeroIdentificacion, std::string nombre, std::string direccion, std::string ciudad, long telefono);
		//getters
		std::string getNumeroIdentificacion();
		std::string getNombre();
		std::string getDireccion();
		std::string getCiudad();
		long getTelefono();
		//setters
		void setNumeroIdentificacion(std::string numeroIdentificacion);
		void setNombre(std::string nombre);
		void setDireccion(std::string direccion);
		void setCiudad(std::string ciudad);
		void setTelefono(long telefono);
 
	private:
		
	
};

#endif