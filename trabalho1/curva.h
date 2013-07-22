//
//  curva.h
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include <GLUT/GLUT.h>

#include <vector>

#import "ponto.h"

using namespace std;


class Curva{
    
public:
	
    Curva(void);
	~Curva(void);

    Curva& operator=(const Curva&);
    
	virtual void refresh();
	virtual bool possuiTodosOsPontosDeControle();
	virtual int getTipoCurva();
    
	void desenharCurva(GLfloat, GLfloat, GLfloat);
	void adicionarPontoDeControle(Ponto);
    void adicioarPontoDeControle(float, float);
    void adicionarPontoDaCurva(Ponto);
    void adicionarPontoDaCurva(float, float);
    void setGrauDaCurva(int);
    int getGrauDaCurva();
    vector<Ponto> getPontosDeControle();
    vector<Ponto> getPontosDaCurva();
    
    
protected:
	vector<Ponto> pontosDeControle;
	vector<Ponto> pontosDaCurva;
	int grauCurva;
    
private:
    
};