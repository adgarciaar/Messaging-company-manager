#include "empresa_mensajeria.h" 

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

EmpresaMensajeria::EmpresaMensajeria(){}

EmpresaMensajeria::EmpresaMensajeria(string nombre){
	this->nombre = nombre;	
}

void EmpresaMensajeria::cargarPersonas(string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	if (myfile.is_open()){
		while ( getline (myfile,line) ){
		  cout << line << '\n';
		}
		myfile.close();
	}else{
		cout << "No se puede abrir el archivo";
	}
	
}

void EmpresaMensajeria::cargarPaquetes(string nombreArchivo){
	
}

void EmpresaMensajeria::registrarPersona(){
	
}

void EmpresaMensajeria::registrarPaquete(){
	
}

long EmpresaMensajeria::conteoPaquetes(){ //hacerlo
	return 0;
}
