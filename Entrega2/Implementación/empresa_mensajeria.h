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
		void registrarPersona(std::string numeroIdentificacion, std::string nombre, std::string apellidos, 
			std::string direccion, std::string ciudad, std::string telefono);
		void registrarPaquete(Persona remitente, Persona destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			OficinaReparto oficinaReparto, RegionReparto regionReparto);
		void conteoPaquetes();
		
		Persona buscarPersona(std::string numeroIdentificacion);
		Paquete buscarPaquete(std::string numeroGuia);
		OficinaReparto buscarOficinaReparto(std::string codigoOficina);
		RegionReparto buscarRegionReparto(std::string codigoRegion);
		
		void agregarRegionReparto(std::string codigoOficina, RegionReparto regionReparto);
		
		bool validarCadenaAlfabetica(std::string& cadena);
		bool validarCadenaNumerica(std::string& cadena);
		bool validarCadenaAlfanumerica(std::string& cadena);
		bool validarCodigoOficina(std::string& cadena);
		
		void cargarOficinas(std::string nombreArchivo); //implementar
		void cargarRegiones(std::string nombreArchivo); //implementar
		void repartirPaquetes(std::string codigoOficina); //implementar
		
		void agregarOficina(OficinaReparto oficinaReparto); //implementar
		void agregarRegion(RegionReparto regionReparto, OficinaReparto oficinaReparto); //implementar
		 
};

#include "empresa_mensajeria.hxx"

#endif