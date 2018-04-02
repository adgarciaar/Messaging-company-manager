#ifndef REGION_REPARTO_H
#define REGION_REPARTO_H 

#include <string>
#include "lugar_reparto.h"

class RegionReparto : public LugarReparto{
		
	public:
	
		//constructor
		RegionReparto(std::string codigo, std::string nombre);
		//destructor
		~RegionReparto();
	
};

#include "region_reparto.hxx"

#endif