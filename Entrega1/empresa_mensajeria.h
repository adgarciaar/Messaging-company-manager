#ifndef EMPRESA_MENSAJERIA_H
#define EMPRESA_MENSAJERIA_H 

#include <string>
#include <list>
#include <queue>
#include "oficina_reparto.h"

using namespace std;

class EmpresaMensajeria{
	
    private:
	
		string nombre;
		list<OficinaReparto> oficinas;
		queue<> paquetes;
		list<Persona> personas;
		
	public:
		EmpresaMensajeria(string nombre);
 
	private:
	
		void cargarPersonas(string nombreArchivo);
		void cargarPaquetes(string nombreArchivo);
		void registrarPersona();
		void registrarPaquete();
		long conteoPaquetes();
	
};

#endif