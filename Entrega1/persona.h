#ifndef PERSONA_H
#define PERSONA_H 

#include <string>

using namespace std;

class Persona{
	
    private:
 
		string numeroIdentificacion;
		string nombre;
		string direccion;
		string ciudad;
		long telefono;
		
	public:
		//constructores
		Persona();
		Persona(string numeroIdentificacion, string nombre, string direccion, string ciudad, long telefono);
		//getters
		string getNumeroIdentificacion();
		string getNombre();
		string getDireccion();
		string getCiudad();
		long getTelefono;
		//setters
		void setNumeroIdentificacion(string numeroIdentificacion);
		void setNombre(string nombre);
		void setDireccion(string direccion);
		void setCiudad(string ciudad);
		void setTelefono(long telefono);
 
	private:
		
	
};

#endif