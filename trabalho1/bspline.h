//
//  bspline.h
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include "curva.h"

class BSpline : public Curva{
public:
	BSpline(void);
	~BSpline(void);
    
	virtual void refresh();
	virtual bool possuiTodosOsPontosDeControle();
	virtual int getTipoCurva();
    
protected:
    
private:

};