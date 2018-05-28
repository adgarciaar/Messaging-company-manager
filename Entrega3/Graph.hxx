#ifndef __PUJ__Graph__hxx__
#define __PUJ__Graph__hxx__

#include <fstream>
#include <cstdlib>
#include <queue>
#include <limits>
#include <sstream>

#include <stdio.h>
#include <limits.h>

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
PUJ::Graph< _TVertex, _TEdge >::
Graph( )
{
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
PUJ::Graph< _TVertex, _TEdge >::
 ~Graph( )
{
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
long PUJ::Graph< _TVertex, _TEdge >::
AddVertex( const _TVertex& v )
{
	long posicion;
	if( m_Vertices.size() == 0 ){
			
		TRow myRow;
		myRow.insert( std::pair< unsigned long, _TEdge* >( m_Vertices.size(), NULL) );
		m_Edges.insert( std::pair< unsigned long, TRow>( m_Vertices.size(), myRow) );	//se crea la matriz para el primer vértice
		posicion = m_Vertices.size();
		
		m_Vertices.push_back(v);
		
	}else{
		int conta = 0;
		bool b = false;
		typename std::vector< _TVertex >::iterator it;
		for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
			if(*it == v){
				b = true;
				posicion = conta;
			}
			conta++;
		}
		
		if(b == false){ //insertar el vértice porque no está registrado
		
			typename std::map<unsigned long, TRow>::iterator it2;			
			
			long ultimoElemento = m_Edges.size();
			while( m_Edges.count( ultimoElemento ) > 0 ){
				ultimoElemento++;
			}
			m_Vertices.push_back(v);
			
			TRow myRow;
			
			for(it2 = m_Edges.begin(); it2 != m_Edges.end(); it2++){
				myRow.insert( std::pair< unsigned long, _TEdge* >( it2->first, NULL) );
			}
			m_Edges.insert( std::pair< unsigned long, TRow>(ultimoElemento , myRow) );	//se agrega la fila para el vértice añadido			
			
			//insertar el nuevo vértice en el TRow de cada vértice (agregar la columna para todos					
			for(it2 = m_Edges.begin(); it2 != m_Edges.end( ); it2++){				
				TRow& tRow = it2->second;
				tRow.insert( std::pair< unsigned long, _TEdge* >( ultimoElemento, NULL) );								
			}	
			posicion = ultimoElemento;
		}
		
	}
	return posicion;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
AddEdge( unsigned long a, unsigned long b, _TEdge cost )
{
	if( m_Vertices.size() != 0 ){
		if( m_Edges.count(a)>0 && m_Edges.count(b)>0 ){ //entonces existen los respectivos vértices		
			if( (m_Edges.at(a)).at(b) == NULL ){ //no existe la arista		
				_TEdge* newEdge = new _TEdge;
				*newEdge = cost;
				(m_Edges.at(a)).at(b) = newEdge; //establecer la arista
			}			
		}
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
long PUJ::Graph< _TVertex, _TEdge >::
GetNumberOfVertices()
{
	return m_Vertices.size();
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
_TVertex PUJ::Graph< _TVertex, _TEdge >::
GetVertex( unsigned long i ){	

	_TVertex vertex;
	
	if(m_Vertices.size()>0){
		
		unsigned long posicion = retornarPosicionEnVertices( i );
		
		unsigned long contador = 0;
		typename std::vector< _TVertex >::iterator it;
		for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
			if(contador == posicion){
				vertex = *it;
			}
			contador++;
		}
		
	}
	
	return vertex;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
DeleteVertex( const _TVertex& v )
{
	if( m_Vertices.size() != 0 ){
		
		bool b = false;
		typename std::vector< _TVertex >::iterator it;
		long contador1 = 0;
		
		for(it = m_Vertices.begin(); it != m_Vertices.end( ); it++){
			if(*it == v){
				b = true;
				break;
			}
			contador1++;
		}
		
		if(b == true){ //el vértice está registrado, se procede a eliminarlo
			
			//tomar el número asignado al vértice
			long posicion = retornarIdEnMatriz(contador1);	
			
			typename std::map<unsigned long, TRow>::iterator it2;
			
			//borrar las columnas del vértice en la matriz
			typename std::map< unsigned long, _TEdge* >::iterator it3;			
			for( it2 = m_Edges.begin(); it2 != m_Edges.end(); it2++ ){
				TRow& tRow = it2->second;								
				it3 = tRow.find(posicion);
				tRow.erase( it3 );							
			}
			
			m_Vertices.erase(it); //borrar el vértice del vector
			
			it2 = m_Edges.find(posicion);			
			m_Edges.erase(it2);   //borrar fila del vértice en la matriz
			
		}	

	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
DeleteEdge( unsigned long a, unsigned long b)
{	
	if( m_Edges.count(a)>0 && m_Edges.count(b)>0 ){ //entonces existen los respectivos vértices		
		(m_Edges.at(a)).at(b) = NULL;		
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
bool PUJ::Graph< _TVertex, _TEdge >::
HasArc( unsigned long i, unsigned long j )
{
	if( m_Edges.count(i)>0 && m_Edges.count(j)>0 ){ //entonces existen los respectivos vértices	
		if ( (m_Edges.at(i)).at(j) != NULL){
			return true;
		}	
	}
	return false;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
_TEdge* PUJ::Graph< _TVertex, _TEdge >::
GetCost( unsigned long i, unsigned long j )
{
	_TEdge* edge = NULL;
	if( m_Edges.count(i)>0 && m_Edges.count(j)>0 ){ //entonces existen los respectivos vértices	
		if ( (m_Edges.at(i)).at(j) != NULL){
			edge = (m_Edges.at(i)).at(j);
		}
	}
	return edge;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
Draw( const std::string& filename )
{
	std::ofstream myfile (filename);
	
	if (myfile.is_open()){
		
		if( m_Vertices.size() != 0 ){ //hay vértices en el grafo
			
			myfile << "Vertices are\n\n";
			myfile <<"\t";
			typename std::vector< _TVertex >::iterator it;
			
			for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
				myfile <<(*it)->getCodigo()<< "\t";
			}
			
			myfile << "\n\n";
			myfile << "Matrix representing graph is\n\n";			
			
			typename std::map<unsigned long, TRow>::iterator it2;			
			for(it2 = m_Edges.begin(); it2 != m_Edges.end( ); it2++){
					
				TRow& tRow = it2->second;
				myfile <<"\t";
				
				typename std::map<unsigned long, _TEdge*>::iterator it3;
				for(it3 = tRow.begin(); it3 != tRow.end( ); it3++){	
					myfile <<it3->first<<"\t";	
				}
				myfile <<"\n"<<it2->first<< "\t";
					
				for(it3 = tRow.begin(); it3 != tRow.end( ); it3++){					
					_TEdge* edge = it3->second;
					if(edge == NULL){
						myfile <<"-"<<"\t";
					}else{
						myfile <<*edge<<"\t";	
					}						
				}				
				myfile << "\n\n";
				
			}
			
		}else{	//no hay vértices en el grafo
			myfile << "There are no vertices\n";
		}		
		
		myfile.close();

	}else{
		std::cout << "Unable to open file";
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
PrintPlaneGraph()
{
	typename std::vector< _TVertex >::iterator it;
	for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
		std::cout<<*it<<" ";
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
PrintPreorderGraph( unsigned long i ) //Depth-first search (DFS)
{
	if( m_Edges.count(i)>0 ){
		
		TMarks marcas;
		typename std::vector< _TVertex >::iterator it;
		for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
			marcas.push_back(false);
		}			
		PrintPreorderGraph_Dummy(i, marcas);
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
PrintLevelsGraph( unsigned long i ) //Breadth-first search (BFS)
{
	if( m_Edges.count(i)>0 ){
		//inicializar vector de marcas
		TMarks marcas;
		typename std::vector< _TVertex >::iterator it;
		for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
			marcas.push_back(false);
		}
	 
		// Create a queue for BFS
		std::queue< unsigned long > cola;

		// Mark the current node as visited and enqueue it
		unsigned long posicion = retornarPosicionEnVertices(i);
		marcas[posicion] = true;	//marca el nodo como visitado
		cola.push(i);
	 
		// 'it' will be used to get all adjacent
		// vertices of a vertex
		typename std::map<unsigned long, _TEdge*>::iterator it2;
	 
		while(!cola.empty()){
			
			i = cola.front();
			std::cout << i << " ";
			cola.pop();
			
			TRow tRow = m_Edges.at(i);
			
			for(it2 = tRow.begin(); it2 != tRow.end(); it2++){	
			
				if(it2->second != NULL){
					
					posicion = retornarPosicionEnVertices(it2->first);
					
					if(marcas[posicion] == false){
						marcas[posicion] = true;
						cola.push(it2->first);
					}
				}
			}
		}
	}
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
PrintPreorderGraph_Dummy( unsigned long i, TMarks& m )
{
	unsigned long posicion = retornarPosicionEnVertices(i);
	
    m[posicion] = true;	//marca el nodo como visitado
    std::cout << i << " ";	//se imprime el nodo
	TRow tRow = m_Edges.at(i);
	
	typename std::map<unsigned long, _TEdge*>::iterator it3;

	for(it3 = tRow.begin(); it3 != tRow.end( ); it3++){	
		
		if(it3->second != NULL){
						
			posicion = retornarPosicionEnVertices(it3->first);
			
			if(m[posicion] == false){
				PrintPreorderGraph_Dummy(it3->first, m);
			}
			
		}		
	}	
	
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
unsigned long PUJ::Graph< _TVertex, _TEdge >::
retornarPosicionEnVertices(unsigned long i){
	
	unsigned long contador = 0;
	typename std::map<unsigned long, TRow>::iterator it2;	
	for(it2 = m_Edges.begin(); it2 != m_Edges.end(); it2++){
		if(it2->first == i){
			break;
		}
		contador++;
	}
	
	unsigned long posicion = 0;	
	typename std::vector< _TVertex >::iterator it;
	for(it = m_Vertices.begin(); it != m_Vertices.end(); it++){
		if(contador == posicion){
			break;
		}
		posicion++;
	}
	return posicion;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
unsigned long PUJ::Graph< _TVertex, _TEdge >::
retornarIdEnMatriz(unsigned long pVector){ //retorna el identificador de un vértice en la posición i del vector de vértices
	
	unsigned long posicion = 0;	
	
	unsigned long contador = 0;
	typename std::map<unsigned long, TRow>::iterator it;	
	for(it = m_Edges.begin(); it != m_Edges.end(); it++){
		if(contador == pVector){
			posicion = it->first;
			break;
		}
		contador++;
	}
	
	return posicion;
}

// -------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
std::vector< std::vector< unsigned long > > PUJ::Graph< _TVertex, _TEdge >::
Dijkstra( unsigned long start, unsigned long end ){
	
	start = retornarPosicionEnVertices(start);
	
	unsigned long V = m_Vertices.size();     
	 
    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    unsigned long dist[V]; 
 
    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance 
    // from src to i is finalized
    bool sptSet[V];
 
    // Parent array to store
    // shortest path tree
    unsigned long parent[V];
 
    // Initialize all distances as 
    // INFINITE and stpSet[] as false
    for (unsigned long i = 0; i < V; i++)
    {        
        dist[i] = LONG_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex 
    // from itself is always 0
    dist[start] = 0;
	parent[start] = -1;
 
    // Find shortest path
    // for all vertices
    for (unsigned long count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed. 
        // u is always equal to src
        // in first iteration.
        unsigned long u = minDistance(dist, sptSet);
 
        // Mark the picked vertex 
        // as processed
        sptSet[u] = true;
 
        // Update dist value of the 
        // adjacent vertices of the
        // picked vertex.
        for (unsigned long v = 0; v < V; v++)
 
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and 
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && (m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v)) != NULL &&
                dist[u] + *((m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v))) < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + *((m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v)));
            } 
    }
 
	std::vector< std::vector< unsigned long > > caminosDijkstra;
	
    saveSolution(dist, parent, caminosDijkstra, start, end);
	
	return caminosDijkstra;	
}

// --------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
unsigned long PUJ::Graph< _TVertex, _TEdge >::
minDistance(unsigned long dist[], bool sptSet[]){
     
    // Initialize min value
    unsigned long min = LONG_MAX, min_index;
 
    for (unsigned long v = 0; v < m_Vertices.size(); v++)
        if (sptSet[v] == false &&  dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

// --------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
savePath(unsigned long parent[], unsigned long j, std::vector< unsigned long >& camino){
	
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;
 
    savePath(parent, parent[j], camino);
	
	camino.push_back(j);
}
 
// --------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
void PUJ::Graph< _TVertex, _TEdge >::
saveSolution(unsigned long dist[], unsigned long parent[], std::vector< std::vector< unsigned long > >& caminosDijkstra, 
	unsigned long start, unsigned long end){
	
	std::vector< unsigned long > camino;
	
    for (int i = 0; i < m_Vertices.size(); i++){        
	
		if(dist[i] < LONG_MAX){
			
			if(i == end){		
				camino.push_back(i); //Vértice final
				camino.push_back( dist[i] ); //Distancia a ese vértice
				camino.push_back( start ); //Vértice de inicio del camino
				
				savePath(parent, i, camino); //Camino a ese vértice
				
				caminosDijkstra.push_back(camino);		
				camino.clear();
			}
		}
    }
	
}

// --------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
std::vector< std::vector< unsigned long > > PUJ::Graph< _TVertex, _TEdge >::
Prim( unsigned long start ){
	
	std::vector< std::vector< unsigned long > > caminosPrim;
	std::vector< unsigned long > camino;
	
	start = retornarPosicionEnVertices(start);
	
	unsigned long V = m_Vertices.size();
	
	unsigned long parent[V]; // Array to store constructed MST
     unsigned long key[V];   // Key values used to pick minimum weight edge in cut
     bool mstSet[V];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (unsigned long i = 0; i < V; i++)
        key[i] = LONG_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[start] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[start] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (unsigned long count = 0; count < V-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        unsigned long u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (unsigned long v = 0; v < V; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if ( (m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v)) != NULL && mstSet[v] == false ){ 
			if ( *((m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v))) <  key[v] ){
				parent[v]  = u, key[v] = *((m_Edges.at(retornarIdEnMatriz(u))).at(retornarIdEnMatriz(v)));
			}
		  }
     }
 
    for (unsigned long i = 0; i < m_Vertices.size(); i++){
	   if( (m_Edges.at(retornarIdEnMatriz( parent[i] ))).at(retornarIdEnMatriz(i)) != NULL && parent[i] < LONG_MAX){
		   camino.push_back(parent[i]);
		   camino.push_back(i);
		   camino.push_back( *((m_Edges.at(retornarIdEnMatriz( i ))).at(retornarIdEnMatriz( parent[i] ))) );		
		   caminosPrim.push_back(camino);
		   camino.clear();
	   }
	}
	
	return caminosPrim;
}

// --------------------------------------------------------------------------
template< class _TVertex, class _TEdge >
unsigned long PUJ::Graph< _TVertex, _TEdge >::
minKey(unsigned long key[], bool mstSet[]){
   // Initialize min value
   unsigned long min = INT_MAX, min_index;
 
   for (unsigned long v = 0; v < m_Vertices.size(); v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}

#endif // __PUJ__Graph__hxx__