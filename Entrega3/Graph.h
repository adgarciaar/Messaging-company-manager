#ifndef __PUJ__Graph__h__
#define __PUJ__Graph__h__

#include <map>
#include <vector>

namespace PUJ
{
  template< class _TVertex, class _TEdge >
  class Graph
  {
  public:
    typedef std::vector< _TVertex > TVertices;
    typedef std::map< unsigned long, _TEdge* > TRow; 
    typedef std::map< unsigned long, TRow >  TMatrix; 
	
	typedef std::vector< bool > TMarks;

  public:
    Graph( );
    virtual ~Graph( );

    long AddVertex( const _TVertex& v );
    void AddEdge( unsigned long a, unsigned long b, _TEdge cost );
	long GetNumberOfVertices( );
	_TVertex GetVertex( unsigned long i );
	void DeleteVertex( const _TVertex& v );
	void DeleteEdge( unsigned long a, unsigned long b);
	bool HasArc( unsigned long i, unsigned long j );
    void Draw( const std::string& filename );	
	
	_TEdge* GetCost( unsigned long i, unsigned long j );
	
	void PrintPlaneGraph();
	void PrintPreorderGraph( unsigned long i ); //Depth-first search (DFS)
	void PrintLevelsGraph( unsigned long i ); //Breadth-first search (BFS)
	
	std::vector< std::vector< unsigned long > > Dijkstra( unsigned long start, unsigned long end );
	
	unsigned long minDistance(unsigned long dist[], bool sptSet[]);
	void savePath(unsigned long parent[], unsigned long j, std::vector< unsigned long >& camino);
	void saveSolution(unsigned long dist[], unsigned long parent[], std::vector< std::vector< unsigned long > >& caminosDijkstra, 
		unsigned long start, unsigned long end);
	
    std::vector< std::vector< unsigned long > > Prim( unsigned long start );
	
	unsigned long minKey(unsigned long key[], bool mstSet[]);
	
  protected:
	void PrintPreorderGraph_Dummy( unsigned long i, TMarks& m );
																 
  public:
	unsigned long retornarIdEnMatriz (unsigned long pVector); //retorna el identificador de un vértice en la posición i del vector de vértices
	unsigned long retornarPosicionEnVertices( unsigned long i ); //retorna la posición del vértice correspondiente a i 
															     //en el vector de vértices para marcar su posición en recorridos
																 
  protected:
    TVertices m_Vertices;
    TMatrix   m_Edges;
  };
}

#include "Graph.hxx"

#endif // __PUJ__Graph__h__