#include "empresa_mensajeria.h" 
#include "oficina_reparto.h" 
#include "region_reparto.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

EmpresaMensajeria::EmpresaMensajeria(){}

EmpresaMensajeria::EmpresaMensajeria(string nombre){
	this->nombre = nombre;	
}

void EmpresaMensajeria::cargarPersonas(string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		bool b = false;
		
		while ( getline (myfile,line) ){
			
			if (b != false){
				
				// Vector of string to save tokens
				vector <string> tokens;
				 
				// stringstream class check1
				stringstream check(line);
				 
				string intermediate;
				 
				// Tokenizing w.r.t. coma ','
				while(getline(check, intermediate, ',')){
					tokens.push_back(intermediate);
				}
							
				Persona persona(tokens[2],tokens[0],tokens[1],tokens[3],tokens[4],tokens[5]);
				this->personas.push_back(persona);
			}
			
			b = true;
		}
		
		myfile.close();
		cout<<endl<<endl<< "La informacion desde el archivo "<<nombreArchivo<<" ha sido cargada exitosamente."<<endl<<endl;
		
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible."<<endl<<endl;
	}
	
}

void EmpresaMensajeria::cargarPaquetes(string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		bool b = false;
		
		while ( getline (myfile,line) ){
			
			if (b != false){
				
				// Vector of string to save tokens
				vector <string> tokens;
				 
				// stringstream class check1
				stringstream check(line);
				 
				string intermediate;
				 
				// Tokenizing w.r.t. coma ','
				while(getline(check, intermediate, ',')){
					tokens.push_back(intermediate);
				}
				
				string cedulaRemitente = tokens[0];
				string cedulaDestinatario = tokens[1];
				
				Persona remitente = this->buscarPersona(cedulaRemitente);
				Persona destinatario = this->buscarPersona(cedulaDestinatario);
				
				if(remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1"){ //ya registrados ambos
				
					//mirar si está registrada ya la oficinaReparto
					
					OficinaReparto oficinaReparto = this->buscarOficinaReparto(tokens[5]);
					RegionReparto regionReparto;
					
					if(oficinaReparto.getCodigo() == "-1"){ //no está registrada
					
						regionReparto.setCodigo(tokens[9]);
						regionReparto.setNombre(tokens[10]);
						
						oficinaReparto.setCodigo(tokens[5]);
						oficinaReparto.setNombre(tokens[6]);
						oficinaReparto.setDireccion(tokens[7]);
						oficinaReparto.setCiudad(tokens[8]);
					
						oficinaReparto.agregarRegion(regionReparto);
						
						this->oficinas.push_back(oficinaReparto);
						
					}else{ //ya está registrada
					
						//mirar si está registrada ya la regionReparto
						RegionReparto regionReparto = this->buscarRegionReparto(tokens[9]);
						
						if(regionReparto.getCodigo() == "-1"){ //no está registrada
						
							regionReparto.setCodigo(tokens[9]);
							regionReparto.setNombre(tokens[10]);
							
							this->agregarRegionReparto(oficinaReparto.getCodigo(), regionReparto);
						}
					}
				
					stringstream ss(tokens[2]);
					int peso;
					ss >> peso;
					Paquete paquete(remitente,destinatario,peso,tokens[3],tokens[4],oficinaReparto,regionReparto);
					this->paquetes.push(paquete);
					
				}else{
					cout<<endl<<"No se puede registrar el paquete con numero de guia "<<tokens[4]<<": remitente y/o destinatario no registrado(s)"<<endl;
				}
							
			}
			
			b = true;
		}
		
		myfile.close();
		cout<<endl<<endl<< "La informacion desde el archivo "<<nombreArchivo<<" ha sido cargada exitosamente."<<endl<<endl;
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible."<<endl<<endl;
	}
	
}

