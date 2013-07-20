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

static int window;

static int valueMenu = 0;
static int menu_id;
static int arquivoSubmenu_id;
static int curvaSubmenu_id;
static int tipoCurvaSubmenu_id;
static int grauCurvaSubmenu_id;

static int tipoCurva = 1;
static int grauCurva = 3;


void menu(int num){
    if(num == 0){
        glutDestroyWindow(window);
        exit(0);
    }else{
        valueMenu = num;
    }
    glutPostRedisplay();
}

void createMenu(void){
    
    arquivoSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Abrir", 1);
    glutAddMenuEntry("Salvar", 2);
    glutAddMenuEntry("Sair do programa", 0);
    
    tipoCurvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("B-spline ", 5);
    glutAddMenuEntry("Bezier", 6);
    
    grauCurvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("3", 7);
    glutAddMenuEntry("4", 8);
    glutAddMenuEntry("5", 9);
    glutAddMenuEntry("6", 10);
    glutAddMenuEntry("7", 11);
    glutAddMenuEntry("8", 12);
    glutAddMenuEntry("9", 13);
    glutAddMenuEntry("10", 14);
    
    curvaSubmenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Criar", 3);
    glutAddMenuEntry("Exlcuir", 4);
    glutAddSubMenu("Escolher tipo", tipoCurvaSubmenu_id);
    glutAddSubMenu("Alterar grau", grauCurvaSubmenu_id);
    
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Arquivo", arquivoSubmenu_id);
    glutAddSubMenu("Curva", curvaSubmenu_id);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT);

    /*Abrir*/
    if(valueMenu == 1){

    }
    
    /*Salvar*/
    else if(valueMenu == 2){
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        glutWireSphere(0.5, 50, 50);
        glPopMatrix();
    }
    
    /*Criar curva*/
    else if(valueMenu == 3){
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        glRotated(65, -1.0, 0.0, 0.0);
        glutWireCone(0.5, 1.0, 50, 50);
        glPopMatrix();
    }
    
    /*Excluir curva*/
    else if(valueMenu == 4){
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        glutWireTorus(0.3,0.6,100,100);
        glPopMatrix();
    }
    
    /*Escolher tipo: B-Spline*/
    else if(valueMenu == 5){
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
        
        tipoCurva = 1;
    }
    
    /*Escolher tipo: Bezier*/
    else if(valueMenu == 6){
        tipoCurva = 2;
    }
    
    /*Alterar grau da curva: 
     valor: 3*/
    else if(valueMenu == 7){
        grauCurva = 3;
    }
    /*valor: 4*/
    else if(valueMenu == 8){
        grauCurva = 4;
    }
    /*valor: 5*/
    else if(valueMenu == 9){
        grauCurva = 5;
    }
    /*valor: 6*/
    else if(valueMenu == 10){
        grauCurva = 6;
    }
    /*valor: 7*/
    else if(valueMenu == 11){
        grauCurva = 7;
    }
    /*valor: 8*/
    else if(valueMenu == 12){
        grauCurva = 8;
    }
    /*valor: 9*/
    else if(valueMenu == 13){
        grauCurva = 9;
    }
    /*valor: 10*/
    else if(valueMenu == 14){
        grauCurva = 10;
    }   
    
    glFlush();
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(250, 200);
    window = glutCreateWindow("Computação Gráfica - Construção de Curvas");
    
    createMenu();
    
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}