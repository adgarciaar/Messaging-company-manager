#include <iostream>
#include "empresa_mensajeria.h" 
#include "paquete.h" 
#include "persona.h"
#include "oficina_reparto.h"
#include <string>

using namespace std;

int main(){
	
	EmpresaMensajeria empresa ("Empresa");
	
	empresa.cargarPersonas("Personas.csv");
	
	empresa.cargarPaquetes("Paquetes.csv");
	
	cout<<endl<<endl;
	
	return 0;
}