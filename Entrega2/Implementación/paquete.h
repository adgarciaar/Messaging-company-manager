#ifndef PAQUETE_H
#define PAQUETE_H 

#include <string>
#include "persona.h"
#include "oficina_reparto.h"
#include "region_reparto.h"
#include "lugar_reparto.h"

class Paquete{
	
    private:
 
		Persona remitente;
		Persona destinatario;
		int peso; //en gramos
		std::string tipoContenido;
		std::string numeroGuia;
		LugarReparto* oficinaReparto;
		LugarReparto* regionReparto;
 
	public:
	
		//constructor
		Paquete();
		Paquete(Persona remitente, Persona destinatario, int peso, std::string tipoContenido, std::string numeroGuia,
			LugarReparto* oficinaReparto, LugarReparto* regionReparto);
			
		//getters
		Persona getRemitente();
		Persona getDestinatario();
		int getPeso();
		std::string getTipoContenido();
		std::string getNumeroGuia();
		LugarReparto* getOficinaReparto();
		LugarReparto* getRegionReparto();
		
		//setters
		void setRemitente(Persona remitente);
		void setDestinatario(Persona destinatario);
		void setPeso(int peso);
		void setTipoContenido(std::string tipoContenido);
		void setNumeroGuia(std::string numeroGuia);
		void setOficinaReparto(LugarReparto* oficinaReparto);
		void setRegionReparto(LugarReparto* regionReparto);
		
};

#include "paquete.hxx"

#endif