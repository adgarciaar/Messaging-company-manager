#ifndef EMPRESA_MENSAJERIA_H
#define EMPRESA_MENSAJERIA_H 

#include <string>
#include <queue>
#include "lugar_reparto.h"
#include "oficina_reparto.h"
#include "region_reparto.h"
#include "persona.h"
#include "paquete.h"
#include "Arbol.h"

class EmpresaMensajeria{
	
    private:
	
		std::string nombre;
		Arbol< LugarReparto* > arbol; //almacena jerarquía de oficinas y regiones
		std::queue<Paquete> paquetes;
		std::list<Persona> personas;
		
	public:
	
		EmpresaMensajeria();
		EmpresaMensajeria(std::string nombre);
		
		void cargarPersonas(std::string nombreArchivo);		
		void cargarPaquetes(std::string nombreArchivo);		
		//--------------------------------------------------------------------------------------------------------------------------
		void registrarPersona(std::string numeroIdentificacion, std::string nombre, std::string apellidos, 
			std::string direccion, std::string ciudad, std::string telefono);
		//--------------------------------------------------------------------------------------------------------------------------
		void registrarPaquete(Persona remitente, Persona destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			LugarReparto* oficinaReparto, LugarReparto* regionReparto);
		//--------------------------------------------------------------------------------------------------------------------------
		void conteoPaquetes();
		
		Persona buscarPersona(std::string numeroIdentificacion);
		Paquete buscarPaquete(std::string numeroGuia);		
		LugarReparto* buscarOficina(std::string codigoOficina);
		LugarReparto* buscarRegion(std::string codigoRegion);
		
		bool validarCadenaAlfabetica(std::string& cadena);
		bool validarCadenaNumerica(std::string& cadena);
		bool validarCadenaAlfanumerica(std::string& cadena);
		bool validarCodigoOficina(std::string& cadena);
		
		bool agregarOficina(LugarReparto* general, LugarReparto* secundaria); //implementar
		bool agregarRegion(LugarReparto* oficina, LugarReparto* region); //implementar
		
		void cargarOficinas(std::string nombreArchivo); //implementar
		void cargarRegiones(std::string nombreArchivo); //implementar
		void repartirPaquetes(std::string codigoOficina); //implementar
		 
};

#include "empresa_mensajeria.hxx"

#endif