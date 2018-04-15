#include "empresa_mensajeria.h" 
#include <fstream> // std::ifstream
#include <sstream>  // std::stringstream
#include "Nodo.h"
#include <algorithm> //para str.erase
#include <map>

using namespace std;

EmpresaMensajeria::EmpresaMensajeria(){
	OficinaReparto* lugarReparto = new OficinaReparto("0", "Oficina central en Colombia", "Calle 142 No. 5", "Bogota");
	this->arbol.fijarRaiz(lugarReparto);
}

//---------------------------------------------------------------------------------------------------

EmpresaMensajeria::EmpresaMensajeria(string nombre){
	this->nombre = nombre;	
	OficinaReparto* lugarReparto = new OficinaReparto("0", "Oficina central en Colombia", "Calle 142 No. 5", "Bogota");
	this->arbol.fijarRaiz(lugarReparto);
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::cargarPersonas(string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		
		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;
		
		long correctos = 0, incorrectos = 0;
		
		while ( getline (myfile,line) ){
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 6 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}
			
			if(tokens.size() != 6 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;
			}else if (tokens.size() == 6 && numeroLinea != 1){
				string numeroIdentificacion=tokens[2],nombre=tokens[0],apellidos=tokens[1],direccion=tokens[3],ciudad=tokens[4],telefono=tokens[5];
				
				//revisar si datos son válidos
				if(this->validarCadenaAlfanumerica(numeroIdentificacion) == true && this->validarCadenaAlfabetica(nombre)==true && this->validarCadenaAlfabetica(apellidos)==true	
					&& this->validarCadenaAlfabetica(ciudad)==true && this->validarCadenaNumerica(telefono)==true) { 
					
					Persona personaComprob = this->buscarPersona(numeroIdentificacion);
					
					if(personaComprob.getNumeroIdentificacion() == "-1"){ //no está registrada
						Persona persona(numeroIdentificacion,nombre,apellidos,direccion,ciudad,telefono);
						this->personas.push_back(persona);
						correctos++;
					}else{ //ya está registrada
						cout<<endl<<"En la linea "<<numeroLinea<<": la persona con numero de identificacion "<<numeroIdentificacion<<" ya se encuentra registrada "<<endl;
						incorrectos++;
					}			
					
				}else{
					cout<<endl<<"En la linea "<<numeroLinea<<": uno o varios datos no son validos"<<endl;
					incorrectos++;
				}							
			}
			
			tokens.clear();
			
		}
		
		myfile.close();
		cout<<endl<<endl<< "Desde el archivo "<<nombreArchivo<<", se han cargado exitosamente "<<correctos
		<<" registros; mientras que "<<incorrectos<<" registros presentaron problemas."<<endl<<endl;
		
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible."<<endl<<endl;
	}
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::cargarPaquetes(string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		
		int numeroLinea = 0;
		
		// Vector of string to save tokens
		vector <string> tokens;
		
		long correctos = 0, incorrectos = 0;
		
		while ( getline (myfile,line) ){
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 11 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}
			
			if(tokens.size() != 11 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;
				
			}else if(tokens.size() == 11 && numeroLinea != 1){
				
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
					&& this->validarCadenaAlfanumerica(codRegionReparto)
					&& this->validarCodigoOficina(codOficina)==true
					&& this->validarCadenaAlfabetica(ciudadOficina)==true 
					&& this->validarCadenaNumerica(pesoString)==true
					&& this->validarCadenaAlfanumerica(numeroGuia)==true && (cedulaRemitente!=cedulaDestinatario) ){
					
					Paquete paqueteComprob = this->buscarPaquete(numeroGuia);
					
					if (paqueteComprob.getNumeroGuia() == "-1"){ //no se ha registrado el paquete						
				
						Persona remitente = this->buscarPersona(cedulaRemitente);
						Persona destinatario = this->buscarPersona(cedulaDestinatario);
						
						if(remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1"){ //ya registrados ambos
						
							//mirar si está registrada ya la oficinaReparto
							
							OficinaReparto* oficinaReparto = this->buscarOficina(codOficina);
							
							RegionReparto regionReparto;
							
							if(oficinaReparto == NULL){ //no está registrada
							
								regionReparto.setCodigo(codRegionReparto); 
								regionReparto.setNombre(nombreRegionReparto);
								
								oficinaReparto = new OficinaReparto(codOficina, nombreOficina, direccionOficina, ciudadOficina);
							
								this->agregarOficina(oficinaReparto);	//REVISAR BIEN ESTO, CUÁL SERÍA LA OFICINA PADRE
								this->agregarRegion(oficinaReparto, regionReparto);
								
							}else{ //ya está registrada
							
								//mirar si está registrada ya la regionReparto
								regionReparto = this->buscarRegion(codRegionReparto);
								
								if(regionReparto.getCodigo() == "-1"){ //no está registrada
								
									regionReparto.setCodigo(codRegionReparto); 
									regionReparto.setNombre(nombreRegionReparto);
									
									this->agregarRegion(oficinaReparto, regionReparto); //cambios
								}
							}
						
							stringstream ss(pesoString);
							int peso;
							ss >> peso;
							Paquete paquete(cedulaRemitente,cedulaDestinatario,peso,tipoContenido,numeroGuia,codOficina,codRegionReparto);
							this->paquetes.push_back(paquete);
							correctos++;
							
						}else{
							cout<<endl<<"En la linea "<<numeroLinea<<": no se puede registrar el paquete con numero de guia "<<numeroGuia<<": remitente y/o destinatario no registrado(s)"<<endl;
							incorrectos++;
						}

					}else{
						cout<<endl<<"En la linea "<<numeroLinea<<": ya se encuentra registrado el paquete con numero guia "<<numeroGuia<<" del archivo "<<nombreArchivo<<endl;
						incorrectos++;
					}					
						
				}else{
					cout<<endl<<"En la linea "<<numeroLinea<<": uno o varios datos no son validos"<<endl;
					incorrectos++;
				}			
				
			}
			
			tokens.clear();
			
		}
		
		myfile.close();
		cout<<endl<<endl<< "Desde el archivo "<<nombreArchivo<<", se han cargado exitosamente "<<correctos
		<<" registros; mientras que "<<incorrectos<<" registros presentaron problemas"<<endl<<endl;
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible"<<endl<<endl;
	}
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::registrarPersona(string numeroIdentificacion, string nombre, string apellidos, 
			string direccion, string ciudad, string telefono){
				
	Persona persona(numeroIdentificacion,nombre,apellidos,direccion,ciudad,telefono);
	this->personas.push_back(persona);	
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::registrarPaquete(string remitente, string destinatario, int peso, string tipoContenido, string numeroGuia,
	string oficinaReparto, string regionReparto){
	
	Paquete paquete(remitente,destinatario,peso,tipoContenido,numeroGuia,oficinaReparto,regionReparto);
	this->paquetes.push_back(paquete);		
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::conteoPaquetes(){

	long numPaquetes = this->paquetes.size();	
	
	if(numPaquetes == 0){
		cout<<endl<<endl<< "No existe informacion de paquetes registrada en el sistema"<<endl<<endl;
	}else{
		cout<<endl<<endl<<"Se encuentran en el sistema "<<numPaquetes<<" pendientes por entregar. Estan distribuidos asi:"<<endl<<endl;
		
		long cantidad = 0;
		
		list< Nodo<OficinaReparto*>* > listaNodos;
		this->arbol.returnNodes(listaNodos);
		
		OficinaReparto* oficinaReparto;	
		
		for(list< Nodo<OficinaReparto*>* >::iterator it = listaNodos.begin(); it != listaNodos.end( );	it++){
							
			oficinaReparto = (*it)->obtenerDato();

			list<RegionReparto> regiones = oficinaReparto->getRegiones();
			
			for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){
				
				cantidad = 0;
				for(list< Paquete >::iterator it = this->paquetes.begin(); it != this->paquetes.end(); it++ ){
					if((*it).getRegionReparto() == (*it2).getCodigo()){
						cantidad++;
					}	
				}
				if(cantidad != 0){
					cout<<cantidad<<" en la oficina "<<oficinaReparto->getCodigo()<<", region de reparto "<<(*it2).getNombre()<<endl;			
				}
								
			}			
							
		}			
				
	}		
			
}

//---------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------
Paquete EmpresaMensajeria::buscarPaquete(string numeroGuia){
	
	Paquete paquete;
	bool b = false;
	
	if(this->paquetes.size() > 0){
		
		for(list< Paquete >::iterator it = this->paquetes.begin(); it != this->paquetes.end( );	it++){
			if((*it).getNumeroGuia() == numeroGuia){
				b = true;
				paquete = *it;
				break;
			}
		}
		
	}
	
	if(b == false){
		paquete.setNumeroGuia("-1");
	}
	
	return paquete;
}

//---------------------------------------------------------------------------------------------------
OficinaReparto* EmpresaMensajeria::buscarOficina(string codigoOficina){	

	OficinaReparto* oficina = NULL;
	OficinaReparto* aux = new OficinaReparto();
	aux->setCodigo(codigoOficina);
	
	Nodo<OficinaReparto*>* nodo = this->arbol.buscarNodo(aux);
	
	if(nodo != NULL){
		oficina = nodo->obtenerDato();
	}
	
	return oficina;
}

//---------------------------------------------------------------------------------------------------
RegionReparto EmpresaMensajeria::buscarRegion(string codigoRegion){
	
	RegionReparto region;
	region.setCodigo("-1");
	
	list< Nodo<OficinaReparto*>* > listaNodos;
	this->arbol.returnNodes(listaNodos);
		
	OficinaReparto* oficinaReparto;	
		
	for(list< Nodo<OficinaReparto*>* >::iterator it = listaNodos.begin(); it != listaNodos.end( );	it++){							
		oficinaReparto = (*it)->obtenerDato();		
		region = oficinaReparto->buscarRegion(codigoRegion);	
		if(region.getCodigo() != "-1"){
			break;
		}
	}
	return region;
}

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::validarCadenaAlfabetica(string& cadena){ //true si cumple
	
	bool b = true;

    for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
        if( isdigit(ch) ){
            b = false;
        }
    }
	
	return b;
}

