//
//  main.h
//  trabalho1
//
//  Created by Marcelle Guine on 20/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include <OpenGL/OpenGL.h>

#include <cstdlib>
#include <string>
#include <vector>

//#include "bspline.h"
#include "bezier.h"

using namespace std;

enum ESTADO {
    CURVA_SELECIONADA,
    DESENHANDO_CURVA,
    TRANSLADANDO_CURVA,
    ROTACIONANDO_CURVA,
    ESCALANDO_CURVA
};


/*Variáveis*/
static int window;

static int menu_id;
static int arquivoSubmenu_id;
static int curvaSubmenu_id;
static int tipoCurvaSubmenu_id;
static int grauCurvaSubmenu_id;

static int tipoCurva = 1; /*B-Spline*/
static int grauCurva = 3; /*Grau 3*/
static int indexCurvaAtual;

ESTADO estadoAtual;
Curva *curvaAtual;
vector<Curva*> curvas;


/*Funções*/
void menu(int);
void criarMenu();

void init();
void idle();
void mouse();
void display(void);
