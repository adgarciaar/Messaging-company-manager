#ifndef EMPRESA_MENSAJERIA_H
#define EMPRESA_MENSAJERIA_H 

#include <string>
#include <list>
#include <queue>
#include "oficina_reparto.h"
#include "persona.h"
#include "paquete.h"

class EmpresaMensajeria{
	
    private:
	
		std::string nombre;
		std::list<OficinaReparto> oficinas;
		std::queue<Paquete> paquetes;
		std::list<Persona> personas;
		
	public:
		EmpresaMensajeria();
		EmpresaMensajeria(std::string nombre);
		
		void cargarPersonas(std::string nombreArchivo);
		void cargarPaquetes(std::string nombreArchivo);
		void registrarPersona();
		void registrarPaquete();
		long conteoPaquetes();

};

#endif