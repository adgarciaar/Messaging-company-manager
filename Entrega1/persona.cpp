#include "persona.h" 

#include <string>

using namespace std;

Persona::Persona(){}

Persona::Persona(string numeroIdentificacion, string nombre, string direccion, string ciudad, long telefono){
	this->numeroIdentificacion = numeroIdentificacion;
	this->nombre = nombre;
	this->direccion = direccion;
	this->ciudad = ciudad;
	this->telefono = telefono;
}

//getters

string Persona::getNumeroIdentificacion(){
	return this->numeroIdentificacion;
}

string Persona::getNombre(){
	return this->nombre;
}

string Persona::getDireccion(){
	return this->direccion;
}

string Persona::getCiudad(){
	return this->ciudad;
}

long Persona::getTelefono(){
	return this->telefono;
}
		
//setters

void Persona::setNumeroIdentificacion(string numeroIdentificacion){
	this->numeroIdentificacion = numeroIdentificacion;
}

void Persona::setNombre(string nombre){
	this->nombre = nombre;
}

void Persona::setDireccion(string direccion){
	this->direccion = direccion;
}

void Persona::setCiudad(string ciudad){
	this->ciudad = ciudad;
}

void Persona::setTelefono(long telefono){
	this->telefono = telefono;
}