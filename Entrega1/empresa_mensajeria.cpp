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
		
	}else{
		cout << "No se puede abrir el archivo";
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
						
						regionReparto(tokens[9], tokens[10]);
						oficinaReparto(tokens[5], tokens[6], tokens[7], tokens[8]);
						oficinaReparto.agregarRegion(regionReparto);
						this->oficinas.push_back(oficinaReparto);
						
					}else{ //ya está registrada
					
						//mirar si está registrada ya la regionReparto
						RegionReparto regionReparto = this->buscarRegionReparto(tokens[9]);
						if(regionReparto.getCodigo() == "-1"){ //no está registrada
							regionReparto(tokens[9], tokens[10]);
							this->agregarRegionReparto(oficinaReparto.getCodigo(), regionReparto);
						}
					}
				
					stringstream ss(tokens[2]);
					int peso;
					ss >> peso;
					Paquete paquete(remitente,destinatario,peso,tokens[3],tokens[4],oficinaReparto,regionReparto);
					this->paquetes.push(paquete);
					
				}else{
					cout<<endl<<"No se puede registrar el paquete de la línea "<<", remitente y/o destinatario no registrados"<<endl;
				}
							
			}
			
			b = true;
		}
		
		myfile.close();
		
	}else{
		cout << "No se puede abrir el archivo";
	}
	
}

void EmpresaMensajeria::registrarPersona(){
	
}

void EmpresaMensajeria::registrarPaquete(){
	
}

long EmpresaMensajeria::conteoPaquetes(){ //hacerlo
	return 0;
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

void EmpresaMensajeria::agregarRegionReparto(std::string codigoOficina, RegionReparto regionReparto){
	
	for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		if(codigoOficina = (*it).getCodigo()){
			(*it).agregarRegion(regionReparto);
			break;
		}
	}
	
}