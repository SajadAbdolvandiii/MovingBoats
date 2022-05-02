/*********
   CTIS164 - Template Source Program
----------
STUDENT : Sajad Abdolvandi
SECTION :
HOMEWORK: 1
----------
PROBLEMS: CODE DOES NOT HAVE ANY PROBLEMS, but as i use XCODE, please remove "stdbool.h" and "GLUT/glut.h" libraries, and change the functions vsprint functinos in lines 98 and 115 to "vsprint_s" to make sure it works on visual studio. Thanks!
----------
ADDITIONAL FEATURES:
 I have designed a background, my code has pointer for mouse, it has moving clouds + OVERFLOW feature, / You can just spawn ships into the water + not in the woods + and you cant spawn at the end of the edges. + you CANT add objects lower than 290 pixels because the moving ships will overlap the "coordinate text "and i limited the area so IT IS NOT A BUG.
 you can add object while moving flawlessly!
 YOU CAN RESIZE THE CLOUDS
 YOU CAN RESET THE APP
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#define NOT_ANIMATING 0
#define ANIMATING 1
#define WINDOW_WIDTH  1150
#define WINDOW_HEIGHT 700
#define TORIGHT 0
#define TOLEFT 1

#define TIMER_PERIOD  1 // Period for the timer.
#define TIMER_ON       1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
// MY VARIABLES
int movingX,movingY;
int ObjCounter = 0;
int coords[10][2];
int moveSpeed;
int lp =0;
int ObjX[10]={0};
int ObjY[10]={0};
char Statement1[40] = "Press \"F1\" Key to START the animation!";
char Statement2[40] = "Press \"F1\" Key to STOP the animation!";
int ResizeAmount = 0;
int direction = TORIGHT;
int state = NOT_ANIMATING;
int cloud3 = -280;
int cloud4= -275;
int cloud2 = 110;
char myName[] = "Sajad Abdolvandi";
char myId[] = "22001504";
int MovingXGlut,MovingYGlut;
int flag = 0;
int flag2 = 0;
int flag3 = 0;
int OldCounter = 0;

//////////////////////////////////
//
// to draw circle, center at (x,y)
// radius r
//
void circle( int x, int y, int r )
{
#define PI 3.1415
   float angle ;
   glBegin( GL_POLYGON ) ;
   for ( int i = 0 ; i < 100 ; i++ )
   {
      angle = 2*PI*i/100;
      glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
   }
   glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
   float angle;

   glBegin(GL_LINE_LOOP);
   for (int i = 0; i < 100; i++)
   {
      angle = 2 * PI*i / 100;
      glVertex2f(x + r*cos(angle), y + r*sin(angle));
   }
   glEnd();
}

void print(int x, int y, const char *string, void *font )
{
   int len, i ;

   glRasterPos2f( x, y );
   len = (int) strlen( string );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, string[i]);
   }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string , ...)
{
   va_list ap;
   va_start ( ap, string );
   char str[1024] ;
   vsprintf( str, string, ap ) ;
   va_end(ap) ;
   
   int len, i ;
   glRasterPos2f( x, y );
   len = (int) strlen( str );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, str[i]);
   }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
   va_list ap;
   va_start(ap, string);
   char str[1024];
   vsprintf(str, string, ap);
   va_end(ap);
   glPushMatrix();
      glTranslatef(x, y, 0);
      glScalef(size, size, 1);
      
      int len, i;
      len = (int)strlen(str);
      for (i = 0; i<len; i++)
      {
         glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
      }
   glPopMatrix();
}

//
// To display onto window using OpenGL commands
//


void DispName(){
    glLineWidth(4);
    glColor3f(.160, .196, .254);
    glRectf(-545, 320, -430, 270);
    glColor3f(1, 1, 1);
    glColor3f( 1, 1, 1 ) ;
    glBegin( GL_LINE_LOOP ) ;
    glVertex2f(-551, 325);
    glVertex2f(-551, 265);
    glVertex2f(-425, 265);
    glVertex2f(-425, 325);
    glEnd() ;
}
void backGround(){
    glColor3f(0.10, 0.45, 0.65);
    glRectf(-575, -115, 575, -350);
}
void Wood(){
    glColor3f(0.266, 0.159, 0.133);
    glRectf(-575, -85, 575, -110);
    glColor3f(0, 0, 0);
    glRectf(-575, -110, 575, -115);
    glColor3f(1, 1, 1);
    glRectf(-575, -88, 575, -85);
}
void Pointer(){
    glColor3f(1, 1, 2);
    circle(movingX,movingY, 3);
    
}
int cloud1 = 440;
void Cloud(int myX, int myY){
    glColor3f(1, 1, 1);
    if (cloud1 <= -650) {
        cloud1 = 700;
    } if (cloud1 <= 700) {
        cloud1-=1;
    }
    glColor3f(1, 1, 1);
    circle(cloud1, myY, 40+ResizeAmount);
    circle(cloud1+50,myY+ 0, 20+ResizeAmount);
    circle(cloud1+39,myY+ 22, 30+ResizeAmount);
    circle(cloud1+-38,myY+ 10, 25+ResizeAmount);
    circle(cloud1+39,myY+ -17, 21+ResizeAmount);
}
void Cloud2(int myX, int myY){
    glColor3f(1, 1, 1);
    if (cloud2 >= 650) {
        cloud2 = -700;
    } if (cloud2 >= -700) {
        cloud2+=1 ;
    }
    circle(cloud2, myY, 40+ResizeAmount);
    circle(50+cloud2,myY+ 0, 20+ResizeAmount);
    circle(cloud2+39,myY+ 22, 30+ResizeAmount);
    circle(cloud2-38,myY+ 10, 25+ResizeAmount);
    circle(cloud2+39,myY+ -17, 21+ResizeAmount);

}
void Cloud4(int myX, int myY){
    glColor3f(1, 1, 1);
    if (cloud4 <= -650) {
        cloud4 = 700;
    } if (cloud4 <= 700) {
        cloud4-=1;
    }
    circle(cloud4, myY, 40+ResizeAmount);
    circle(50+cloud4,myY+ 0, 20+ResizeAmount);
    circle(cloud4+39,myY+ 22, 30+ResizeAmount);
    circle(cloud4-38,myY+ 10, 25+ResizeAmount);
    circle(cloud4+39,myY+ -17, 21+ResizeAmount);

}
void CloudReverse(int myX, int myY){
    glColor3f(1, 1, 1);
    if (cloud3 >= 650) {
        cloud3 = -700;
    } if (cloud3 >= -700) {
        cloud3+=1 ;
    }
    circle(cloud3, myY, 40+ResizeAmount);
    circle(cloud3-50,myY+0, 20+ResizeAmount);
    circle(cloud3-39,myY+22, 30+ResizeAmount);
    circle(cloud3+38,myY+10, 25+ResizeAmount);
    circle(cloud3-39,myY-17, 21+ResizeAmount);
   
}
void tree(int myX, int myY){
    glColor3f(0.5607, 0.356, 0.211);
    glRectf(myX, myY, myX+20, myY+60);
    glColor3f(0.125, 0.278, 0.06);
    glBegin(GL_TRIANGLES);
    glVertex2f(myX-60, myY+40);
    glVertex2f(myX+10, myY+80);
    glVertex2f(myX+80, myY+40);
    glEnd();
    glColor3f(0.125, 0.278, 0.06);
    glBegin(GL_TRIANGLES);
    glVertex2f(myX-80, myY+40);
    glVertex2f(myX+10, myY+80);
    glVertex2f(myX+100, myY+40);
    glEnd();
    glColor3f(0.213, 0.488, 0.09);
    glBegin(GL_TRIANGLES);
    glVertex2f(myX-60, myY+70);
    glVertex2f(myX+10, myY+110);
    glVertex2f(myX+80, myY+70);
    glEnd();
    glColor3f(0.262, 0.622, 0.106);
    glBegin(GL_TRIANGLES);
    glVertex2f(myX-40, myY+100);
    glVertex2f(myX+10, myY+140);
    glVertex2f(myX+60, myY+100);
    glEnd();
    glColor3f(1, 1, 1);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(myX-5, myY+130);
    glVertex2f(myX+10, myY+140);
    glVertex2f(myX+25, myY+130);
    glEnd();
}
void DispComp(){
    if (state == NOT_ANIMATING) {
      /*
        for (int s = 0; s<OldCounter; s++) {
        
            ObjX[s]+=moveSpeed[s];
        }
       */
       
        glColor3b(0.160, 0.196, 0.254);
        glBegin(GL_POLYGON);
        glLineWidth(4);
        glVertex2f(ObjX[lp]-50, ObjY[lp]);
        glVertex2f(ObjX[lp]-40, ObjY[lp]-20);
        glVertex2f(ObjX[lp]+40, ObjY[lp]-20);
        glVertex2f(ObjX[lp]+50, ObjY[lp]);
        glEnd();
        glColor3f(1, 1, 1);
        glRectf(ObjX[lp]-50, ObjY[lp], ObjX[lp]+50, ObjY[lp]-4);
        glColor3f(1, 1, 1);
        circle(ObjX[lp]+25, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]+25, ObjY[lp]-12, 3);
        //
        glColor3f(1, 1, 1);
        circle(ObjX[lp]+0, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]+0, ObjY[lp]-12, 3);
        //
        glColor3f(1, 1, 1);
        circle(ObjX[lp]-25, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]-25, ObjY[lp]-12, 3);
        glColor3f(0.1, 0.1, 0);
        glRectf(ObjX[lp]-15, ObjY[lp], ObjX[lp]-25, ObjY[lp]+25);
        glRectf(ObjX[lp]+15, ObjY[lp], ObjX[lp]+20, ObjY[lp]+15);
        glColor3f(0.921, 0.368, 0.156);
        glRectf(ObjX[lp]-15, ObjY[lp]+20, ObjX[lp]-25, ObjY[lp]+25);
        glRectf(ObjX[lp]+15, ObjY[lp]+10, ObjX[lp]+20, ObjY[lp]+15);
        // print the object count
        //check if is under nine print with a different X because "10" is two digits and it visualizes badly when it overlaps one part of the ship, so i changed the X coords on the 10th ship.
        if (lp==9) {
            vprint(ObjX[lp]-10, ObjY[lp], GLUT_BITMAP_HELVETICA_18, "%d",lp+1);
        }else
            vprint(ObjX[lp]-5, ObjY[lp], GLUT_BITMAP_HELVETICA_18, "%d",lp+1);

    }
    if (state == ANIMATING) {
        // check if the ships passed the window, set the coordinates
        /*
        if (ObjX[lp]+moveSpeed[lp] >= 700) {
            ObjX[lp] = -700; // change their moving coordinates to come again from the other side
            coords[lp][0] = -700; // change their first coordinate so they don't flash and stutter in displaying (displaying their moving coordinates + displaying their first coordinates)
            // make the speed zero so they wont spawn in a different place
            moveSpeed[lp] = 0;
        }
        else{
            // if they did not passed the window yet, just add the speed
            ObjX[lp]+=moveSpeed[lp];

        }
         */
        glColor3b(0.160, 0.196, 0.254);
        glBegin(GL_POLYGON);
        glLineWidth(4);
        glVertex2f(ObjX[lp]-50, ObjY[lp]);
        glVertex2f(ObjX[lp]-40, ObjY[lp]-20);
        glVertex2f(ObjX[lp]+40, ObjY[lp]-20);
        glVertex2f(ObjX[lp]+50, ObjY[lp]);
        glEnd();
        glColor3f(1, 1, 1);
        glRectf(ObjX[lp]-50, ObjY[lp], ObjX[lp]+50, ObjY[lp]-4);
        glColor3f(1, 1, 1);
        circle(ObjX[lp]+25, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]+25, ObjY[lp]-12, 3);
        //
        glColor3f(1, 1, 1);
        circle(ObjX[lp]+0, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]+0, ObjY[lp]-12, 3);
        //
        glColor3f(1, 1, 1);
        circle(ObjX[lp]-25, ObjY[lp]-12, 5);
        glColor3f(0.921, 0.368, 0.156);
        glLineWidth(3);
        circle_wire(ObjX[lp]-25, ObjY[lp]-12, 3);
        glColor3f(0.1, 0.1, 0);
        glRectf(ObjX[lp]-15, ObjY[lp], ObjX[lp]-25, ObjY[lp]+25);
        glRectf(ObjX[lp]+15, ObjY[lp], ObjX[lp]+20, ObjY[lp]+15);
        glColor3f(0.921, 0.368, 0.156);
        glRectf(ObjX[lp]-15, ObjY[lp]+20, ObjX[lp]-25, ObjY[lp]+25);
        glRectf(ObjX[lp]+15, ObjY[lp]+10, ObjX[lp]+20, ObjY[lp]+15);
        if (lp==9) {
            vprint(ObjX[lp]-10, ObjY[lp], GLUT_BITMAP_HELVETICA_18, "%d",lp+1);
        }else
            vprint(ObjX[lp]-5, ObjY[lp], GLUT_BITMAP_HELVETICA_18, "%d",lp+1);
    }
}
void buildings(){
    glColor3f(0.2, 0.2, 0.2);
    glRectf(-565, -100, -400, 200);
    glColor3f(0.8, 0.8, 0.8);
    glRectf(-380, -100, -400, 140);
    glColor3f(0.23, 0.43, 0.44);
    glRectf(-510, 170, -455, 120);
    glRectf(-510, 100, -455, 80);
    glRectf(-510, 170, -455, 120);
    glRectf(-510, 70, -455, -70);
    glColor3f(0.23, 0.43, 0.44);
    glEnd();
    glColor3f(0.9, 0.9, 0.9);
    glRectf(-555, -110, -410, 190);
    glColor3f(0.23, 0.43, 0.44);
    glRectf(-510, 170, -455, 120);
    glRectf(-510, 100, -455, 80);
    glRectf(-510, 170, -455, 120);
    glRectf(-510, 70, -455, -70);
    glColor3f(.8, 0.8, 0.8);
    glRectf(-350, -110, 100, 110);
    glColor3f(0.20, 0.20, 0.20);
    glRectf(-330, -110, 80, 90);
    glColor3f(1, 1, 1);
    glRectf(-350, 110, 100, 115);
    glRectf(-565, 200, -400, 205);
    glRectf(-400, 140, -380, 145);
    glColor3f(0.23, 0.43, 0.44);
    glRectf(-290, 0, 40, 50);
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(265, -100);
    glVertex2f(420, 1000);
    glVertex2f(575, -100);
    glEnd();
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_TRIANGLES);
    glVertex2f(275, -100);
    glVertex2f(420, 1000);
    glVertex2f(565, -100);
    glEnd();
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_TRIANGLES);
    glVertex2f(285, -100);
    glVertex2f(420, 1000);
    glVertex2f(555, -100);
    glEnd();
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2f(295, -100);
    glVertex2f(420, 1000);
    glVertex2f(545, -100);
    glEnd();
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_TRIANGLES);
    glVertex2f(305, -100);
    glVertex2f(420, 1000);
    glVertex2f(535, -100);
    glEnd();
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_TRIANGLES);
    glVertex2f(315, -100);
    glVertex2f(420, 1000);
    glVertex2f(525, -100);
    glEnd();
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(325, -100);
    glVertex2f(420, 1000);
    glVertex2f(515, -100);
    glEnd();
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(335, -100);
    glVertex2f(420, 1000);
    glVertex2f(505, -100);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(345, -100);
    glVertex2f(420, 1000);
    glVertex2f(495, -100);
    glEnd();
    glLineWidth(5);
    glColor3f(0.23, 0.43, 0.44);
    circle_wire(420, 320, 10);
    circle_wire(420, 270, 20);
    circle_wire(420, 200, 30);
    circle_wire(420, 110, 40);
    circle_wire(420, 0, 50);
}