void EmpresaMensajeria::registrarPersona(string numeroIdentificacion, string nombre, string apellidos, 
			string direccion, string ciudad, string telefono){
				
	bool b = false;
	
	for(list< Persona >::iterator it = this->personas.begin(); it != this->personas.end( );	it++){
		if(numeroIdentificacion == (*it).getNumeroIdentificacion()){
			cout<<endl<<endl<< "La persona con identificacion "<<numeroIdentificacion<<" ya se encuentra registrada en el sistema."<<endl<<endl;
			b = true;
			break;
		}
	}
	
	if(b == false){ //se registra
		Persona persona(numeroIdentificacion,nombre,apellidos,direccion,ciudad,telefono);
		this->personas.push_back(persona);
		cout<<endl<<endl<< "La persona con identificacion "<<numeroIdentificacion<<" ha sido registrada exitosamente."<<endl<<endl;
	}
	
}

void EmpresaMensajeria::registrarPaquete(Persona remitente, Persona destinatario, int peso, string tipoContenido, string numeroGuia,
	OficinaReparto oficinaReparto, RegionReparto regionReparto){
	
	bool b = false;
	
	queue<Paquete> auxiliar (this->paquetes);
	
	while (auxiliar.empty() == false){
		if(auxiliar.front().getNumeroGuia() == numeroGuia){
			b = true;
			cout<<endl<<endl<< "El paquete con numero de guia "<<numeroGuia<<" ya se encuentra registrado en el sistema."<<endl<<endl;
			break;
		}
		auxiliar.pop();
	}	
	
	if(b == false){ //se registra
		Paquete paquete(remitente,destinatario,peso,tipoContenido,numeroGuia,oficinaReparto,regionReparto);
		this->paquetes.push(paquete);
		cout<<endl<<endl<< "El paquete con numero de guia "<<numeroGuia<<" ha sido registrado exitosamente."<<endl<<endl;
	}
}

void EmpresaMensajeria::conteoPaquetes(){

	long numPaquetes = this->paquetes.size();
	
	if(numPaquetes == 0){
		cout<<endl<<endl<< "No existe informacion de paquetes registrada en el sistema."<<endl<<endl;
	}else{
		cout<<endl<<endl<<"Se encuentran en el sistema "<<numPaquetes<<" pendientes por entregar. Estan distribuidos asi:"<<endl<<endl;
		
		queue<Paquete> auxiliar (this->paquetes);
		vector <long> paquetesPorRegion;
		long cantidad = 0;
		for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		
			list<RegionReparto> regiones = (*it).getRegiones();
			
			for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){
				cantidad = 0;
				while(auxiliar.empty() == false){
					if(auxiliar.front().getRegionReparto().getCodigo() == (*it2).getCodigo()){
						cantidad += 1;
					}					
					auxiliar.pop();
				}
				cout<<cantidad<<" en la region de reparto "<<(*it2).getNombre()<<endl;
				auxiliar = this->paquetes;				
			}			
		}		
	}
}

Persona EmpresaMensajeria::buscarPersona(string cedula){
	
	Persona persona;
	bool b = false;
	
	for(list< Persona >::iterator it = this->personas.begin(); it != this->personas.end( );	it++){
		if(cedula == (*it).getNumeroIdentificacion()){
			b = true;
			persona = *it;
			break;
		}
	}
	
	if(b == false){
		persona.setNumeroIdentificacion("-1");
	}
	
	return persona;
}

OficinaReparto EmpresaMensajeria::buscarOficinaReparto(string codigoOficina){
	
	OficinaReparto oficinaReparto;
	bool b = false;
	
	for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		if(codigoOficina == (*it).getCodigo()){
			b = true;
			oficinaReparto = *it;
			break;
		}
	}
	
	if(b == false){
		oficinaReparto.setCodigo("-1");
	}
	
	return oficinaReparto;
}

RegionReparto EmpresaMensajeria::buscarRegionReparto(string codigoRegion){
	
	RegionReparto regionReparto;
	bool b = false;
	
	for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		
		list<RegionReparto> regiones = (*it).getRegiones();
		
		for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){
			
			if(codigoRegion == (*it2).getCodigo()){
				b = true;
				regionReparto = *it2;
				break;
			}
			
		}

	}
	
	if(b == false){
		regionReparto.setCodigo("-1");
	}
	
	return regionReparto;
}

void EmpresaMensajeria::agregarRegionReparto(string codigoOficina, RegionReparto regionReparto){
	
	for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		if(codigoOficina == (*it).getCodigo()){
			(*it).agregarRegion(regionReparto);
			break;
		}
	}
	
}