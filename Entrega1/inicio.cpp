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
	cin.ignore();
	getline (cin, nombre);
	cout<<endl<<"Digite los apellidos: ";
	cin.ignore();
	getline (cin, apellidos);
	cout<<endl<<"Digite la direccion: ";
	cin.ignore();
	getline (cin, direccion);
	cout<<endl<<"Digite la ciudad: ";
	cin.ignore();
	cin>>ciudad;
	cout<<endl<<"Digite el telefono: ";
	cin>>telefono;
	cin.ignore();
	
	//validar que los datos sean validos
	if(empresa.validarCadenaAlfanumerica(numeroIdentificacion) == true && empresa.validarCadenaAlfabetica(nombre)==true && empresa.validarCadenaAlfabetica(apellidos)==true	
		&& empresa.validarDireccion(direccion)==true && empresa.validarCadenaAlfabetica(ciudad)==true && empresa.validarCadenaNumerica(telefono)==true) { 
		empresa.registrarPersona(numeroIdentificacion, nombre, apellidos, direccion, ciudad, telefono);
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a intentar"<<endl<<endl;	
	}
}

void registrarPaquete(EmpresaMensajeria& empresa){
	Persona remitente, destinatario;
	string peso;
	string tipoContenido, numeroGuia, numIdRemitente, numIdDestinatario, codOficina,codRegion;
	OficinaReparto oficinaReparto;
	RegionReparto regionReparto;
	
	cout<<"Digite el numero de guia: ";
	cin>>numeroGuia;
	cout<<"Digite el numero de identificacion del remitente: ";
	cin>>numIdRemitente;
	cout<<"Digite el numero de identificacion del destinatario: ";
	cin>>numIdDestinatario;
	cout<<"Digite el peso: ";
	cin>>peso;	
	cout<<endl<<"Digite el tipo de contenido: ";
	cin.ignore();
	getline (cin, tipoContenido);
	cout<<"Digite el codigo de la oficina de reparto: ";
	cin>>codOficina;
	cout<<"Digite el codigo de la region de reparto: ";
	cin>>codRegion;	
	cin.ignore();	
	
	if (empresa.validarCodigoOficina(codOficina)==true){cout<<"true codOficina"<<endl;}
	
	//validar que los datos sean validos
	if( empresa.validarCadenaAlfanumerica(numeroGuia)==true && empresa.validarCadenaAlfanumerica(numIdRemitente)==true && empresa.validarCadenaAlfanumerica(numIdDestinatario)==true 
		&& empresa.validarCadenaNumerica(peso)==true && empresa.validarCodigoOficina(codOficina)==true && empresa.validarCadenaAlfanumerica(codRegion)==true 
		&& (numIdRemitente != numIdDestinatario) && empresa.validarCadenaAlfanumerica(tipoContenido)==true ){
	
		remitente = empresa.buscarPersona(numIdRemitente);
		destinatario = empresa.buscarPersona(numIdDestinatario);
		oficinaReparto = empresa.buscarOficinaReparto(codOficina);
		regionReparto = empresa.buscarRegionReparto(codRegion);
	
		//validar que existan remitente, destinatario, oficina y region
		if (remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1" && oficinaReparto.getCodigo() != "-1" && regionReparto.getCodigo() != "-1"){
			
			stringstream ss(peso);
			int pesoInt;
			ss >> pesoInt;
			
			empresa.registrarPaquete(remitente, destinatario, pesoInt, tipoContenido, numeroGuia, oficinaReparto, regionReparto);
		}else{
			cout<<endl<<"No se pudo registrar el paquete, remitente y/o destinatario y/o oficina y/o region no estan registradas"<<endl<<endl;	
		}		
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a ingresarlo(s)"<<endl<<endl;	
	}
}