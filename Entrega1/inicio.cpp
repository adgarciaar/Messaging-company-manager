#include <iostream>
#include "empresa_mensajeria.h" 
#include "paquete.h" 
#include "persona.h"
#include "oficina_reparto.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

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
		
			}else if(comando == "registrarPaquete"){ 
				
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
		
	}while(comando != "salir");
	
	cout<<endl<<endl;
	return 0;	
}