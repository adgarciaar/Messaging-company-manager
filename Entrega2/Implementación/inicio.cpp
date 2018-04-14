#include <iostream>
#include "empresa_mensajeria.h" 
#include "paquete.h" 
#include "persona.h"
#include "oficina_reparto.h"
#include "region_reparto.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

void registrarPersona(EmpresaMensajeria& empresa);
void registrarPaquete(EmpresaMensajeria& empresa);
void registrarOficina(EmpresaMensajeria& empresa);
void registrarRegion(EmpresaMensajeria& empresa);

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
				cout<<"\t"<<"cargarOficinas nombre_archivo"<<endl;
				cout<<"\t"<<"cargarRegiones nombre_archivo"<<endl;
				cout<<"\t"<<"registrarPersona"<<endl;
				cout<<"\t"<<"registrarPaquete"<<endl;
				cout<<"\t"<<"registrarOficina"<<endl;
				cout<<"\t"<<"registrarRegion"<<endl;
				cout<<"\t"<<"conteoPaquetes"<<endl;
				cout<<"\t"<<"repartirPaquetes codigo_oficina"<<endl;
				cout<<"\t"<<"ayuda comando"<<endl;
				cout<<"\t"<<"salir"<<endl;
			}else if(comando == "registrarPersona"){ 
				registrarPersona(empresa);
			}else if(comando == "registrarPaquete"){ 
				registrarPaquete(empresa);
			}else if(comando == "registrarOficina"){ 
				registrarOficina(empresa);
			}else if(comando == "registrarRegion"){ 
				registrarRegion(empresa);
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
			}else if(tokens[0] == "cargarOficinas"){ 
				empresa.cargarOficinas(tokens[1]);
			}else if(tokens[0] == "cargarRegiones"){ 
				empresa.cargarRegiones(tokens[1]);
			}else if(tokens[0] == "repartirPaquetes"){ 
				empresa.repartirPaquetes(tokens[1]);
			}else if(tokens[0] == "ayuda"){ 
				if(tokens[1] == "cargarPersonas"){
					cout<<"\t"<<"Se debe escribir el comando: cargarPersonas nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de las personas, seguido de su extension. Por ejemplo: cargarPersonas personas.csv"<<endl;
				}else if(tokens[1] == "cargarPaquetes"){
					cout<<"\t"<<"Se debe escribir el comando: cargarPaquetes nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de los paquetes, seguido de su extension. Por ejemplo: cargarPersonas paquetes.csv"<<endl;
				}else if(tokens[1] == "cargarOficinas"){
					cout<<"\t"<<"Se debe escribir el comando: cargarOficinas nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de las oficinas, seguido de su extension. Por ejemplo: cargarOficinas oficina.csv"<<endl;
				}else if(tokens[1] == "cargarRegiones"){
					cout<<"\t"<<"Se debe escribir el comando: cargarRegiones nombre_archivo, donde nombre_archivo es el nombre del archivo que tiene la informacion de las regiones, seguido de su extension. Por ejemplo: cargarRegiones regiones.csv"<<endl;
				}else if(tokens[1] == "registrarPersona"){
					cout<<"\t"<<"Se debe escribir el comando: registrarPersona. El programa lo guiara para introducir los datos de la persona"<<endl;
				}else if(tokens[1] == "registrarPaquete"){
					cout<<"\t"<<"Se debe escribir el comando: registrarPaquete. El programa lo guiara para introducir los datos del paquete"<<endl;
				}else if(tokens[1] == "registrarOficina"){
					cout<<"\t"<<"Se debe escribir el comando: registrarOficina. El programa lo guiara para introducir los datos de la oficina"<<endl;
				}else if(tokens[1] == "registrarRegion"){
					cout<<"\t"<<"Se debe escribir el comando: registrarRegion. El programa lo guiara para introducir los datos de la region"<<endl;
				}else if(tokens[1] == "conteoPaquetes"){
					cout<<"\t"<<"Se debe escribir el comando: conteoPaquetes. Se imprimira la informacion de los paquetes"<<endl;
				}else if(tokens[1] == "repartirPaquetes"){
					cout<<"\t"<<"Se debe escribir el comando: repartirPaquetes codigo_oficina, donde codigo_oficina es el codigo de la oficina donde se repartiran los paquetes"<<endl;
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
       && empresa.validarCadenaAlfabetica(ciudad)==true && empresa.validarCadenaNumerica(telefono)==true) { 
	   
	    Persona personaComprob = empresa.buscarPersona(numeroIdentificacion);
					
		if(personaComprob.getNumeroIdentificacion() == "-1"){ //no está registrada	   
			empresa.registrarPersona(numeroIdentificacion, nombre, apellidos, direccion, ciudad, telefono);
			cout<<endl<<endl<< "La persona con identificacion "<<numeroIdentificacion<<" ha sido registrada exitosamente"<<endl<<endl;			
		}else{
			cout<<endl<<endl<< "La persona con identificacion "<<numeroIdentificacion<<" ya se encuentra registrada en el sistema"<<endl<<endl;
		}
		
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a intentar."<<endl<<endl;	
	}
}

