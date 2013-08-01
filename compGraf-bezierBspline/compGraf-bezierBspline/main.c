//
//  main.c
//  compGraf-bezierBspline
//
//  Created by Carolina Zamith e Marcelle Guine on 31/07/13.
//  Copyright (c) 2013 Carolina Zamith e Marcelle Guine. All rights reserved.
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

int order = 3; /*grau da curva*/
int count = 0;
struct list * selected = 0;
int bezier = 0;
float * knot = 0;
struct list * l = 0;

// Chamadas da GLUT
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void display(void);
void reshape(int w, int h);

// Bezier
void computeNOrderBezierlf(int n, struct list * l, float t, float * resx, float * resy);
int coeff(int n, int k);

// B-spline
void computeNOrderBsplinelf(int d, struct list * l, float u, float * t, float * resx, float * resy);
float BsplineBasis(int j, int d, float u, float * t);
float * computeKnot(int d, int n);

// Print
struct list * listGetNearestNodegl(struct list * l, int x, int y);
void printHelpglut();


int main (int argc, const char * argv[])
{
	int gwind = 0;
    
	printf("Dicas, Utilize:\n - 3 - 9 para mudar o grau da curva.\n - 0 para trocar entre as curvas de Bezier and B-Spline.\n - C para limpar todos os pontos de controle.\n - ESC para sair do programa.\n - R para rotacionar a curva.\n - T para transladar a curva.\n - S para escalar a curva.\n - O botão esquerdo do mouse para adicionar um ponto de controle.\n - O botão direito do mouse para remover um ponto de controle.\n");
    
    knot = computeKnot(order + 1, count - 1);
    
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

// Print window
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

// GLUT : Mover pontos de controle pela tela
void motion(int x, int y)
{
    if (selected)
    {
        selected->x = (float)x;
        selected->y = (float)y;
        glutPostRedisplay();
    }
}

static void mult(float m[3][3], float m_pos[3][1], float m_resut[3][1])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 1; k++)
                m_resut[i][j] = m_resut[i][j] + (m[i][k] * m_pos[k][j]);
}

static void translate()
{
    float posX = 0;
    float posY = 0;
    printf("\n Entre com o valor para translação em x: ");
	if (!scanf("%f", &posX)) fflush(stdin);
    printf("\n Entre com o valor para translação em y: ");
	if (!scanf("%f", &posY)) fflush(stdin);
    
    float auxX, auxY;
    struct list * lResultT = 0;
    struct list * lAuxT = 0;
    
    lAuxT = l;
    selected = 0;
    count = 0;
    
    while(lAuxT)
    {
        auxX = lAuxT->x + posX;
        auxY = lAuxT->y + posY;
        lAuxT = lAuxT->next;
        
        if (lResultT)
            listAdd(lResultT, (auxX), (auxY));
        else
            lResultT = listNew((auxX), (auxY));
        
        count++;
        free(knot);
        knot = computeKnot(order + 1, count - 1);
        
        glutPostRedisplay();
    }
    
    listFree(l);
    l = 0;
    l = lResultT;
}

static void rotate()
{    
    float angle = 0;
    printf("\n Entre com o angulo de rotação desejado: ");
	if (!scanf("%f", &angle)) fflush(stdin);
    
    float auxX, auxY;
    struct list * lResult = 0;
    struct list * lAux = 0;
    float m_resut[3][1] = {0,0,0};
    
    lAux = l;
    selected = 0;
    count = 0;
    
    float m_rotate[3][3] = { { cos(angle), -sin(angle), 0},
                             { sin(angle), cos(angle) , 0},
                             {     0     ,     0      , 1} };
    
    while(lAux)
    {
        auxX = lAux->x;
        auxY = lAux->y;
        lAux = lAux->next;
        
        float m_pos[3][1] = {{ auxX },
            { auxY },
            {  1   }};
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++)
                    m_resut[i][j] = m_resut[i][j] + (m_rotate[i][k] * m_pos[k][0]);
        
        if (lResult)
            listAdd(lResult, (m_resut[0][0]), (m_resut[1][0]));
        else
            lResult = listNew((m_resut[0][0]), (m_resut[1][0]));
        
        count++;
        free(knot);
        knot = computeKnot(order + 1, count - 1);
        
        glutPostRedisplay();
    }
    
    listFree(l);
    l = 0;
    l = lResult;
}

