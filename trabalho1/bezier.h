//
//  bezier.h
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include "curva.h"

class Bezier : public Curva{
public:
	Bezier(void);
	~Bezier(void);
    
	virtual void refresh();
	virtual bool possuiTodosOsPontosDeControle();
	virtual int getTipoCurva();
    
protected:
    
private:
//    float factorial(int);
//	float combination(int, int);
    
};