void registrarPaquete(EmpresaMensajeria& empresa){
	
	Persona remitente, destinatario;
	string peso;
	string tipoContenido, numeroGuia, numIdRemitente, numIdDestinatario, codOficina,codRegion;
	OficinaReparto* oficinaReparto;
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
	
	//validar que los datos sean validos
	if( empresa.validarCadenaAlfanumerica(numeroGuia)==true && empresa.validarCadenaAlfanumerica(numIdRemitente)==true && empresa.validarCadenaAlfanumerica(numIdDestinatario)==true 
		&& empresa.validarCadenaNumerica(peso)==true && empresa.validarCodigoOficina(codOficina)==true && empresa.validarCadenaAlfanumerica(codRegion)==true 
		&& (numIdRemitente != numIdDestinatario) ){
	
		remitente = empresa.buscarPersona(numIdRemitente);
		destinatario = empresa.buscarPersona(numIdDestinatario);
		oficinaReparto = empresa.buscarOficina(codOficina);
		regionReparto = empresa.buscarRegion(codRegion);
	
		//validar que existan remitente, destinatario, oficina y region
		if (remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1" && oficinaReparto != NULL && regionReparto.getCodigo() != "-1" ){
			
			Paquete paqueteComprob = empresa.buscarPaquete(numeroGuia);
					
			if (paqueteComprob.getNumeroGuia() == "-1"){ //no se ha registrado el paquete
			
				stringstream ss(peso);
				int pesoInt;
				ss >> pesoInt;
				
				empresa.registrarPaquete(remitente, destinatario, pesoInt, tipoContenido, numeroGuia, *oficinaReparto, regionReparto);
				
				cout<<endl<<endl<< "El paquete con numero de guia "<<numeroGuia<<" ha sido registrado exitosamente."<<endl<<endl;
				
			}else{
				cout<<endl<<endl<< "El paquete con numero de guia "<<numeroGuia<<" ya se encuentra registrado en el sistema"<<endl<<endl;
			}
		}else{
			cout<<endl<<"No se pudo registrar el paquete, remitente y/o destinatario y/o oficina y/o region no estan registradas"<<endl<<endl;	
		}		
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a ingresarlo(s)"<<endl<<endl;	
	}
}

void registrarOficina(EmpresaMensajeria& empresa){
	
	string codOficina, nombreOficina, direccionOficina, ciudadOficina;
	cout<<"Digite el codigo de la oficina: ";
	cin>>codOficina;
	cout<<endl<<"Digite el nombre de la oficina: ";
	cin.ignore();
	getline (cin, nombreOficina);
	cout<<endl<<"Digite la direccion de la oficina: ";
	cin.ignore();
	getline (cin, direccionOficina);
	cout<<endl<<"Digite la ciudad de la oficina: ";
	cin.ignore();
	getline (cin, ciudadOficina);
	cin.ignore();
	
	//validar que los datos sean validos
	if(empresa.validarCodigoOficina(codOficina) == true && empresa.validarCadenaAlfabetica(ciudadOficina)==true ) { 		
		
		OficinaReparto* oficinaReparto = empresa.buscarOficina(codOficina);
		
		if(oficinaReparto == NULL){ //no está registrada
		
			oficinaReparto = new OficinaReparto(codOficina, nombreOficina, direccionOficina, ciudadOficina);		
			
			empresa.agregarOficina(oficinaReparto);
			
			cout<<endl<<"La oficina con identificacion "<<codOficina<<" ha sido registrada exitosamente"<<endl<<endl;
		
		}else{ //ya está registrada
			cout<<endl<<"La oficina con identificacion "<<codOficina<<" ya se encuentra registrada en el sistema"<<endl<<endl;	
		}
		
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a intentar"<<endl<<endl;	
	}
}

void registrarRegion(EmpresaMensajeria& empresa){
	
	string codRegion, nombreRegion, codOficina;
	cout<<"Digite el codigo de la region: ";
	cin>>codRegion;
	cout<<endl<<"Digite el nombre de la region: ";
	cin.ignore();
	getline (cin, nombreRegion);
	cout<<"Digite el codigo de la oficina a la que pertenece: ";
	cin>>codOficina;
	cin.ignore();
	
	//validar que los datos sean validos
	if(empresa.validarCadenaAlfanumerica(codRegion) == true) { 		
		
		RegionReparto regionReparto = empresa.buscarRegion(codRegion);
		
		if(regionReparto.getCodigo() == "-1"){ //no está registrada
		
			OficinaReparto* oficinaReparto = empresa.buscarOficina(codOficina);
			
			if(oficinaReparto != NULL){ //ya está registrada
		
				regionReparto.setCodigo(codRegion); 
				regionReparto.setNombre(nombreRegion);
			
				empresa.agregarRegion(oficinaReparto, regionReparto);
			
				cout<<endl<<"La region con codigo "<<codRegion<<" ha sido registrada exitosamente"<<endl<<endl;
				
			}else{
				cout<<endl<<"La oficina a la que pertenece no esta registrada en el sistema. No se puede registrar la region"<<endl<<endl;
			}
		
		}else{ //ya está registrada
			cout<<endl<<"La region con codigo "<<codRegion<<" ya se encuentra registrada en el sistema"<<endl<<endl;	
		}
		
	}else{
		cout<<endl<<"Uno o varios datos no son validos, corrijalos y vuelva a intentar"<<endl<<endl;	
	}
}