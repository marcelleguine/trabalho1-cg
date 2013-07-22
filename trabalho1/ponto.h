//
//  ponto.h
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

class Ponto{

public:
    Ponto(void);
	Ponto(float, float);
	~Ponto(void);
    
	Ponto& operator=(const Ponto&);
    
	void setX(float);
	void setY(float);
    
	float getX();
	float getY();
    
protected:
    
private:
    float x;
	float y;

};