#ifndef PAQUETE_H
#define PAQUETE_H 

#include <string>
#include "persona.h"
#include "oficina_reparto.h"
#include "region_reparto.h"

class Paquete{
	
    private:
 
		std::string remitente;
		std::string destinatario;
		int peso; //en gramos
		std::string tipoContenido;
		std::string numeroGuia;
		std::string oficinaRecepcion;
		std::string regionReparto;
 
	public:
	
		//constructor
		Paquete();
		Paquete(std::string remitente, std::string destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			std::string oficinaRecepcion, std::string regionReparto);
			
		//getters
		std::string getRemitente();
		std::string getDestinatario();
		int getPeso();
		std::string getTipoContenido();
		std::string getNumeroGuia();
		std::string getOficinaRecepcion();
		std::string getRegionReparto();
		
		//setters
		void setRemitente(std::string remitente);
		void setDestinatario(std::string destinatario);
		void setPeso(int peso);
		void setTipoContenido(std::string tipoContenido);
		void setNumeroGuia(std::string numeroGuia);
		void setOficinaRecepcion(std::string oficinaRecepcion);
		void setRegionReparto(std::string regionReparto);
		
};

#include "paquete.hxx"

#endif