void display() {
 
   glClearColor(0.5960, 0.7568, 0.8509, 1);
   glClear(GL_COLOR_BUFFER_BIT);
    glColor3b(0.160, 0.196, 0.254);
    Cloud2(110, 145);
    Cloud4(-105,180);
    buildings();
    Wood();
    backGround();
    Cloud(440,275);
    DispName();
    Pointer();
    CloudReverse(-280,200);
    tree(-410,-85);
    tree(-210,-85);
    tree(-10,-85);
    tree(190,-85);
    tree(390,-85);
    glLineWidth(1);
    vprint2(-540, 300, 0.1, myName);
    vprint2(-540, 280, 0.1, myId);
    glColor3f(0, 0, 0);
    // display the sentence
    if (state == NOT_ANIMATING) {
        vprint(-200, 320, GLUT_BITMAP_HELVETICA_18, Statement1);
// STOP sentence
    }else
        vprint(-200, 320, GLUT_BITMAP_HELVETICA_18, Statement2);

// coordinates

    vprint(430, -340,GLUT_BITMAP_HELVETICA_12, "OpenGL(X:%d,Y:%d)" ,movingX,movingY);
    vprint(430, -320,GLUT_BITMAP_HELVETICA_12, "GLUT(X:%d,Y:%d)",MovingXGlut,MovingYGlut);
    vprint(-170, 300, GLUT_BITMAP_HELVETICA_18, "Press + OR - to resize the clouds!");
    vprint(-155, 280, GLUT_BITMAP_HELVETICA_18, "Press \"R\" to RESTART the app!");
    vprint(-250, 260, GLUT_BITMAP_HELVETICA_18, "Press \"<-\" OR \"->\" To change the speed and direction!");


    //vprint2(480, -330, 0.1, "lp:%d  MS:%d",lp,moveSpeed[lp]);
    // display every object simultaneously
    for (lp= 0; lp<ObjCounter; lp++) {
        if (coords[lp][0] <= 800 && direction == TORIGHT)
            coords[lp][0] += moveSpeed;
        else if(coords[lp][0] >= 700 && direction == TORIGHT)
            coords[lp][0] = -700;
        else if (coords[lp][0] <= -700 && direction == TOLEFT){
            coords[lp][0] = 700;
        }
        else if(coords[lp][0] > -700 && direction == TOLEFT){
            coords[lp][0] += moveSpeed;
        }
      

         
        ObjX[lp] = coords[lp][0];
        ObjY[lp] = coords[lp][1];
       
        DispComp();
        
    }
    
   


    glutSwapBuffers();

}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    if (key == 43) {
        if (ResizeAmount>=30) {
    
        }else
        ResizeAmount++;
    }
    else if (key == 45){
        if (ResizeAmount<=-6) {
    
        }else
        ResizeAmount--;
    }
    if (key == 114) {
        state = NOT_ANIMATING;
        moveSpeed=0;
        lp = 20;
        ObjCounter = 0;
        for (int i = 0; i<ObjCounter; i++) {
            coords[i][0] = 0;
            coords[i][1] = 0;

        }
    }
  
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