static void scale()
{
    float scaleX = 1;
    float scaleY = 1;
    printf("\n Entre com o valor para escala em x: ");
	if (!scanf("%f", &scaleX)) fflush(stdin);
    printf("\n Entre com o valor para escala em y: ");
	if (!scanf("%f", &scaleY)) fflush(stdin);
    
    float auxX, auxY;
    struct list * lResult = 0;
    struct list * lAux = 0;
    float m_resut[3][1] = {0,0,0};
    
    lAux = l;
    selected = 0;
    count = 0;
    
    float m_scale[3][3] = { { scaleX,  0,    0},
                          {   0,   scaleY,   0},
                          {   0,     0,      1}};
    
    while(lAux)
    {
        auxX = lAux->x;
        auxY = lAux->y;
        lAux = lAux->next;
        
        float m_pos[3][1] = {{ auxX },
            { auxY },
            {  1   }};
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++)
                    m_resut[i][j] = m_resut[i][j] + (m_scale[i][k] * m_pos[k][0]);
        
        if (lResult)
            listAdd(lResult, (m_resut[0][0]), (m_resut[1][0]));
        else
            lResult = listNew((m_resut[0][0]), (m_resut[1][0]));
        
        count++;
        free(knot);
        knot = computeKnot(order + 1, count - 1);
        
        glutPostRedisplay();
    }
    
    listFree(l);
    l = 0;
    l = lResult;
}

void mouse(int button, int state, int x, int y)
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
            knot = computeKnot(order + 1, count - 1);
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
            knot = computeKnot(order + 1, count - 1);
        }
        
        glutPostRedisplay();
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
        rotate();
	}
    
    else if (key == 't' || key == 'T')
	{
        translate();
	}
    
    else if (key == 's' || key == 'S')
	{
        scale();
	}
	
    else if ((int)key == 27)
	{
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}
    
	glutPostRedisplay();

	return;
}

void display()
{
	struct list * tmp = l;
	float x, y;
	float t;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha linhas de controle
    glColor3ub(119, 136, 153);
	glBegin(GL_LINE_STRIP);
        tmp = l;
        while (tmp)
        {
            glVertex2f(tmp->x, tmp->y);
            tmp = tmp->next;
        }
    glEnd();
    
    // Desenha pontos de controle
    glColor3ub(255, 105, 180);
    glBegin(GL_POINTS);
        tmp = l;
        while (tmp)
        {
            glVertex2f(tmp->x, tmp->y);
            tmp = tmp->next;
        }
    glEnd();
    
    // Desenha curva
    glColor3ub(106, 90, 205);
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

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, w, h, 0, -1.0, 1.0 );
    glMatrixMode(GL_MODELVIEW);
}

// Calcula o ponto do enésimo grau da curva de Bezier no intervalo t
// Retorna o ponto através das variáveis resx e resy
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

// Calcula recursivamente os coeficientes binomiais para a curva de Bezier
int coeff(int n, int k)
{
    if (n == 0 && k > 0)
        return 0;
    if (k == 0)
        return 1;
    return coeff(n-1, k-1) + coeff(n-1, k);
}

// Calcula: m = d + n + 1
float * computeKnot(int d, int n)
{
	int j = 0;
    int m = (d + n + 1);
	float * t = malloc(sizeof(float) * m);
    
    for (j = 0; j < m; j++)
		t[j] = (float)j;
    
	return t;
}

// Calcula o ponto do enésimo grau da curva de B-spline no intervalo u
// Retorna o ponto através das variáveis resx e resy
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

// Calcula recursivamente a função de base B-spline no intervalo u
// Manipula a divisão por zero
float BsplineBasis(int j, int d, float u, float * t)
{
	if (d == 1)
		if (t[j] <= u && u < t[j+1]) return 1.0f; else return 0.0f;
        else
            return ((t[j+d-1] == t[j]) ? 0.0f : (u-t[j]) / (t[j+d-1]-t[j]) * BsplineBasis(j, d-1, u, t)) + ((t[j+d] == t[j+1]) ? 0.0f : (t[j+d]-u)/(t[j+d]-t[j+1]) * BsplineBasis(j+1, d-1, u, t));
}
