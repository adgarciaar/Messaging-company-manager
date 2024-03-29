#ifndef EMPRESA_MENSAJERIA_H
#define EMPRESA_MENSAJERIA_H 

#include <string>
#include <queue>
#include <list>
#include "oficina_reparto.h"
#include "region_reparto.h"
#include "persona.h"
#include "paquete.h"
#include "Arbol.h"
#include "Graph.h"

typedef PUJ::Graph< OficinaReparto*, float > TGraph;

class EmpresaMensajeria{
	
    private:
	
		std::string nombre;
		Arbol< OficinaReparto* > arbol; //almacena jerarquía de oficinas
		std::list<Persona> personas;
		TGraph grafo;
		
	public:
	
		EmpresaMensajeria();
		EmpresaMensajeria(std::string nombre);
		
		void cargarPersonas(std::string nombreArchivo);		
		void cargarPaquetes(std::string nombreArchivo);		
		//--------------------------------------------------------------------------------------------------------------------------
		void registrarPersona(std::string numeroIdentificacion, std::string nombre, std::string apellidos, 
			std::string direccion, std::string ciudad, std::string telefono);
		//--------------------------------------------------------------------------------------------------------------------------
		void registrarPaquete(std::string remitente, std::string destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			std::string oficinaRecepcion, std::string regionReparto);
		//--------------------------------------------------------------------------------------------------------------------------
		void conteoPaquetes();
		void conteoPaquetesRepartidos();
		
		Persona buscarPersona(std::string numeroIdentificacion);
		Paquete buscarPaquete(std::string numeroGuia);		
		OficinaReparto* buscarOficina(std::string codigoOficina);
		RegionReparto buscarRegion(std::string codigoRegion);
		
		bool validarCadenaAlfabetica(std::string& cadena);
		bool validarCadenaNumerica(std::string& cadena);
		bool validarCadenaAlfanumerica(std::string& cadena);
		bool validarCodigoOficina(std::string& cadena);
		
		bool agregarOficina(OficinaReparto* general, OficinaReparto* secundaria); 
		bool agregarOficina(OficinaReparto* secundaria); 
		bool agregarRegion(OficinaReparto* oficina, RegionReparto region); 
		
		void cargarOficinas(std::string nombreArchivo);
		void cargarRegiones(std::string nombreArchivo); 
		void repartirPaquetes(std::string codigoOficina);
		
		void cargarConexiones(std::string nombreArchivo);
		void rutaReparto(std::string codigoOficinaOrigen, std::string codigoOficinaDestino);
		
		void imprimirArbolYGrafo();
		 
};

#include "empresa_mensajeria.hxx"

#endif