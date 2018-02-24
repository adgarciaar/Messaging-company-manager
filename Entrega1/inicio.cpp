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
	
	cout<<endl<<endl;
	
	empresa.cargarPaquetes("Paquetes.csv");
	
	
	return 0;
}