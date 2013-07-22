//
//  bezier.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#import "bezier.h"

Bezier::Bezier(void) {
	Curva::Curva();
}

Bezier::~Bezier(void) {
    
}

void Bezier::refresh() {
	pontosDaCurva.clear();
}

bool Bezier::possuiTodosOsPontosDeControle() {
	return pontosDeControle.size() == (grauCurva + 1);
}

int Bezier::getTipoCurva() {
	return 2;
}