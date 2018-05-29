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
    std::string oficinaActual;
		std::string regionReparto;
		bool repartido; //permite conocer si el paquete fue repartido

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
    std::string getOficinaActual();
		std::string getRegionReparto();
		bool getRepartido();

		//setters
		void setRemitente(std::string remitente);
		void setDestinatario(std::string destinatario);
		void setPeso(int peso);
		void setTipoContenido(std::string tipoContenido);
		void setNumeroGuia(std::string numeroGuia);
		void setOficinaRecepcion(std::string oficinaRecepcion);
    void setOficinaActual(std::string oficinaActual);
		void setRegionReparto(std::string regionReparto);

		void setRepartido();

};

#include "paquete.hxx"

#endif
