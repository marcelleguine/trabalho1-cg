//
//  ponto.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#import "ponto.h"

Ponto::Ponto(void) {
	x = 0.0;
	y = 0.0;
}

Ponto::Ponto(float xAux, float yAux) {
	x = xAux;
	y = yAux;
}

Ponto::~Ponto(void) {
    
}

Ponto& Ponto::operator=(const Ponto &src) {
	x = src.x;
	y = src.y;
    
	return *this;
}

void Ponto::setX(float xAux) {
	x = xAux;
}

void Ponto::setY(float yAux) {
	y = yAux;
}

float Ponto::getX() {
	return x;
}

float Ponto::getY() {
	return y;
}