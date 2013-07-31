//
//  main.c
//  compGraf-bezierBspline
//
//  Created by Marcelle Guine on 31/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include "List.h"

typedef enum{
    DESENHANDO,
    TRANSLADANDO,
    ROTACIONANDO,
    ESCALANDO
} estadoPrograma;

estadoPrograma estado = DESENHANDO;

int order = 3;
int count = 0;
struct list * selected = 0;
int bezier = 0;
float * knot = 0;
struct list * l = 0;

// GLUT callbacks.
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void display(void);
void reshape(int w, int h);

// Bezier computation.
void computeNOrderBezierlf(int n, struct list * l, float t, float * resx, float * resy);
int coeff(int n, int k);

// B-spline computation.
void computeNOrderBsplinelf(int d, struct list * l, float u, float * t, float * resx, float * resy);
float BsplineBasis(int j, int d, float u, float * t);
float * computeUniformKnot(int d, int n);

// Helper functions.
struct list * listGetNearestNodegl(struct list * l, int x, int y);
void printHelpglut();


// Main asks for initial input from the user and instructs the user how to interact at run-time.
int main (int argc, const char * argv[])
{
	int gwind = 0;
    
	printf("Dicas, Utilize:\n - 3 - 9 para mudar o grau da curva.\n - 0 para trocar entre as curvas de Bezier and B-Spline.\n - C para limpar todos os pontos de controle.\n - ESC para sair do programa.\n - R para rotacionar a curva.\n - T para transladar a curva.\n - S para escalar a curva.\n - o botão esquerdo do mouse para adicionar um ponto de controle.\n - o botão direito do mouse para remover um ponto de controle.\n");
    
    knot = computeUniformKnot(order + 1, count - 1);
    
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    gwind = glutCreateWindow("Trabalho de Computação Gráfica - Construção de Curvas");
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(8.0f);
	glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}

// Returns the first node in a list that is within range of GL_POINT_SIZE.
struct list * listGetNearestNodegl(struct list * l, int x, int y)
{
    float pointSize;
    
    glGetFloatv(GL_POINT_SIZE, &pointSize);
    pointSize /= 2.0f;
    
    while (l)
    {
        if (l->x - pointSize <= x && l->x + pointSize >= x && l->y - pointSize <= y && l->y + pointSize >= y)
            return l;
        l = l->next;
    }
    
    return 0;
}

// Prints help on screen.
void printHelpglut()
{
    char s[100];
    char * st = 0;
    
    glColor3ub(0, 0, 0);
    glRasterPos2i(2, 12);
    sprintf(s, "%s curva de grau %i, com %i pontos de controle.", bezier ? "Bezier Uniforme" : "B-spline Uniforme", order, count);
    st = s;
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 36);
    st = "[3..9] - grau";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 48);
    st = "[0] - bezier/b-spline";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 72);
    st = "[C] - limpar";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 84);
    st = "[R] - rotacionar";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 96);
    st = "[T] - transladar";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 108);
    st = "[S] - escalar";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 130);
    st = "BEsq - adicionar, mover";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 142);
    st = "BDir - remover";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
    
    glRasterPos2i(2, 164);
    st = "[ESC] - sair";
    while (*st)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *st);
        st++;
    }
}

// GLUT callback for mouse dragging.
void motion(int x, int y)
{
    if (selected)
    {
        selected->x = (float)x;
        selected->y = (float)y;
        glutPostRedisplay();
    }
}

static void rotacionar(tempontosdecontrole){
    //    if(tempontosdecontrole.x!=0){
    //        for (int i=0; tempontosdecontrole.size; i++) {
    //
    //        }
    //    }
    
    estado = DESENHANDO;
}

static void transladar(int x, int y){
    
    //    float topX = -10, topY = -10;
    //
    //    int num_pontos = sizeof(pontosDeControle)/sizeof(pontosDeControle[0]);
    //
    //    for (int i = 0; i < num_pontos; i++) {
    //        if (pontosDeControle[i][0] && pontosDeControle[i][0] > topX) topX = pontosDeControle[i][0];
    //        if (pontosDeControle[i][1] && pontosDeControle[i][1] > topY) topY = pontosDeControle[i][1];
    //    }
    //
    //    float wx, wy;
    //    mouse_to_coordenada(x, y, &wx, &wy);
    //
    //    float translationXOffset = wx - topX;
    //    float translationYOffset = wy - topY;
    //
    //    for (int i = 0; i < num_pontos; i++) {
    //        if (pontosDeControle[i][0]) pontosDeControle[i][0] += translationXOffset;
    //        if (pontosDeControle[i][1]) pontosDeControle[i][1] += translationYOffset;
    //    }
    //
    //    display();
    //    desenharCurva();
    
    estado = DESENHANDO;
}

static void escalar(){
    estado = DESENHANDO;
}

