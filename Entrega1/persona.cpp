#include "persona.h" 

Persona::Persona(string numeroIdentificacion, string nombre, string direccion, string ciudad, long telefono){
	this->numeroIdentificacion = numeroIdentificacion;
	this->nombre = nombre;
	this->direccion = direccion;
	this->ciudad = ciudad;
	this->telefono = telefono;
}

//getters

string getNumeroIdentificacion(){
	return this->numeroIdentificacion;
}

string getNombre(){
	return this->nombre;
}

string getDireccion(){
	return this->direccion;
}

string getCiudad(){
	return this->ciudad;
}

long getTelefono{
	return this->telefono;
}
		
//setters

void setNumeroIdentificacion(string numeroIdentificacion){
	this->numeroIdentificacion = numeroIdentificacion;
}

void setNombre(string nombre){
	this->nombre = nombre;
}

void setDireccion(string direccion){
	this->direccion = direccion;
}

void setCiudad(string ciudad){
	this->ciudad = ciudad;
}

void setTelefono(long telefono){
	this->telefono = telefono;
}