#include "Nodo.h"

// ------------------------------------------------------------------------
template< class T >
Nodo<T>::Nodo() {
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>::Nodo(const T& val) {
	this->dato = val;
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>::~Nodo() {
	typename TList::iterator it;
	for (it = this->desc.begin(); it != this->desc.end(); it++){
		delete *it;
	}
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
T& Nodo<T>::obtenerDato() {
	return this->dato;
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::fijarDato(T& val) {
	this->dato = val;
}

// ------------------------------------------------------------------------
template< class T >
typename Nodo<T>::TList& Nodo<T>::obtenerDesc() {
	return this->desc;
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::fijarDesc(TList& listaDesc) {
	this->desc = listaDesc;
}

// ------------------------------------------------------------------------
template< class T >
bool Nodo<T>::adicionarDesc(T& nval) {
	bool b = false;
	Nodo<T>* nodo = new Nodo<T>;
	nodo->dato = nval;
	this->desc.push_back(nodo);
	b = true;
	return b;
}

// ------------------------------------------------------------------------
template< class T >
bool Nodo<T>::eliminarDesc(T& val) {
	
	bool b = false;
	typename TList::iterator it;
	int posicion = 0;
	for (it = this->desc.begin(); it != this->desc.end(); it++){
		posicion++;
		if( val == (*it)->obtenerDato() ){
			b = true;
			break;
		}
	}
	
	if(b == true){ //se encontró el nodo a eliminar
	
		typedef std::list< Nodo<T>* > TList;
		TList descendientes = (*it)->obtenerDesc(); //lista de descendientes del nodo a eliminar
		int numDes = descendientes.size();
		
		if( numDes > 0 ){ //si el nodo a eliminar tiene descendientes	
		
			it = this->desc.begin();
			advance (it,posicion-1);   //avanzar a la posicion ocupada por el nodo anterior
			
			this->desc.splice (it, descendientes); //insertar todos los descendientes del nodo eliminado en el mismo orden
													//en el lugar ocupado por el eliminado				
		}
		
		it = this->desc.begin();
		advance (it,posicion-1+numDes);
		this->desc.erase(it);	//eliminar el nodo requerido
	
	}	
	return b;
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>* Nodo<T>::buscarDesc(T& val) {
	
	Nodo<T>* p_it;
	typename TList::iterator it;
  
	for (it = this->desc.begin(); it != this->desc.end(); it++) {
		p_it = *it;
		if (p_it->obtenerDato() == val)
		  break;
	}
	return p_it;
  
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::limpiarLista() {
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Nodo<T>::numDesc() {
	return this->desc.size();	
}

// ------------------------------------------------------------------------
template< class T >
bool Nodo<T>::insertarNodo(T& padre, T& n) {
	
	bool b = false;
	
	if (this->dato == padre){ //si este nodo es el padre puede insertarlo		
		this->adicionarDesc(n);	
		b = true;		
	}else{ //si este nodo no es el padre
		typename TList::iterator it;
		for(it = this->desc.begin(); it != this->desc.end(); it++){
			b = (*it)->insertarNodo(padre, n);		
			if (b == true){
				break;
			}
		}
	}
	return b;
}

// ------------------------------------------------------------------------
//pista: recursividad
template< class T >
bool Nodo<T>::eliminarNodo(T& n) {
	
	bool b = false;
	typename TList::iterator it;
	
	b = this->eliminarDesc(n);
	
	if (b == false){
		//si no se ha eliminado el nodo
		for(it = this->desc.begin(); it != this->desc.end(); it++){		
			b = (*it)->eliminarNodo(n);
		}
	}
	return b;	
}

// ------------------------------------------------------------------------
template< class T >
Nodo<T>* Nodo<T>::buscarNodo(T& val) {	

	Nodo<T>* nodo = NULL;
	bool b = false;
	//modificación respecto al TAD original
	if(val->getCodigo() == this->dato->getCodigo()){
		nodo = this;
	}else{	
		typename TList::iterator it;	
		for(it = this->desc.begin(); it != this->desc.end(); it++){		
			nodo = (*it)->buscarNodo(val);
			if(nodo != NULL){
				break;
			}
		}
	}
	
	return nodo;
}

// ------------------------------------------------------------------------
template< class T >
int Nodo<T>::altura() {	

	int altura = 0, alturaMayor = 0;
	
	if( this->numDesc() == 0 ){
		return 0;
	}else{		
		typename TList::iterator it;
		for(it = this->desc.begin(); it != this->desc.end(); it++){
			altura = 1; 
			altura += (*it)->altura();
			if(altura > alturaMayor){
				alturaMayor = altura;
			}
		}		
		return alturaMayor;
	}
	
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Nodo<T>::tamano() {
	
	unsigned int tamano = this->desc.size();
	
	typename TList::iterator it;
	for(it = this->desc.begin(); it != this->desc.end(); it++){
		tamano += (*it)->tamano();
	}
	
	return tamano;
  
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::preOrden() {
	
	std::cout << this->dato << "\t";
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
		  (*it)->preOrden();
		}
	}
	
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::posOrden() {	

	typename TList::iterator it;
	if(this->desc.size() > 0){
		it = this->desc.begin(); //situado en primer nodo a la izquierda
		(*it)->posOrden();
	}
	
	if(this->desc.size() > 1){
		it = this->desc.begin();
		it++;
		for(it; it != this->desc.end(); it++){
			(*it)->posOrden();
		}
	}
	
	std::cout << this->dato << "\t";
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::inOrden() {
	
	typename TList::iterator it;
	if(this->desc.size() > 0){
		it = this->desc.begin(); //situado en primer nodo a la izquierda
		(*it)->inOrden();
	}
	
	std::cout << this->dato << "\t";
	
	if(this->desc.size() > 1){
		it = this->desc.begin();
		it++;
		for(it; it != this->desc.end(); it++){
			(*it)->inOrden();
		}
	}
  
}

// ------------------------------------------------------------------------
template< class T >
int Nodo<T>::grado() { //Grado (orden) de un árbol: el máximo de los grados de los nodos del árbol
	
	int orden = this->desc.size(), ordenMayor;
	ordenMayor = orden;
	
	typename TList::iterator it;
	for(it = this->desc.begin(); it != this->desc.end(); it++){
		orden = (*it)->grado();
		if(orden > ordenMayor){
			ordenMayor = orden;
		}
	}
	
	return ordenMayor;
  
}

// ------------------------------------------------------------------------ 
/* Print nodes at a given level */
template< class T >
void Nodo<T>::printGivenLevel(Nodo<T>* root, int level)
{
    if (root == NULL)
        return;
    if (level == 0)
        std::cout<<root->dato<<"\t";
    else if (level > 0)
    {
		typename TList::iterator it;
		for(it = root->desc.begin(); it != root->desc.end(); it++){
			Nodo<T>* nodo = *it;
			printGivenLevel(nodo, level-1);
		}        
    }
}

// ------------------------------------------------------------------------ 
/* Function to print level order traversal a tree*/
template< class T >
void Nodo<T>::printLevelOrder(Nodo<T>* root)
{
    int h = root->altura();
    int i;
    for (i=0; i<=h; i++)
        printGivenLevel(root, i);
} 

// ------------------------------------------------------------------------
/* Helper function for getLevel().  It returns level of the data if data is
   present in tree, otherwise returns -1.*/
template< class T >
int Nodo<T>::getLevelUtil(Nodo<T>* node, T key, int level)
{
    if (node == NULL)
        return -1;
 
    if (node->dato == key)
        return level;
	
	int downlevel = -1;
	
	typename TList::iterator it;
	
	if(node->desc.size() > 0){
		it = node->desc.begin(); //situado en primer nodo a la izquierda
		Nodo<T>* izquierdo = (*it);
		downlevel = getLevelUtil(izquierdo, key, level+1);
	}
   
    if (downlevel != -1)
        return downlevel;
	
	if(node->desc.size() > 1){
		it = node->desc.begin();
		it++;
		for(it; it != node->desc.end(); it++){ //los de la derecha
			Nodo<T>* derecho = (*it);
			downlevel = getLevelUtil(derecho, key, level+1);
		}
	} 
    
    return downlevel;
}
 
// ------------------------------------------------------------------------
/* Returns level of given data value */
template< class T >
int Nodo<T>::getLevel(Nodo<T>* node, T key)
{
    return getLevelUtil(node,key,0); //first level is zero
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::returnNodes(Nodo<T>* root, std::list< Nodo<T>* >& lista){
	
    int h = root->altura();
    int i;
    for (i=0; i<=h; i++)
        returnNodesGivenLevel(root, i, lista);
	
}

// ------------------------------------------------------------------------ 
template< class T >
void Nodo<T>::returnNodesGivenLevel(Nodo<T>* root, int level, std::list< Nodo<T>* >& lista){
	
    if (root == NULL)
        return;
    if (level == 0)
        lista.push_back(root);
    else if (level > 0)
    {
		typename TList::iterator it;
		for(it = root->desc.begin(); it != root->desc.end(); it++){
			Nodo<T>* nodo = *it;
			returnNodesGivenLevel(nodo, level-1, lista);
		}        
    }
	
}

// ------------------------------------------------------------------------
template< class T >
void Nodo<T>::returnValues(Nodo<T>* root, std::list<T>& lista){
    int h = root->altura();
    int i;
    for (i=0; i<=h; i++)
        returnValuesGivenLevel(root, i, lista);
}

// ------------------------------------------------------------------------ 
template< class T >
void Nodo<T>::returnValuesGivenLevel(Nodo<T>* root, int level, std::list<T>& lista){
	
    if (root == NULL)
        return;
    if (level == 0)
        lista.push_back(root->dato);
    else if (level > 0)
    {
		typename TList::iterator it;
		for(it = root->desc.begin(); it != root->desc.end(); it++){
			Nodo<T>* nodo = *it;
			returnValuesGivenLevel(nodo, level-1, lista);
		}        
    }
	
}

// eof - Nodo.hxx