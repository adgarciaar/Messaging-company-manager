#include <iostream>
#include "empresa_mensajeria.h" 
#include "paquete.h" 
#include "persona.h"
#include "oficina_reparto.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

void registrarPersona(EmpresaMensajeria& empresa);
void registrarPaquete(EmpresaMensajeria& empresa);

int main(){
	
	cout<<endl<<endl<<"Bienvenido, digite comando (digite ayuda en caso de no conocerlo)"<<endl;
	
	EmpresaMensajeria empresa ("Empresa");
	
	string comando;
	// Vector of string to save tokens
	vector <string> tokens;
	
	do{
		cout<<endl<<endl;
		cout<<"$";
			
		getline (cin, comando);
					 
		// stringstream class check1
		stringstream check(comando);
					 
		string intermediate;
					 
		// Tokenizing w.r.t. space ' '
		while(getline(check, intermediate, ' ')){
			tokens.push_back(intermediate);
		}
		cout<<endl;
		if (tokens.size() > 2){
			cout<<endl<<"Comando no valido"<<endl<<endl;
		}else if(tokens.size() == 1){
			if (comando == "ayuda"){
				cout<<endl<<endl<<"Comandos disponibles: "<<endl<<endl;	
				cout<<"\t"<<"cargarPersonas nombre_archivo"<<endl;
				cout<<"\t"<<"cargarPaquetes nombre_archivo"<<endl;
				cout<<"\t"<<"registrarPersona"<<endl;
				cout<<"\t"<<"registrarPaquete"<<endl;
				cout<<"\t"<<"conteoPaquetes"<<endl;
				cout<<"\t"<<"ayuda comando"<<endl;
				cout<<"\t"<<"salir"<<endl;
			}else if(comando == "registrarPersona"){ 
				registrarPersona(empresa);
			}else if(comando == "registrarPaquete"){ 
				registrarPaquete(empresa);
			}else if(comando == "conteoPaquetes"){ 
				empresa.conteoPaquetes();
			}else if(comando == "salir"){ 
				break;
			}else{ 
				cout<<endl<<"Comando no valido"<<endl<<endl;	
			}

		}else if(tokens.size() == 2){
			if(tokens[0] == "cargarPersonas"){ 
				empresa.cargarPersonas(tokens[1]);
			}else if(tokens[0] == "cargarPaquetes"){ 
				empresa.cargarPaquetes(tokens[1]);
			}else if(tokens[0] == "ayuda"){ 
				if(tokens[1] == "cargarPersonas"){
					cout<<"\t"<<"Se debe escribir el comando: cargarPersonas nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de las personas, seguido de su extension. Por ejemplo: cargarPersonas personas.csv"<<endl;
				}else if(tokens[1] == "cargarPaquetes"){
					cout<<"\t"<<"Se debe escribir el comando: cargarPaquetes nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de los paquetes, seguido de su extension. Por ejemplo: cargarPersonas paquetes.csv"<<endl;
				}else if(tokens[1] == "registrarPersona"){
					cout<<"\t"<<"Se debe escribir el comando: registrarPersona. El programa lo guiara para introducir los datos de la persona"<<endl;
				}else if(tokens[1] == "registrarPaquete"){
					cout<<"\t"<<"Se debe escribir el comando: registrarPaquete. El programa lo guiara para introducir los datos del paquete"<<endl;
				}else if(tokens[1] == "conteoPaquetes"){
					cout<<"\t"<<"Se debe escribir el comando: conteoPaquetes. Se imprimira la informacion de los paquetes"<<endl;
				}else if(tokens[1] == "salir"){
					cout<<"\t"<<"Se debe escribir el comando: salir. El programa terminara la ejecucion"<<endl;
				}else{
					cout<<endl<<"Comando no valido"<<endl<<endl;
				}
			}else{ 
				cout<<endl<<"Comando no valido"<<endl<<endl;	
			}
		}
		
		tokens.clear();
		
	}while(true);
	
	cout<<endl<<endl;
	return 0;	
}

void registrarPersona(EmpresaMensajeria& empresa){
	string numeroIdentificacion, nombre, apellidos, direccion, ciudad, telefono;
	cout<<"Digite el numero de identificacion: ";
	cin>>numeroIdentificacion;
	cout<<endl<<"Digite el nombre: ";
	getline (cin, nombre);
	cout<<endl<<"Digite los apellidos: ";
	getline (cin, apellidos);
	cout<<endl<<"Digite la direccion: ";
	getline (cin, direccion);
	cout<<endl<<"Digite la ciudad: ";
	cin>>ciudad;
	cout<<endl<<"Digite el telefono: ";
	cin>>telefono;
	
	if(true){ //validar los datos
		empresa.registrarPersona(numeroIdentificacion, nombre, apellidos, direccion, ciudad, telefono);
	}
}

void registrarPaquete(EmpresaMensajeria& empresa){
	Persona remitente, destinatario;
	int peso;
	string tipoContenido, numeroGuia;
	OficinaReparto oficinaReparto;
	RegionReparto regionReparto;
	
	if(true){ //validar los datos
		empresa.registrarPaquete(remitente, destinatario, peso, tipoContenido, numeroGuia, oficinaReparto, regionReparto);
	}
}