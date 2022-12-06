#include<bits/stdc++.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
using namespace std;

#define CIRCLE_RADIUS  0.15f
#define PI 3.14159265358979323846

//  global variable
int width = 600;
int height = 650;
int eggs_caught=0,missed_eggs=0,level_count=1,points=0;
int egg_xc,egg_yc;
// for coordinates of egg
int basket_x,basket_y;
int speed_1=1,speed_2=1.5,speed_3=2,speed_4=2.5;
bool start = false;

// function declartion
void init();
void basket_set(int,int);
void myReshape(int,int);
void keys(unsigned char,int,int);
void quit();
void menu(int);

void init(){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,(GLdouble)width,0,(GLdouble)height);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

// display helper function...

void ground(int i , int j){
    glBegin(GL_QUADS);
    glColor3f(0,1.0,0);

    glVertex2f(i+0.0,j-500);
    glVertex2f(0.0,0.0);
    glVertex2f(i+600.0,0.0);
    glVertex2f(i+600.0,j-500);
    glEnd();

}

void backk(int i ,int j){
    glBegin(GL_QUADS);
    glColor3f(0,0.5,1);

    glVertex2f(i+0.0,j+0.0);
    glVertex2f(i+0.0,150.0);
    glVertex2f(i+600.0,150.0);
    glVertex2f(i+600.0,j+0.0);
    glEnd();
    glFlush();

}

// drawing duck...
void duck(int i , int j){
    int h;
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);

    // duck body
    glVertex2f(45+i,45+j);
    glVertex2f(70+i,20+j);
    glVertex2f(95+i,20+j);
    glVertex2f(120+i,45+j);
    glVertex2f(95+i,70+j);
    glVertex2f(70+i,70+j);
    glVertex2f(95+i,95+j);
    glVertex2f(82.5+i,107.5+j);
    glVertex2f(32.5+i,57.5+j);
    glEnd();
    glFlush();

    // line in duck body
    for(h = 0 ; h < 13 ; h+=4){
        glBegin(GL_LINES);
        glColor3f(0.7,0.4,0);
        glVertex2f(57.5+h+i,52.5+h+j);
        glVertex2f(100+h+i,30+h+j);
        glEnd();
        glFlush();
    }

    // duck lip
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(82.5+i,107.5+j);
    glVertex2f(65+i,107.5+j);
    glVertex2f(50+i,95+j);
    glVertex2f(70+i,95+j);
    glEnd();
    glFlush();

    // duck eye
    glColor3f(0.0,0.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(76+i,101+j);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(72.5+i,107.5+j);
    glVertex2f(67.5+i,112.5+j);
    glVertex2f(72.5+i,110+j);
    glVertex2f(77.5+i,112.5+j);
    glEnd();
    glFlush();

}

void sun(){
    float theta;

    GLfloat angle;

    glLineWidth(1.5);
    glColor3f(1,0.2,0);
    glBegin(GL_POLYGON);

    for(int i = 0 ; i < 360 ; i++){
        theta = i*PI*i/180;
        glVertex2f(500+80*cos(theta)/2, 600+80*sin(theta)/2);
    }

    glEnd();
    glFlush();

}

void cloud1(){
     float theta;

    GLfloat angle;
    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
    theta  = i*PI*i/180;
    glVertex2f(100+50*cos(theta)/2, 590+50*sin(theta)/2);
    }

    glEnd();
    //GLfloat angle;
    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
    theta  = i*PI*i/180;
    glVertex2f(130+50*cos(theta)/2, 580+50*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
    theta  = i*PI*i/180;
    glVertex2f(140+50*cos(theta)/2, 600+50*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
    theta  = i*PI*i/180;
    glVertex2f(170+50*cos(theta)/2, 590+50*sin(theta)/2);
    }

    glEnd();
    glFlush();
}

void cloud2(){
    
}

void line(int i , int j){
    glBegin(GL_QUADS);
    glColor3f(1.0,.5,0.5);
    glVertex2f(0.0+i,10.0+j);
    glVertex2f(0.0+i,15.0+j);
    glVertex2f(600.0+i,15.0+j);
    glVertex2f(600.0+i,10.0+j);
    glEnd();
    glFlush();
}

void egg(){
    float x,y,z;
    int t;
    glColor3f(1.0,10,1.0);
    glBegin(GL_POLYGON);
    for(t=0;t<=360;t+=1){
        x = egg_xc+8*(cos(t));
        y = egg_yc+16*(sin(t));
        glVertex2f(x,y);
    }
    glEnd();
}

void egg_start(){
    egg_yc = 375;

    switch (rand()%9){
        case 0:egg_xc=115; break;
        case 1:egg_xc=255; break;
        case 2:egg_xc=390; break;
        case 5:egg_xc=115; break;
        case 3:egg_xc=255; break;
        case 4:egg_xc=390; break;
        case 7:egg_xc=115; break;
        case 6:egg_xc=255; break;
        case 8:egg_xc=390; break;
    }
}

