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
		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;
		
		while ( getline (myfile,line) ){
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 6 && b == false){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida."<<endl<<endl;
				break;
			}
			
			if(tokens.size() != 6 && b != false){
				cout<<endl<<"Datos incompletos en la linea "<<numeroLinea<<" del archivo "<<nombreArchivo<<endl;
			}else if (tokens.size() == 6 && b != false){
				string numeroIdentificacion=tokens[2],nombre=tokens[0],apellidos=tokens[1],direccion=tokens[3],ciudad=tokens[4],telefono=tokens[5];
				
				//revisar si datos son válidos
				if(this->validarCadenaAlfanumerica(numeroIdentificacion) == true && this->validarCadenaAlfabetica(nombre)==true && this->validarCadenaAlfabetica(apellidos)==true	
					&& this->validarCadenaAlfanumerica(direccion)==true && this->validarCadenaAlfabetica(ciudad)==true && this->validarCadenaNumerica(telefono)==true) { 
			
					Persona persona(numeroIdentificacion,nombre,apellidos,direccion,ciudad,telefono);
					this->personas.push_back(persona);
				}else{
					cout<<endl<<"Uno o varios datos no son validos, en la linea "<<numeroLinea<<" del archivo "<<nombreArchivo<<endl;
				}							
			}
			
			tokens.clear();
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
		int numeroLinea = 0;
		bool b = false;
		// Vector of string to save tokens
		vector <string> tokens;
		
		while ( getline (myfile,line) ){
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 11 && b == false){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida."<<endl<<endl;
				break;
			}
			
			if(tokens.size() != 11 && b != false){
				cout<<endl<<"Datos incompletos en la linea "<<numeroLinea<<" del archivo "<<nombreArchivo<<endl;
				
			}else if(tokens.size() == 11 && b != false){
				
				string cedulaRemitente = tokens[0];
				string cedulaDestinatario = tokens[1];
				string codRegionReparto = tokens[9];
				string nombreRegionReparto = tokens[10];
				string codOficina = tokens[5];
				string nombreOficina = tokens[6];
				string direccionOficina = tokens[7];
				string ciudadOficina = tokens[8];
				string pesoString = tokens[2];
				string tipoContenido = tokens[3];
				string numeroGuia = tokens[4];
				
				//revisar si datos son válidos
				
				if(this->validarCadenaAlfanumerica(cedulaRemitente)==true && this->validarCadenaAlfanumerica(cedulaDestinatario)== true
					&& this->validarCadenaAlfanumerica(codRegionReparto) && this->validarCadenaAlfabetica(nombreRegionReparto)==true 
					&& this->validarCodigoOficina(codOficina)==true && this->validarCadenaAlfabetica(nombreOficina)==true
					&& this->validarCadenaAlfanumerica(direccionOficina)==true && this->validarCadenaAlfabetica(ciudadOficina)==true 
					&& this->validarCadenaNumerica(pesoString)==true && this->validarCadenaAlfabetica(tipoContenido)==true
					&& this->validarCadenaAlfanumerica(numeroGuia) ){
					
					
					Persona remitente = this->buscarPersona(cedulaRemitente);
					Persona destinatario = this->buscarPersona(cedulaDestinatario);
					
					if(remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1"){ //ya registrados ambos
					
						//mirar si está registrada ya la oficinaReparto
						
						OficinaReparto oficinaReparto = this->buscarOficinaReparto(codOficina);
						RegionReparto regionReparto;
						
						if(oficinaReparto.getCodigo() == "-1"){ //no está registrada
						
							regionReparto.setCodigo(codRegionReparto);
							regionReparto.setNombre(nombreRegionReparto);
							
							oficinaReparto.setCodigo(codOficina);
							oficinaReparto.setNombre(nombreOficina);
							oficinaReparto.setDireccion(direccionOficina);
							oficinaReparto.setCiudad(ciudadOficina);
						
							oficinaReparto.agregarRegion(regionReparto);
							
							this->oficinas.push_back(oficinaReparto);
							
						}else{ //ya está registrada
						
							//mirar si está registrada ya la regionReparto
							regionReparto = this->buscarRegionReparto(codRegionReparto);
							
							if(regionReparto.getCodigo() == "-1"){ //no está registrada
							
								regionReparto.setCodigo(codRegionReparto);
								regionReparto.setNombre(nombreRegionReparto);
								
								this->agregarRegionReparto(oficinaReparto.getCodigo(), regionReparto);
							}
						}
					
						stringstream ss(pesoString);
						int peso;
						ss >> peso;
						Paquete paquete(remitente,destinatario,peso,tipoContenido,numeroGuia,oficinaReparto,regionReparto);
						this->paquetes.push(paquete);
						
					}else{
						cout<<endl<<"No se puede registrar el paquete con numero de guia "<<numeroGuia<<": remitente y/o destinatario no registrado(s)"<<endl;
					}						
					
				}else{
					cout<<endl<<"Uno o varios datos no son validos, en la linea "<<numeroLinea<<" del archivo "<<nombreArchivo<<endl;
				}			
							
			}
			
			tokens.clear();
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
		long cantidad = 0;
		
		for(list< OficinaReparto >::iterator it = this->oficinas.begin(); it != this->oficinas.end( );	it++){
		
			list<RegionReparto> regiones = (*it).getRegiones();
			
			for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){
				cantidad = 0;
				while(auxiliar.empty() == false){					
					if(auxiliar.front().getRegionReparto().getCodigo() == (*it2).getCodigo()){
						cantidad++;
					}					
					auxiliar.pop();
				}
				if(cantidad != 0){
					cout<<cantidad<<" en la region de reparto "<<(*it2).getNombre()<<endl;					
				}
				auxiliar = this->paquetes;				
			}			
		}		
	}
}

Persona EmpresaMensajeria::buscarPersona(string numeroIdentificacion){
	
	Persona persona;
	bool b = false;
	
	for(list< Persona >::iterator it = this->personas.begin(); it != this->personas.end( );	it++){
		if(numeroIdentificacion == (*it).getNumeroIdentificacion()){
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

bool EmpresaMensajeria::validarCadenaAlfabetica(string& cadena){ //true si cumple
	
	bool b = true;

    for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
        if( !((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch == ' ')) ){
            b = false;
        }
    }
	
	return b;
}

bool EmpresaMensajeria::validarCadenaNumerica(string& cadena){ //true si cumple
	
	bool b = true;

    for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
        if( !(isdigit(ch)) ){
            b = false;
        }
    }
	
	return b;
}

bool EmpresaMensajeria::validarCadenaAlfanumerica(string& cadena){ //true si cumple
	
	bool b = true;

    for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
        if( !((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch == ' ') || (isdigit(ch))) ){
            b = false;
        }
    }
	
	return b;
}

bool EmpresaMensajeria::validarCodigoOficina(string& cadena){ //true si cumple
	
	bool b = true;
	
	if(cadena.size() == 8){
		for (int i=0; i<3; i++){
			char ch = cadena[i];
			if( !((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch == ' ')) ){
				b = false;
			}
		}
		for (int i=3; i<cadena.size(); i++){
			char ch = cadena[i];
			if( !(isdigit(ch)) ){
				b = false;
			}
		}
	}else{
		b = false;
	}   
	
	return b;
}