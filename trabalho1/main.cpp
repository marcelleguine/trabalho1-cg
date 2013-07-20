//
//  main.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 20/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

static int window;

static int menu_id;
static int arquivoSubmenu_id;
static int curvaSubmenu_id;
static int tipoCurvaSubmenu_id;
static int grauCurvaSubmenu_id;

static int tipoCurva = 1;
static int grauCurva = 3;


void menu(int num){
    
    switch(num) {
        
        /*Sair*/
		case 0:
            glutDestroyWindow(window);
			exit(EXIT_SUCCESS);
			break;
        
        /*Escolher tipo: 1- B-Spline / 2- Bezier*/
		case 1:
        case 2:
            tipoCurva = num;
            break;
        
        /*Alterar grau da curva 3-10*/
		case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            grauCurva = num;
            break;
        
        /*Criar curva*/
        case 11:
            break;
            
        /*Excluir curva*/
		case 12:
            break;
        
        /*Transladar curva*/
		case 13:
            break;
        
        /*Rotacioar curva*/
		case 14:
            break;
        
        /*Abrir arquivo*/
		case 15:
            break;
            
        /*Salvar arquivo*/
		case 16:
            break;
	}
    
	glutPostRedisplay();
}


void createMenu(void){
    
    arquivoSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Abrir", 1);
    glutAddMenuEntry("Salvar", 2);
    glutAddMenuEntry("Sair do programa", 0);
    
    tipoCurvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("B-spline ", 1);
    glutAddMenuEntry("Bezier", 2);
    
    grauCurvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("3", 3);
    glutAddMenuEntry("4", 4);
    glutAddMenuEntry("5", 5);
    glutAddMenuEntry("6", 6);
    glutAddMenuEntry("7", 7);
    glutAddMenuEntry("8", 8);
    glutAddMenuEntry("9", 9);
    glutAddMenuEntry("10", 10);
    
    curvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Criar", 11);
    glutAddMenuEntry("Excluir", 12);
    glutAddMenuEntry("Transladar", 13);
    glutAddMenuEntry("Rotacionar", 14);
    glutAddSubMenu("Escolher tipo", tipoCurvaSubmenu_id);
    glutAddSubMenu("Alterar grau", grauCurvaSubmenu_id);
    
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Arquivo", arquivoSubmenu_id);
    glutAddSubMenu("Curva", curvaSubmenu_id);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT);
    
//	glColor3f(0.0, 0.0, 1.0);
    
//	glBegin(GL_POINTS);
//    
//    
//	glEnd();
    
	glutSwapBuffers();
    
}


void mouse(int button, int state, int x, int y) {
    
    glutPostRedisplay();
}


void idle() {
    
    glutSetWindow(window);
    glutPostRedisplay();
}


void init(){
    
    glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1024.0, 768.0, 0.0);
	glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
	glPointSize(5.0f);
    
}


int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(250, 200);
    
    window = glutCreateWindow("Computação Gráfica - Construção de Curvas");

    createMenu();
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
	glutIdleFunc(idle);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}