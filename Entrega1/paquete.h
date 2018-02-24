#ifndef PAQUETE_H
#define PAQUETE_H 

#include <string>
#include "persona.h"

class Paquete{
	
    private:
 
		Persona remitente;
		Persona destinatario;
		int peso; //en gramos
		std::string tipoContenido;
		std::string numeroGuia;
 
	public:
		//constructor
		Paquete();
		Paquete(Persona remitente, Persona destinatario, int peso, std::string tipoContenido, std::string numeroGuia);
		//getters
		Persona getRemitente();
		Persona getDestinatario();
		int getPeso();
		std::string getTipoContenido();
		std::string getNumeroGuia();
		//setters
		void setRemitente(Persona remitente);
		void setDestinatario(Persona destinatario);
		void setPeso(int peso);
		void setTipoContenido(std::string tipoContenido);
		void setNumeroGuia(std::string numeroGuia);
			
};

#endif