void onKeyUp(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = true; break;
   case GLUT_KEY_DOWN: down = true; break;
   case GLUT_KEY_LEFT: left = true; break;
   case GLUT_KEY_RIGHT: right = true; break;
   }
    // change the state of the game
    if (key == GLUT_KEY_F1 && state == NOT_ANIMATING && ObjCounter != 0) {
        
        state = ANIMATING;
        moveSpeed = 1;
        flag2 =1;
    }
    else if(key == GLUT_KEY_F1  && state == ANIMATING){
        state = NOT_ANIMATING;
        moveSpeed=0;
    }
    if (key == GLUT_KEY_RIGHT  && state == ANIMATING) {
        moveSpeed++;
        if (moveSpeed > 0) {
            direction = TORIGHT;
        }else if (moveSpeed <0)
            direction = TOLEFT;
    }
    if (key == GLUT_KEY_LEFT  && state == ANIMATING) {
        moveSpeed--;
        if (moveSpeed > 0) {
            direction = TORIGHT;
        }else if (moveSpeed <0)
            direction = TOLEFT;
    }
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = false; break;
   case GLUT_KEY_DOWN: down = false; break;
   case GLUT_KEY_LEFT: left = false; break;
   case GLUT_KEY_RIGHT: right = false; break;
   }

   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//

