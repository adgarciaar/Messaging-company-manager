#ifndef EMPRESA_MENSAJERIA_H
#define EMPRESA_MENSAJERIA_H 

#include <string>
#include <list>
#include <queue>
#include "oficina_reparto.h"

using namespace std;

class Paquete{
	
    private:
	
		list<OficinaReparto> oficinas;
		queue<> paquetes;
		list<Persona> personas;
 
	private:
	
		void cargarPersonas(string nombreArchivo);
		void cargarPaquetes(string nombreArchivo);
		void registrarPersona();
		void registrarPaquete();
		long conteoPaquetes();
	
};

#endif