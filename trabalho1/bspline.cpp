//
//  bspline.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 22/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#import "bspline.h"

BSpline::BSpline(void) {
	Curva::Curva();
}

BSpline::~BSpline(void) {
    
}

void BSpline::refresh() {
	pontosDaCurva.clear();
}

bool BSpline::possuiTodosOsPontosDeControle() {
	return pontosDeControle.size() == (grauCurva + 1);
}

int BSpline::getTipoCurva() {
	return 1;
}