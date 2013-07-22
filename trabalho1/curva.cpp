//
//  curva.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#import "curva.h"

Curva::Curva(void) {
	grauCurva = -1;
}

Curva& Curva::operator=(const Curva &src) {
	pontosDeControle.clear();
	pontosDeControle = src.pontosDeControle;
	grauCurva = src.grauCurva;
    
	return *this;
}

Curva::~Curva(void) {
    
}

void Curva::desenharCurva(GLfloat r, GLfloat g, GLfloat b) {
    
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	for (size_t j = 0; j < pontosDeControle.size() - 1; j++) {
		glVertex2f(pontosDaCurva[j].getX(), pontosDaCurva[j].getY());
		glVertex2f(pontosDaCurva[j+1].getX(), pontosDaCurva[j+1].getY());
	}
	glEnd();
}


void Curva::refresh() {
    
}

bool Curva::possuiTodosOsPontosDeControle() {
	return pontosDeControle.size() == grauCurva;
}

int Curva::getTipoCurva() {
	return -1;
}



void Curva::adicionarPontoDeControle(Ponto ponto) {
	pontosDeControle.push_back(ponto);
}

void Curva::adicioarPontoDeControle(float x, float y) {
	pontosDeControle.push_back(Ponto(x, y));
}

void Curva::adicionarPontoDaCurva(Ponto ponto) {
	pontosDaCurva.push_back(ponto);
}

void Curva::adicionarPontoDaCurva(float x, float y) {
	pontosDaCurva.push_back(Ponto(x, y));
}


void Curva::setGrauDaCurva(int grauCurvaAux) {
	grauCurva = grauCurvaAux;
}

int Curva::getGrauDaCurva() {
	return grauCurva;
}

vector<Ponto> Curva::getPontosDeControle() {
	return pontosDeControle;
}

vector<Ponto> Curva::getPontosDaCurva() {
	return pontosDaCurva;
}