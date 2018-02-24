#ifndef PAQUETE_H
#define PAQUETE_H 

#include <string>
#include "Persona.h"

using namespace std;

class Paquete{
	
    private:
 
		Persona remitente;
		Persona destinatario;
		int peso; //en gramos
		string tipoContenido;
		string numeroGuia;
 
	public:
		//constructores
		Paquete();
		Paquete(Persona remitente, Persona destinatario, int peso, string tipoContenido, string numeroGuia);
		//getters
		Persona getRemitente();
		Persona getDestinatario();
		int getPeso();
		string getTipoContenido();
		string getNumeroGuia();
		//setters
		void setRemitente(Persona remitente);
		void setDestinatario(Persona destinatario);
		void setPeso(int peso);
		void setTipoContenido(string tipoContenido);
		void setNumeroGuia(string numeroGuia);
			
};

#endif