void basket(int i,int j){
    j=10;
    if(i>=width-60){
        i = width-60;
    }
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i,30.0+j);
    glVertex2f(10.0+i,10.0+j);
    glVertex2f(50.0+i,10.0+j);
    glVertex2f(60.0+i,30.0+j);
    glEnd();
}

void score(){
    if(egg_yc <= 50 && (egg_xc >= basket_x && egg_xc <= basket_x+60)){
        eggs_caught++;

        // cout << "eggs caught " << eggs_caught << endl;
        egg_yc = -10;
    }
}

void start_screen(int i , int j){
    int k;
    char cat[4]="EGG";
    char orr[9]="Catching";
    char hatch[5]="Game";
    char start[20]="Press S for start";

    glColor3f(0,1,0);
    glRasterPos2i(150,320);
    for(k=0;k<4;k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,cat[k]);
    }

    glColor3f(1,1,1);
    glRasterPos2i(200,320);
    for(k=0;k<9;k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,orr[k]);
    }
    
    glColor3f(1,0,0);
    glRasterPos2i(300,320);
    for(k=0;k<5;k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,hatch[k]);
    }
    
    glColor3f(1,1,0);
    glRasterPos2i(210,200);

    for(k=0;k<20;k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,start[k]);
    }
    
    glColor3f(1,.5,.5);
}


void showLevel(){

    int i;
    char level1[12]="LEVEL 1";
    char level2[12]="LEVEL 2";
    char level3[12]="LEVEL 3";
    char level4[12]="LEVEL 4";

    if(level_count==1){
        glColor3f(1,1,1);
        glRasterPos2i(500,400);
        for(i=0;i<12;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level1[i]);
    }else if(level_count == 2){
        glColor3f(1,0,0);
        glRasterPos2i(500,400);
        for(i=0;i<12;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level2[i]);
    }else if(level_count == 3){
        glColor3f(0,1,1);
        glRasterPos2i(500,400);
        for(i=0;i<12;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level3[i]);
    }else if(level_count == 4){
        glColor3f(1,0,1);
        glRasterPos2i(500,400);
        for(i=0;i<12;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level4[i]);
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    ground(0,650);
    backk(0,650);

    duck(40,375);
    duck(180,375);
    duck(320,375);

    sun();
    cloud1();
    line(0,375);

    int i;
    char allName[30]="Nishan Firoz Saifuz Uday";

    if(start){

        glColor3f(0,0,1);
        glRasterPos2i(10,10);
        for(i=0;i<30;i++){
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13,allName[i]);
        }

        showLevel();

        // showing the score level...
        char str[15]="score is: ";
        glColor3f(0,1,1);
        glRasterPos2i(500,300);
        for(int i=0;i<15;i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
        }

        ostringstream ss;
        ss << eggs_caught;

        string scoreStr = ss.str();

        glColor3f(0,1,1);
        glRasterPos2i(580,300);
        for(int i=0;i<scoreStr.length();i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,scoreStr[i]);
        }

        if(egg_yc<=10){
            egg_start();
        }

        egg();
        basket(basket_x,basket_y);

        // here define set the level based on eggs catching

        if(eggs_caught >= 3){
            egg_yc -= speed_2;
            level_count = 2;
        }
        if(eggs_caught >= 6){
            egg_yc -= speed_3;
            level_count = 3;
        }
        if(eggs_caught >= 9){
            egg_yc -= speed_3;
            level_count = 4;
        }
        else{
            egg_yc -= speed_1;
        }


        score();

    }else{
        start_screen(40,300);
    }


    glFlush();
    glutSwapBuffers();
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(width,height);
    glutCreateWindow("EGG CATCHING GAME");
    init();
    glutInitWindowPosition(100,100);
    glutCreateMenu(menu);
    glutAddMenuEntry("Start game",1);
    glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutPassiveMotionFunc(basket_set);
    glutIdleFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();
}

void menu(int id){
    switch(id){
        case 1:
            start = true;
            break;
        case 2:
            quit();
            break;
        default: 
            exit(0);
    }
    glutPostRedisplay();
}

void basket_set(int a , int b){
    // cout << "basket " << a << " " << b << endl;
    basket_x = a;
    basket_y = b;
    glutPostRedisplay();
}

void myReshape(int w , int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
    width=w;
    height=h;
}


void keys(unsigned char key , int x , int y){
    if(key == 's' || key == 'S'){
        start = true;
    }else if(key == 'q' || key == 'Q'){
        printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
        quit();
    }
}

void quit(){
    exit(0);
}