//---------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::validarCadenaAlfanumerica(string& cadena){ //true si cumple
	
	bool b = true;

    for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
		//los números validan posibles tildes y ñ
        if( !((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch == ' ') || (isdigit(ch)) ) ){
            b = false;
        }
    }
	
	return b;
}

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::validarCodigoOficina(string& cadena){ //true si cumple
	
	int numLetras = 0, numDigitos = 0;
	
	for (int i=0; i<cadena.size(); i++){
        char ch = cadena[i];
        if( !(isdigit(ch)) ){
            numLetras++;			
        }
		if( isdigit(ch) ){
            numDigitos++;
        }
    }
	
	bool b;
	
	if(numLetras == 3 && numDigitos == 5){
		b = true;
	}else{
		b = false;
	}
	
	return b;
}

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::agregarOficina(OficinaReparto* general, OficinaReparto* secundaria){
	return this->arbol.insertarNodo(general, secundaria);
}

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::agregarOficina(OficinaReparto* secundaria){
	return this->arbol.insertarNodo(this->arbol.obtenerRaiz()->obtenerDato(), secundaria);
}

//---------------------------------------------------------------------------------------------------
bool EmpresaMensajeria::agregarRegion(OficinaReparto* oficina, RegionReparto region){
	oficina->agregarRegion(region);
	return true;
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::cargarOficinas(std::string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		
		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;
		
		long correctos = 0, incorrectos = 0;
		
		OficinaReparto* oficinaGeneral = NULL;
		
		while ( getline (myfile,line) ){
			
			line.erase(remove(line.begin(), line.end(), '"'), line.end()); //eliminar los " de la línea
			
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 4 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}			
			
			if(tokens.size() != 4 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;
				
			}else if (tokens.size() == 4 && numeroLinea != 1){
				string codOficina = tokens[0];
				string nombreOficina = tokens[1];
				string direccionOficina = tokens[2];
				string ciudadOficina = tokens[3];
				
				//revisar si datos son válidos
				if(this->validarCodigoOficina(codOficina)==true	&& this->validarCadenaAlfabetica(ciudadOficina)==true) { 
					
					OficinaReparto* oficinaReparto = this->buscarOficina(codOficina);							
							
					if(oficinaReparto == NULL){ //no está registrada
								
						oficinaReparto = new OficinaReparto(codOficina, nombreOficina, direccionOficina, ciudadOficina);
						
						if(numeroLinea == 2){ //primera oficina del archivo
							oficinaGeneral = oficinaReparto;
							this->agregarOficina(oficinaReparto); //es la oficina general de la ciudad
							correctos++;
						}else{
							if(oficinaGeneral != NULL){
								this->agregarOficina(oficinaGeneral, oficinaReparto); //es una oficina secundaria de la ciudad
								correctos++;
							}else{
								cout<<endl<<"En la linea "<<numeroLinea<<": la oficina con codigo "<<codOficina<<" no pudo registrarse por problemas de registro de su oficina general"<<endl;
								incorrectos++;	
							}
							
						}
								
					}else{	//ya está registrada
						if(numeroLinea == 2){
							oficinaGeneral = oficinaReparto;
						}
						cout<<endl<<"En la linea "<<numeroLinea<<": la oficina con codigo "<<codOficina<<" ya se encuentra registrada "<<endl;
						incorrectos++;		
					}
					
				}else{
					cout<<endl<<"En la linea "<<numeroLinea<<": uno o varios datos no son validos"<<endl;
					incorrectos++;
				}							
			}
			
			tokens.clear();
			
		}
		
		myfile.close();
		cout<<endl<<endl<< "Desde el archivo "<<nombreArchivo<<", se han cargado exitosamente "<<correctos
		<<" registros; mientras que "<<incorrectos<<" registros presentaron problemas."<<endl<<endl;
		
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible."<<endl<<endl;
	}	
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::cargarRegiones(std::string nombreArchivo){
	
	string line;
	ifstream myfile (nombreArchivo);
	
	if (myfile.is_open()){
		
		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;
		
		long correctos = 0, incorrectos = 0;
		
		while ( getline (myfile,line) ){
			
			line.erase(remove(line.begin(), line.end(), '"'), line.end()); //eliminar los " de la línea
			
			numeroLinea++;
			// stringstream class check1
			stringstream check(line);
				 
			string intermediate;
				 
			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}
			
			if(tokens.size() != 3 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}			
			
			if(tokens.size() != 3 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;
				
			}else if (tokens.size() == 3 && numeroLinea != 1){
				string codRegionReparto = tokens[0];
				string nombreRegionReparto = tokens[1];
				string codOficina = tokens[2];
				
				//revisar si datos son válidos
				if( this->validarCodigoOficina(codOficina)==true && this->validarCadenaAlfanumerica(codRegionReparto) ) { 
					
					RegionReparto regionReparto = this->buscarRegion(codRegionReparto);
								
					if(regionReparto.getCodigo() == "-1"){ //no está registrada
					
						OficinaReparto* oficinaReparto = this->buscarOficina(codOficina);
							
						if(oficinaReparto != NULL){ // está registrada
							regionReparto.setCodigo(codRegionReparto); 
							regionReparto.setNombre(nombreRegionReparto);									
							this->agregarRegion(oficinaReparto, regionReparto); 
							correctos++;
						}else{
							cout<<endl<<"En la linea "<<numeroLinea<<": la oficina con codigo "<<codOficina<<" no se encuentra registrada. No se puede registrar la region"<<endl;
							incorrectos++;		
						}				
								
					}else{	//ya está registrada
						cout<<endl<<"En la linea "<<numeroLinea<<": la region con codigo "<<codRegionReparto<<" ya se encuentra registrada "<<endl;
						incorrectos++;		
					}
					
				}else{
					cout<<endl<<"En la linea "<<numeroLinea<<": uno o varios datos no son validos"<<endl;
					incorrectos++;
				}							
			}
			
			tokens.clear();
			
		}
		
		myfile.close();
		cout<<endl<<endl<< "Desde el archivo "<<nombreArchivo<<", se han cargado exitosamente "<<correctos
		<<" registros; mientras que "<<incorrectos<<" registros presentaron problemas."<<endl<<endl;
		
	}else{
		cout<<endl<<endl<< "El archivo "<<nombreArchivo<<" no existe o es ilegible."<<endl<<endl;
	}
	
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::repartirPaquetes(std::string codigoOficina){
	/*
	OficinaReparto* oficinaReparto = new OficinaReparto();
	oficinaReparto->setCodigo(codigoOficina);
	
	Nodo<OficinaReparto*>* nodo = this->arbol.buscarNodo(oficinaReparto);
	
	if(nodo == NULL){ //no está registrada la oficina
		cout<<endl<<endl<< "La oficina "<<codigoOficina<<" no esta registrada"<<endl<<endl;
	}else{

		list<OficinaReparto*> oficinasSecundarias;		
		this->arbol.returnLeafs(nodo, oficinasSecundarias);
		
		list<RegionReparto> regiones;
		map <string, string> oficinasRegiones;
		queue<string> codigosRegiones;

		typename list<OficinaReparto*>::iterator it;		
		for(it = oficinasSecundarias.begin(); it != oficinasSecundarias.end(); it++){
			oficinaReparto = (*it);
			regiones = oficinaReparto->getRegiones();
			for(list<RegionReparto>::iterator it = regiones.begin(); it != regiones.end( ); it++){
				oficinasRegiones.insert(pair <string, string> ( (*it).getCodigo() , oficinaReparto.getCodigo() ));
				codigosRegiones.push( (*it).getCodigo() );
			}
		}
		
		int regionesReparto = regiones.size();
					
		if(regionesReparto == 0){ //no regiones asociadas ni para la oficina ni para sus secundarias (en caso de tenerlas)
			cout<<endl<<endl<< "La oficina "<<codigoOficina<<" no tiene regiones de reparto asociadas"<<endl<<endl;
		}else{
			long paquetesRepartidos = 0, paquetesARepartir = this->paquetes.size();
			int oficinasReparto = oficinasSecundarias.size();
			
			string codOficina, codRegion;
			
			if(paquetesARepartir == regionesReparto){ //#paquetes = # regiones
			
				queue<Paquete> auxPaquetes (this->paquetes); //inicializado como copia de this->paquetes 
				while(auxPaquetes.size() > 0){
					
					paquete = auxPaquetes.front(); //tomar paquete en el tope
					auxPaquetes.pop();	//eliminar el tope de la pila
					this->paquetes.pop(); //eliminar el tope de la pila original
					
					codRegion = codigosRegiones.front();	//tomar región en tope de la pila
					codigosRegiones.pop();	//eliminar tope de la pila
					
					codOficina = oficinasRegiones.at(codRegion);	//buscar el codigo de oficina de la respectiva región, almacenado en el map
					
					paquete.setOficinaReparto(codOficina); //establecer al paquete la nueva oficina
					paquete.setRegionReparto(codRegion); //establecer al paquete la nueva region de la respectiva oficina
					
					this->paquetes.push(paquete);	//insertar el paquete en la pila original
					
				}				
				
			}else if(paquetesARepartir < regionesReparto){ //#paquetes < # regiones
				
			}else if(paquetesARepartir > regionesReparto){ //#paquetes > # regiones
				
			}
			
			Paquete paquete;
			
			cout<<endl<<endl<< "Se han repartido exitosamente "<<paquetesRepartidos<<" paquetes en "<<regionesReparto
			<<" regiones de reparto de "<<oficinasReparto<<" oficinas "<<" secundarias a la oficina "<<codigoOficina<<endl<<endl;
		}
	
	}*/
}