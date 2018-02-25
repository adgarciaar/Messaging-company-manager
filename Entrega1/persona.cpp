#include "persona.h" 

#include <string>

using namespace std;

Persona::Persona(){}

Persona::Persona(string numeroIdentificacion, string nombre, string apellidos, string direccion, string ciudad, string telefono){
	this->numeroIdentificacion = numeroIdentificacion;
	this->nombre = nombre;
	this->apellidos = apellidos;
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

string Persona::getApellidos(){
	return this->apellidos;
}

string Persona::getDireccion(){
	return this->direccion;
}

string Persona::getCiudad(){
	return this->ciudad;
}

string Persona::getTelefono(){
	return this->telefono;
}
		
//setters

void Persona::setNumeroIdentificacion(string numeroIdentificacion){
	this->numeroIdentificacion = numeroIdentificacion;
}

void Persona::setNombre(string nombre){
	this->nombre = nombre;
}

void Persona::setApellidos(string apellidos){
	this->apellidos = apellidos;
}

void Persona::setDireccion(string direccion){
	this->direccion = direccion;
}

void Persona::setCiudad(string ciudad){
	this->ciudad = ciudad;
}

void Persona::setTelefono(string telefono){
	this->telefono = telefono;
}