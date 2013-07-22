//
//  main.cpp
//  trabalho1
//
//  Created by Marcelle Guine on 20/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//


#include "main.h"


void menu(int num){
    
    switch(num) {
        
        /*Sair*/
		case 0:
            glutDestroyWindow(window);
			exit(EXIT_SUCCESS);
			break;
        
        /*Escolher tipo: 1- B-Spline / 2- Bézier*/
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
            if (tipoCurva == 1)
                curvaAtual = new BSpline();
            else
                curvaAtual = new BezierCurve();
            
            curvaAtual -> setGrauCurva(grauCurva);
            estadoAtual = DESENHANDO_CURVA;
            
            break;
            
        /*Excluir curva*/
		case 12:
            break;
        
        /*Transladar curva*/
		case 13:
            if (estadoAtual == CURVA_SELECIONADA) {
				estadoAtual = TRANSLADANDO_CURVA;
			}
            break;
        
        /*Rotacioar curva*/
		case 14:
            if (estadoAtual == CURVA_SELECIONADA) {
				estadoAtual = ROTACIONANDO_CURVA;
			}
            break;
            
        /*Escalar curva*/
        case 15:
            if (estadoAtual == CURVA_SELECIONADA) {
				estadoAtual = ESCALANDO_CURVA;
			}
            break;
        
        /*Abrir arquivo*/
		case 16:
            break;
            
        /*Salvar arquivo*/
		case 17:{
            break;
        }
	}
    
	glutPostRedisplay();
}


void criarMenu(void){
    
    arquivoSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Abrir", 16);
    glutAddMenuEntry("Salvar", 17);
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
    glutAddMenuEntry("Escalar", 15);
    glutAddSubMenu("Escolher tipo", tipoCurvaSubmenu_id);
    glutAddSubMenu("Alterar grau", grauCurvaSubmenu_id);
    
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Arquivo", arquivoSubmenu_id);
    glutAddSubMenu("Curva", curvaSubmenu_id);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display(void){
        
}


void mouse(int botao, int estado, int x, int y) {
    
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

    criarMenu();
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
	glutIdleFunc(idle);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}