void onClick( int button, int stat, int x, int y )
{
   // Write your codes here.
    // limitation for the area, for having a better view and a better app, without this X and Y limitations you will see a lot of bad visuals for example i dont want the ships t spawn at sky or on the wood or on the vprint of coordinates.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && ObjCounter<10 && movingY<-135 && movingY> -280 && movingX <520 && movingX > -520 ) {
       
      
        // set the coordinates JUST for the first ship
        if (ObjCounter == 0) {
            coords[ObjCounter][0] = x - winWidth / 2;
            coords[ObjCounter][1] = winHeight / 2 - y;
            ObjCounter++;
        }else{
            // compare all coordinates to the moving pointer to prevent overlapping
            for (int i = 0; i<10; i++) {
               
                // check if game is animated once, change the way of comparing (instead of comparing pointer X and Y with thefirst coordinates compare the moving pointer to the moving coordinates of objects)
             if (flag2 == 0) {
                    if ( movingX <= coords[i][0]+100 && movingX >= coords[i][0]-100&& movingY <= coords[i][1]+50&&movingY>=coords[i][1]-50 ){
                        flag=1;
                        }
                }
              
              else if(flag2 ==1)
                {
                    // check if game is animated once, change the way of comparing (instead of comparing pointer X and Y with thefirst coordinates compare the moving pointer to the moving coordinates of objects)
                    if ( movingX <= coords[i][0]+100 && movingX >= coords[i][0]-100&& movingY <= coords[i][1]+50&&movingY>=coords[i][1]-50 ){
                        flag=1;
                        }
                    
                }
               
                
            }
              
            // PREVENT OVERLAPPING OBJECTS: if the limitation of X and Y is exceeded, it will do NOTHING, because it will overlap
            if (flag == 1) {

            }else {
                
                coords[ObjCounter][0] = x - winWidth / 2;
                coords[ObjCounter][1] = winHeight / 2 - y;
                OldCounter = ObjCounter;
                ObjCounter++;
            }
            flag = 0;
                
                    
        }
        
    
     
            

       
      

         }

    glutPostRedisplay() ;
    }
   
   // to refresh the window it calls display() function


//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
   winWidth = w;
   winHeight = h;
   glViewport( 0, 0, w, h ) ;
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
   glMatrixMode( GL_MODELVIEW);
   glLoadIdentity();
   display(); // refresh window.
}

void onMoveDown( int x, int y ) {
   // Write your codes here.


   
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 =
void onMove( int x, int y ) {
   // Write your codes here.
    movingY = winHeight / 2 - y;
    movingX = x - winWidth / 2;
    MovingXGlut= x;
    MovingYGlut=y;
   
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

#if TIMER_ON == 1
void onTimer( int v ) {
    
   glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
   // Write your codes here.

// check if the state is animating, increment the speed of every object in every sequence of runtime.
  
   // to refresh the window it calls display() function
   glutPostRedisplay() ; // display()

}
#endif

void Init() {
   
   // Smoothing shapes
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
}

int main( int argc, char *argv[] ) {
  
    glutInit(&argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Cyber Lake");
 
    glutDisplayFunc(display);
    glutReshapeFunc(onResize);
     
    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
     

    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);
    
    #if  TIMER_ON == 1
    // timer event
    glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
    #endif

    Init();
    
    glutMainLoop();

}