// GLUT callback for mouse activity.
void mouse(int button, int state, int x, int y)
{
    /*Desenha na tela*/
    if (estado == DESENHANDO)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (!(selected = listGetNearestNodegl(l, x, y)))
            {
                if (l)
                    listAdd(l, (float)x, (float)y);
                else
                    l = listNew((float)x, (float)y);
            
                count++;
                free(knot);
                knot = computeUniformKnot(order + 1, count - 1);
            }
        
            glutPostRedisplay();
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            if ((selected = listGetNearestNodegl(l, x, y)))
            {
                if (l == selected)
                    l = listRemove(selected);
                else
                    listRemoveAt(selected, 0);
                
                selected = 0;
                count --;
                free(knot);
                knot = computeUniformKnot(order + 1, count - 1);
            }
        
            glutPostRedisplay();
        }
    }
    
    /*Aplica transformações*/
    else{
        if (estado == TRANSLADANDO)
            transladar(x, y);
        else if (estado == ROTACIONANDO)
            rotacionar(1);
        else if (estado == ESCALANDO)
            escalar();
    }
}

void keyboard(unsigned char key, int x, int y)
{
	if (key >= '3' && key <= '9')
        order = (int)key - 48;
    else if (key == '0')
        bezier = !bezier;
	else if (key == 'c' || key == 'C')
	{
		selected = 0;
		listFree(l);
		l = 0;
        count = 0;
	}
    else if (key == 'r' || key == 'R')
	{
        estado = ROTACIONANDO;
	}
    else if (key == 't' || key == 'T')
	{
        estado = TRANSLADANDO;
	}
    else if (key == 's' || key == 'S')
	{
        estado = ESCALANDO;
	}
	else if ((int)key == 27)
	{
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}
    
    if (!bezier)
    {
        free(knot);
        knot = computeUniformKnot(order + 1, count - 1);
    }
	glutPostRedisplay();
	return;
}

// GLUT callback for rendering.
// Draws all the control points in l, their connecting lines and the curve as specified by the user.
// Ends by printing a description of the current curve to the screen.
void display()
{
	struct list * tmp = l;
	float x, y;
	float t;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(127, 127, 127);
	glBegin(GL_LINE_STRIP);
    
	tmp = l;
	while (tmp)
    {
        glVertex2f(tmp->x, tmp->y);
        tmp = tmp->next;
    }
    
	glEnd();
    
    glColor3ub(255, 0, 0);
    
    glBegin(GL_POINTS);
	tmp = l;
    while (tmp)
    {
        glVertex2f(tmp->x, tmp->y);
        tmp = tmp->next;
    }
    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
	tmp = l;
    if (bezier)
    {
        while (tmp && listCount(tmp) > order)
        {
            for (t = 0.0f; t <= 1.0f; t+=0.01f)
            {
                computeNOrderBezierlf(order, tmp, t, &x, &y);
                glVertex2f(x, y);
            }
            tmp = listGet(tmp, order);
        }
    }
    else
    {
        for (t = knot[order]; t <= knot[count]; t+=0.01f)
        {
            computeNOrderBsplinelf(order + 1, l, t, knot, &x, &y);
            glVertex2f(x, y);
        }
    }
    glEnd();
    
    printHelpglut();
    
    glutSwapBuffers();
}

// GLUT callback for window resizing.
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, w, h, 0, -1.0, 1.0 );
    glMatrixMode(GL_MODELVIEW);
}

// Computes a point on a N-th degree bezier curve at interval t.
// Returns the point through resx and resy.
void computeNOrderBezierlf(int n, struct list * l, float t, float * resx, float * resy)
{
    float omt = 1.0f - t;
	int i = 0;
	float c;
    *resx = 0.0f;
    *resy = 0.0f;
    while (l && i <= n)
    {
        c = (float)coeff(n, i);
        *resx += c * powf(omt, n - i) * powf(t, i) * l->x;
        *resy += c * powf(omt, n - i) * powf(t, i) * l->y;
        l = l->next;
        i++;
    }
}

// Recursively computes the binomial coefficients for Bezier curves.
int coeff(int n, int k)
{
    if (n == 0 && k > 0)
        return 0;
    if (k == 0)
        return 1;
    return coeff(n-1, k-1) + coeff(n-1, k);
    
}

// Computes all (m = d + n + 1) uniform knot vectors.
float * computeUniformKnot(int d, int n)
{
	int j = 0;
    int m = (d + n + 1);
	float * t = malloc(sizeof(float) * m);
    
    for (j = 0; j < m; j++)
		t[j] = (float)j;
    
	return t;
}

// Computes a point on a N-th degree (d - 1) B-spline curve at interval u.
// Returns the point through resx and resy.
void computeNOrderBsplinelf(int d, struct list * l, float u, float * t, float * resx, float * resy)
{
	int j = 0;
	
	*resx = 0.0f;
	*resy = 0.0f;
    
    j = 0;
    while (l)
    {
        *resx += l->x * BsplineBasis(j, d, u, t);
        *resy += l->y * BsplineBasis(j, d, u, t);
        l = l->next;
        j++;
    }
}

// Recursively computes the B-spline basis function at interval u.
// Handles division by zero as zero and stops recursing in a branch when multiplication by zero would occur.
float BsplineBasis(int j, int d, float u, float * t)
{
	if (d == 1)
		if (t[j] <= u && u < t[j+1]) return 1.0f; else return 0.0f;
        else
            return ((t[j+d-1] == t[j]) ? 0.0f : (u-t[j]) / (t[j+d-1]-t[j]) * BsplineBasis(j, d-1, u, t)) + ((t[j+d] == t[j+1]) ? 0.0f : (t[j+d]-u)/(t[j+d]-t[j+1]) * BsplineBasis(j+1, d-1, u, t));
}
