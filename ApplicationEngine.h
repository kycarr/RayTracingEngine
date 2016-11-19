// ApplicationEngine.h: interface for the ApplicationEngine class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Application.h"

class ApplicationEngine : public Application  
{
public:
	ApplicationEngine();
	virtual ~ApplicationEngine();
	
	int	Initialize();
	virtual int Render(); 
	void Clean();
};
