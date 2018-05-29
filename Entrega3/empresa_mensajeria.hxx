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

			if(tokens.size() != 7 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}

			if(tokens.size() != 7 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;

			}else if(tokens.size() == 7 && numeroLinea != 1){

				string cedulaRemitente = tokens[0];
				string cedulaDestinatario = tokens[1];
				string codRegionReparto = tokens[6];
				string codOficina = tokens[5];
				string pesoString = tokens[2];
				string tipoContenido = tokens[3];
				string numeroGuia = tokens[4];

				//revisar si datos son válidos

				if(this->validarCadenaAlfanumerica(cedulaRemitente)==true && this->validarCadenaAlfanumerica(cedulaDestinatario)== true
					&& this->validarCadenaAlfanumerica(codRegionReparto)
					&& this->validarCodigoOficina(codOficina)==true
					&& this->validarCadenaNumerica(pesoString)==true
					&& this->validarCadenaAlfanumerica(numeroGuia)==true && (cedulaRemitente!=cedulaDestinatario) ){

					Paquete paqueteComprob = this->buscarPaquete(numeroGuia);

					if (paqueteComprob.getNumeroGuia() == "-1"){ //no se ha registrado el paquete

						Persona remitente = this->buscarPersona(cedulaRemitente);
						Persona destinatario = this->buscarPersona(cedulaDestinatario);

						if(remitente.getNumeroIdentificacion() != "-1" && destinatario.getNumeroIdentificacion() != "-1"){ //ya registrados ambos

							OficinaReparto* oficinaReparto = this->buscarOficina(codOficina); //mirar si está registrada ya la oficinaReparto

							RegionReparto regionReparto = this->buscarRegion(codRegionReparto); //mirar si está registrada ya la regionReparto

							if(oficinaReparto != NULL && regionReparto.getCodigo() != "-1"){ //ambas están registradas

								stringstream ss(pesoString);
								int peso;
								ss >> peso;
								Paquete paquete(cedulaRemitente,cedulaDestinatario,peso,tipoContenido,numeroGuia,codOficina,codRegionReparto);

								oficinaReparto->agregarPaquete(paquete);

								correctos++;

							}else{
								cout<<endl<<"En la linea "<<numeroLinea<<": no se puede registrar el paquete con numero de guia "<<numeroGuia<<": oficina y/o region no registrada(s)"<<endl;
								incorrectos++;
							}

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
	string oficinaRecepcion, string regionReparto){

	OficinaReparto* oficinaReparto = this->buscarOficina(oficinaRecepcion);

	Paquete paquete(remitente,destinatario,peso,tipoContenido,numeroGuia,oficinaRecepcion,regionReparto);
	oficinaReparto->agregarPaquete(paquete);
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::conteoPaquetes(){

	list<OficinaReparto*> listaOficinas;
	this->arbol.returnValues(listaOficinas);

	list<Paquete> paquetes;

	for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end(); it++){
		paquetes.splice (paquetes.end(), (*it)->getPaquetes() );
	}

	if(paquetes.size() == 0){
		cout<<endl<<endl<< "No existe informacion de paquetes registrada en el sistema"<<endl<<endl;
	}else{
		cout<<endl<<endl<<"Se encuentran en el sistema "<<paquetes.size()<<" pendientes por entregar. Estan distribuidos asi:"<<endl<<endl;

		list<RegionReparto> regiones;

		for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end(); it++){
			regiones.splice (regiones.end(), (*it)->getRegiones() ); //conseguir todas las regiones
		}

		long cantidad = 0;

		OficinaReparto* oficinaReparto;

		for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end( );	it++){

			oficinaReparto = (*it);

			for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){

				cantidad = 0;
				for(list< Paquete >::iterator it3 = paquetes.begin(); it3 != paquetes.end(); it3++ ){
					if( (*it3).getRegionReparto() == (*it2).getCodigo() && ((*it3).getOficinaActual() == oficinaReparto->getCodigo() ) ){
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
void EmpresaMensajeria::conteoPaquetesRepartidos(){

	list<OficinaReparto*> listaOficinas;
	this->arbol.returnValues(listaOficinas);

	list<Paquete> paquetes;

	for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end(); it++){
		paquetes.splice (paquetes.end(), (*it)->getPaquetesRepartidos() );
	}

	if(paquetes.size() == 0){
		cout<<endl<<endl<< "No existe informacion de paquetes repartidos registrada en el sistema"<<endl<<endl;
	}else{
		cout<<endl<<endl<<"Se encuentran en el sistema "<<paquetes.size()<<" ya repartidos. Estan distribuidos asi:"<<endl<<endl;

		long cantidad = 0;

		OficinaReparto* oficinaReparto;
		list<RegionReparto> regiones;

		for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end( );	it++){

			oficinaReparto = (*it);
			regiones = oficinaReparto->getRegiones();

			for(list< RegionReparto >::iterator it2 = regiones.begin(); it2 != regiones.end( ); it2++){

				cantidad = 0;
				for(list< Paquete >::iterator it3 = paquetes.begin(); it3 != paquetes.end(); it3++ ){
					if( (*it3).getRegionReparto() == (*it2).getCodigo() ){
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

	list<OficinaReparto*> listaOficinas;
	this->arbol.returnValues(listaOficinas);

	std::list<Paquete> paquetes;

	OficinaReparto* oficinaReparto;

	for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end(); it++){

		oficinaReparto = *it;
		paquete = oficinaReparto->buscarPaquete(numeroGuia);
		if(paquete.getNumeroGuia() != "-1"){
			break;
		}

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
        if( !( isdigit(ch) || ch=='.' ) ){
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

		string ciudadActual;
		bool cambioCiudad = false;

		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;

		long correctos = 0, incorrectos = 0;

		OficinaReparto* oficinaGeneral = NULL;
		int idOficinaGeneral, idOficinaSecundaria;

		while ( getline (myfile,line) ){

			//line.erase(remove(line.begin(), line.end(), '"'), line.end()); //eliminar los " de la línea
			//line.erase(remove(line.begin(), line.end(), ' '), line.end()); //eliminar los espacios en blanco de la línea

			numeroLinea++;
			// stringstream class check1
			stringstream check(line);

			string intermediate;

			// Tokenizing w.r.t. coma ','
			while(getline(check, intermediate, ',')){
				tokens.push_back(intermediate);
			}

			if(tokens.size() != 5 && numeroLinea == 1){
				cout<<endl<<endl<<"El archivo "<<nombreArchivo<<" no contiene informacion valida"<<endl<<endl;
				break;
			}

			if(tokens.size() != 5 && numeroLinea != 1){
				cout<<endl<<"En la linea "<<numeroLinea<<": datos incompletos"<<endl;
				incorrectos++;

			}else if (tokens.size() == 5 && numeroLinea != 1){
				string codOficina = tokens[0];
				string nombreOficina = tokens[1];
				string direccionOficina = tokens[2];
				string ciudadOficina = tokens[3];
				string distanciaAOficinaPadre = tokens[4];

				//revisar si datos son válidos
				if(this->validarCodigoOficina(codOficina)==true	&& this->validarCadenaAlfabetica(ciudadOficina)==true) {

					OficinaReparto* oficinaReparto = this->buscarOficina(codOficina);

					if(oficinaReparto == NULL){ //no está registrada

						oficinaReparto = new OficinaReparto(codOficina, nombreOficina, direccionOficina, ciudadOficina);

						if(numeroLinea == 2){ //primera oficina del archivo
							ciudadActual = ciudadOficina;
							oficinaGeneral = oficinaReparto;
							this->agregarOficina(oficinaReparto); //es la oficina general de la ciudad
							idOficinaGeneral = this->grafo.AddVertex( oficinaReparto );
							correctos++;
						}else{

							if(ciudadOficina != ciudadActual){
								ciudadActual = ciudadOficina;
								cambioCiudad = true;
							}

							if(oficinaGeneral != NULL){
								if(cambioCiudad == false){

									this->agregarOficina(oficinaGeneral, oficinaReparto); //es una oficina secundaria de una ciudad
									idOficinaSecundaria = this->grafo.AddVertex( oficinaReparto );

									stringstream ss(distanciaAOficinaPadre);
									float distanciaAPadre;
									ss >> distanciaAPadre;

									this->grafo.AddEdge( idOficinaGeneral, idOficinaSecundaria, distanciaAPadre );
									this->grafo.AddEdge( idOficinaSecundaria, idOficinaGeneral, distanciaAPadre );
									correctos++;
								}else{
									oficinaGeneral = oficinaReparto;
									this->agregarOficina(oficinaReparto); //es la oficina general de otra ciudad
									idOficinaGeneral = this->grafo.AddVertex( oficinaReparto );
									correctos++;
									cambioCiudad = false;
								}
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

			//line.erase(remove(line.begin(), line.end(), '"'), line.end()); //eliminar los " de la línea
			//line.erase(remove(line.begin(), line.end(), ' '), line.end()); //eliminar los espacios en blanco de la línea

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
				string codRegionReparto = tokens[0];
				string nombreRegionReparto = tokens[1];
				string codOficina = tokens[2];
				string distanciaAOficinaPadre = tokens[3];

				/*if(this->validarCodigoOficina(codOficina)==false){
					cout<<endl<<"Error con codOficina"<<endl;
				}
				if(this->validarCadenaAlfanumerica(codRegionReparto)==false){
					cout<<endl<<"Error con codRegionReparto"<<endl;
				}
				if(this->validarCadenaNumerica(distanciaAOficinaPadre)==false){
					cout<<endl<<"Error con distanciaAOficinaPadre"<<endl;
				}*/

				//revisar si datos son válidos
				if( this->validarCodigoOficina(codOficina)==true && this->validarCadenaAlfanumerica(codRegionReparto)==true
					&& this->validarCadenaNumerica(distanciaAOficinaPadre)==true ) {

					RegionReparto regionReparto = this->buscarRegion(codRegionReparto);

					if(regionReparto.getCodigo() == "-1"){ //no está registrada

						OficinaReparto* oficinaReparto = this->buscarOficina(codOficina);

						if(oficinaReparto != NULL){ // está registrada

							stringstream ss(distanciaAOficinaPadre);
							float distanciaAPadre;
							ss >> distanciaAPadre;

							regionReparto.setCodigo(codRegionReparto);
							regionReparto.setNombre(nombreRegionReparto);
							regionReparto.setDistanciaAOficinaPadre(distanciaAPadre);

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
void EmpresaMensajeria::repartirPaquetes(std::string codigoOficina){ //recibe el codigo de oficina de destino para repartir paquetes

	OficinaReparto* oficinaReparto = new OficinaReparto();
	oficinaReparto->setCodigo(codigoOficina);

	Nodo<OficinaReparto*>* nodo = this->arbol.buscarNodo(oficinaReparto); //trae el nodo con la oficina buscada

	if(nodo == NULL){ //no está registrada la oficina

		cout<<endl<<endl<< "La oficina "<<codigoOficina<<" no esta registrada"<<endl<<endl;

	}else{ //sí está registrada la oficina

		list<OficinaReparto*> oficinasSecundarias;
		this->arbol.returnLeafs(nodo, oficinasSecundarias); //trae las oficinas secundarias a la oficina buscada o la misma en caso de no tener

		list<RegionReparto> listRegiones;
		map <string, string> mapOficinasRegiones;

		typename list<OficinaReparto*>::iterator it;

		for(it = oficinasSecundarias.begin(); it != oficinasSecundarias.end(); it++){
			//cout<<endl<<"oficina es "<<(*it)->getNombre();
			oficinaReparto = (*it);
			listRegiones = oficinaReparto->getRegiones();

			for(list<RegionReparto>::iterator it2 = listRegiones.begin(); it2 != listRegiones.end( ); it2++){
				//cout<<endl<<"region es "<<(*it2).getNombre();
				mapOficinasRegiones.insert(pair <string, string> ( (*it2).getCodigo(), oficinaReparto->getCodigo() ));
			}
		}
		//cout<<endl<<"oficinas secundarias "<<oficinasSecundarias.size()<<endl;

		if(mapOficinasRegiones.size() == 0){ //no regiones asociadas ni para la oficina ni para sus secundarias (en caso de tenerlas)

			cout<<endl<<endl<< "La oficina "<<codigoOficina<<" no tiene regiones de reparto asociadas"<<endl<<endl;

		}else{

			list<OficinaReparto*> listaOficinas;
			this->arbol.returnValues(listaOficinas); //retorna las oficinas almacenadas

			list<Paquete> paquetes;

			for(list< OficinaReparto* >::iterator it = listaOficinas.begin(); it != listaOficinas.end(); it++){
				paquetes.splice (paquetes.end(), (*it)->getPaquetesARepartir() ); //conseguir todos los paquetes por repartir
			}

			queue<Paquete> colaPaquetes; //copiar lista de paquetes en una cola
			for(list< Paquete >::iterator it = paquetes.begin(); it != paquetes.end();	it++){
				colaPaquetes.push(*it);
			}

			long paquetesRepartidos = 0;

			Paquete paquete;
			string codOficina, codRegion;

			//cout<<endl<<"paquetes a repartir "<<paquetes.size()<<" y regiones a repartir "<<mapOficinasRegiones.size()<<endl;
			paquetes.clear();

			while(colaPaquetes.size() > 0){

				paquete = colaPaquetes.front(); //tomar paquete en el tope
				colaPaquetes.pop();	//eliminar el tope de la pila

				if ( mapOficinasRegiones.count(paquete.getRegionReparto()) > 0 ){ // la región de reparto del paquete es cubierta por la oficina deseada, entonces se reparte en ésta

					codRegion = paquete.getRegionReparto(); //toma el código de región de destino
					codOficina = mapOficinasRegiones.at(codRegion);	//buscar el codigo de oficina de la respectiva región, almacenado en el map

					oficinaReparto = this->buscarOficina(codOficina);
					paquete.setRepartido();
					oficinaReparto->agregarPaquete(paquete); //agrega el paquete a la oficina destino

					codOficina = paquete.getOficinaRecepcion(); //trae el código de oficina de recepción
					oficinaReparto = this->buscarOficina(codOficina);
					oficinaReparto->eliminarPaquete(paquete.getNumeroGuia()); //elimina el paquete de su oficina de recepción

					paquetesRepartidos++;
				}
			}

			cout<<endl<<endl<< "Se han repartido exitosamente "<<paquetesRepartidos<<" paquetes en "<<oficinasSecundarias.size()
			<<" oficinas de las regiones de reparto de la oficina "<<codigoOficina<<endl<<endl;
		}

	}
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::cargarConexiones(std::string nombreArchivo){

	string line;
	ifstream myfile (nombreArchivo);

	if (myfile.is_open()){

		int numeroLinea = 0;
		// Vector of string to save tokens
		vector <string> tokens;

		long correctos = 0, incorrectos = 0;

		int idOficinaGeneral, idOficinaSecundaria;

		while ( getline (myfile,line) ){

			//line.erase(remove(line.begin(), line.end(), ' '), line.end()); //eliminar los espacios en blanco de la línea

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
				string codOficina1 = tokens[0];
				string codOficina2 = tokens[1];
				string distancia = tokens[2];

				//revisar si datos son válidos
				if( this->validarCodigoOficina(codOficina1)==true && this->validarCodigoOficina(codOficina2)==true
					&& this->validarCadenaNumerica(distancia)==true ) {

					OficinaReparto* oficina1 = this->buscarOficina(codOficina1);
					OficinaReparto* oficina2 = this->buscarOficina(codOficina2);

					if(oficina1 != NULL && oficina2 != NULL){ //están registradas

						stringstream ss(distancia);
						float distanciaOficinas;
						ss >> distanciaOficinas;

						idOficinaGeneral = this->grafo.AddVertex( oficina1 );
						idOficinaSecundaria = this->grafo.AddVertex( oficina2 );

						if( this->grafo.HasArc(idOficinaGeneral,idOficinaSecundaria)==true ){	// ya están conectadas
							float* distanciaAnterior = this->grafo.GetCost(idOficinaGeneral,idOficinaSecundaria);
							if( distanciaOficinas < *distanciaAnterior ){
								this->grafo.DeleteEdge( idOficinaGeneral, idOficinaSecundaria ); //eliminar anterior arista
								this->grafo.DeleteEdge( idOficinaSecundaria, idOficinaGeneral ); //eliminar anterior arista
								this->grafo.AddEdge( idOficinaGeneral, idOficinaSecundaria, distanciaOficinas );
								this->grafo.AddEdge( idOficinaSecundaria, idOficinaGeneral, distanciaOficinas );
							}
						}else{ // aún no están conectadas
							this->grafo.AddEdge( idOficinaGeneral, idOficinaSecundaria, distanciaOficinas );
							this->grafo.AddEdge( idOficinaSecundaria, idOficinaGeneral, distanciaOficinas );
						}

						correctos++;

					}else{	//no está(n) registrada(s)
						if(oficina1 == NULL && oficina2 == NULL){
							cout<<endl<<"En la linea "<<numeroLinea<<": las oficinas no se encuentran registradas"<<endl;
						}else{
							if(oficina1 == NULL){
								cout<<endl<<"En la linea "<<numeroLinea<<": la oficina origen no se encuentra registrada"<<endl;
							}else if(oficina2 == NULL){
								cout<<endl<<"En la linea "<<numeroLinea<<": la oficina destino no se encuentra registrada"<<endl;
							}
						}
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
void EmpresaMensajeria::imprimirArbolYGrafo(){
	//this->arbol.printLevelOrder();
	this->grafo.Draw( "grafo.txt" );
}

//---------------------------------------------------------------------------------------------------
void EmpresaMensajeria::rutaReparto(std::string codigoOficinaOrigen, std::string codigoOficinaDestino){

	OficinaReparto* oficinaOrigen = this->buscarOficina(codigoOficinaOrigen);
	OficinaReparto* oficinaDestino = this->buscarOficina(codigoOficinaDestino);

	if( oficinaOrigen != NULL && oficinaDestino != NULL ){ //ambas oficinas están registradas

		int idOficinaOrigen = this->grafo.AddVertex( oficinaOrigen );
		int idOficinaDestino = this->grafo.AddVertex( oficinaDestino );

		vector< vector< unsigned long > > vectorDijkstra = this->grafo.Dijkstra( idOficinaOrigen, idOficinaDestino );
		vector< unsigned long > camino;

		typename vector< unsigned long >::iterator it;

		camino = vectorDijkstra[0];

		cout<<endl<<"La ruta de reparto mas corta que conecta las oficinas "<<codigoOficinaOrigen<<
		" y "<<codigoOficinaDestino<<" pasa por: ";
		for(it = camino.begin()+2; it != camino.end(); it++){
			cout<<(this->grafo.GetVertex(*it))->getCodigo();
			if(it == camino.end()-1){
				cout<<"; ";
			}else{
				cout<<", ";
			}
		}
		cout<<"con una longitud de "<<camino[1]<<" km."<<endl<<endl;

	}else{
		if( oficinaOrigen == NULL && oficinaDestino == NULL ){
			cout<<endl<<"La oficinas "<<codigoOficinaOrigen<<" y "<<codigoOficinaDestino<<" no se encuentran registradas en el sistema"<<endl<<endl;
		}else{
			if( oficinaOrigen == NULL ){
				cout<<endl<<"La oficina "<<codigoOficinaOrigen<<" no se encuentra registrada en el sistema"<<endl<<endl;
			}else if( oficinaDestino == NULL ){
				cout<<endl<<"La oficina "<<codigoOficinaDestino<<" no se encuentra registrada en el sistema"<<endl<<endl;
			}
		}
	}

}
