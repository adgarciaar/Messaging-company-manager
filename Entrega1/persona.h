#ifndef PERSONA_H
#define PERSONA_H 

#include <string>

class Persona{
	
    private:
 
		std::string numeroIdentificacion;
		std::string nombre;
		std::string apellidos;
		std::string direccion;
		std::string ciudad;
		std::string telefono;
		
	public:
		//constructor
		Persona();
		Persona(std::string numeroIdentificacion, std::string nombre, std::string apellidos, std::string direccion, std::string ciudad, std::string telefono);
		//getters
		std::string getNumeroIdentificacion();
		std::string getNombre();
		std::string getApellidos();
		std::string getDireccion();
		std::string getCiudad();
		std::string getTelefono();
		//setters
		void setNumeroIdentificacion(std::string numeroIdentificacion);
		void setNombre(std::string nombre);
		void setApellidos(std::string apellidos);
		void setDireccion(std::string direccion);
		void setCiudad(std::string ciudad);
		void setTelefono(std::string telefono);
 
	private:
		
	
};

#endif