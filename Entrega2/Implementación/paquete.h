#ifndef PAQUETE_H
#define PAQUETE_H 

#include <string>
#include "persona.h"
#include "oficina_reparto.h"
#include "region_reparto.h"

class Paquete{
	
    private:
 
		Persona remitente;
		Persona destinatario;
		int peso; //en gramos
		std::string tipoContenido;
		std::string numeroGuia;
		OficinaReparto oficinaReparto;
		RegionReparto regionReparto;
 
	public:
	
		//constructor
		Paquete();
		Paquete(Persona remitente, Persona destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			OficinaReparto oficinaReparto, RegionReparto regionReparto);
			
		//getters
		Persona getRemitente();
		Persona getDestinatario();
		int getPeso();
		std::string getTipoContenido();
		std::string getNumeroGuia();
		OficinaReparto getOficinaReparto();
		RegionReparto getRegionReparto();
		
		//setters
		void setRemitente(Persona remitente);
		void setDestinatario(Persona destinatario);
		void setPeso(int peso);
		void setTipoContenido(std::string tipoContenido);
		void setNumeroGuia(std::string numeroGuia);
		void setOficinaReparto(OficinaReparto oficinaReparto);
		void setRegionReparto(RegionReparto regionReparto);
		
};

#include "paquete.hxx"

#endif