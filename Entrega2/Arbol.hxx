#include "Arbol.h"

// ------------------------------------------------------------------------
template< class T >
Arbol<T>::Arbol() : raiz(NULL){}

// ------------------------------------------------------------------------
template< class T >
Arbol<T>::Arbol(const T& val) {
	Nodo<T> *nnodo = new Nodo<T>(val);
	this->raiz = nnodo;
}

// ------------------------------------------------------------------------
template< class T >
Arbol<T>::~Arbol() {
	if (this->raiz != NULL){
		delete this->raiz;
	}
}

// ------------------------------------------------------------------------
template< class T >
bool Arbol<T>::esVacio() {
	if (this->raiz == NULL){
		return true;
	}else{
		return false;
	}
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>* Arbol<T>::obtenerRaiz() {
	return this->raiz;
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::fijarRaiz(T& val) {
	Nodo<T>* nodo = new Nodo<T>(val);
	this->raiz = nodo;
}

// ------------------------------------------------------------------------
template< class T >
bool Arbol<T>::insertarNodo(T& padre, T& n) {
	bool ins = false;
	if (!this->esVacio()) {
		ins = this->raiz->insertarNodo(padre,n);
	}
	return ins;
}

// ------------------------------------------------------------------------
template< class T >
bool Arbol<T>::eliminarNodo(T& n) {
	
	bool ins = false;
	if (!this->esVacio()) {
		
		if(this->raiz->obtenerDato() == n){ //la raíz se va a eliminar
			delete this->raiz;
			this->raiz = NULL;
			ins = true;
		}else{ //tiene varios nodos
			ins = this->raiz->eliminarNodo(n);
		}	
	}
	return ins;
	
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>* Arbol<T>::buscarNodo(T& val) {

	if( this->esVacio() == true ){
		return NULL;
	}else{		
		return this->raiz->buscarNodo(val);
	}
	
}

// ------------------------------------------------------------------------
template< class T >
int Arbol<T>::altura() {
	
	if( !this->esVacio() ){
		if(this->tamano() == 1){
			return 0;
		}else{
			return this->raiz->altura();
		}
	}else{
		return 0;
	}
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Arbol<T>::tamano() {
	
	if( !this->esVacio() ){
		return 1+this->raiz->tamano();
	}else{
		return 0;
	}  
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::preOrden() {
	
	if (!this->esVacio()) {
		this->raiz->preOrden();
		std::cout << std::endl;
	}
  
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::posOrden() {
	
	if (!this->esVacio()) {
		this->raiz->posOrden();
		std::cout << std::endl;
	}
  
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::inOrden() {
	
	if (!this->esVacio()) {
		this->raiz->inOrden();
		std::cout << std::endl;
	}
  
}

// ------------------------------------------------------------------------
template< class T >
int Arbol<T>::grado() {
	if( !this->esVacio() ){
		return this->raiz->grado();
	}else{
		return 0;
	}
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::printGivenLevel(int level){
	if( !this->esVacio() ){
		this->raiz->printGivenLevel(this->raiz, level);
	}
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::printLevelOrder(){
	if( !this->esVacio() ){
		this->raiz->printLevelOrder(this->raiz);
	}
}

// ------------------------------------------------------------------------
template< class T >
int Arbol<T>::getLevel(T key){
	if(this->esVacio() == false){
		this->raiz->getLevel(this->raiz, key);
	}else{
		return -1;
	}
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::returnNodes(std::list< Nodo<T>* >& lista){
	this->raiz->returnNodes(this->raiz, lista);
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::returnValues(std::list<T>& lista){
	this->raiz->returnValues(this->raiz, lista);
}

// ------------------------------------------------------------------------
template< class T >
void Arbol<T>::returnLeafs(Nodo<T>* nodo, std::list<T>& lista){
	this->raiz->returnLeafs(nodo, lista);
}

// eof - Arbol.hxx

