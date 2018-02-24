#include "empresa_mensajeria.h" 

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
	
	Persona persona;
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		
		while ( getline (myfile,line) ){
			
			// Vector of string to save tokens
			vector <string> tokens;
			 
			// stringstream class check1
			stringstream check(line);
			 
			string intermediate;
			 
			// Tokenizing w.r.t. space ' '
			while(getline(check, intermediate, ','))
			{
				tokens.push_back(intermediate);
			}
			 
			// Printing the token vector
			for(int i = 0; i < tokens.size(); i++)
				cout << tokens[i] << ' ';		
			
			//cout << line << '\n';
			cout<< '\n';
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
		
		while ( getline (myfile,line) ){
		  cout << line << '\n';
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