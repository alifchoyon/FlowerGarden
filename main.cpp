#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

float PI=3.1416;

static float	tx	=  0.0;
static float	ty	=  0.0;



int seed=2018;

int buffer_seed=time(NULL);

float e=1;
float b_x=0;

int sunny=1;

void reset_seed()
{
    buffer_seed=time(NULL);
}

double r2()
{
    double r=(double)rand() / (double)RAND_MAX;
    return r;
}


double r2_b()
{
    double r=(double)rand() / (double)RAND_MAX;
    return r;
}


float r2_s=0;
double r2_sticky()
{
    r2_s=r2_s+0.0000001;
    if(r2_s>1)
        r2_s=0;

    return r2_s ;
}
void animate()
{

    {
        for(int i=0; i<5;)
        {

            i=i+1;
            tx=tx+i;

            glutPostRedisplay();
        }

        for(int i=0; i<5;)
        {

            i=i-.5;
            tx=tx+i;

            glutPostRedisplay();
        }



    }

}

float petal_color_r=.9;
float petal_color_g=.9;
float petal_color_b=.9;

void petal(float x, float y, float radius_x, float radius_y)
{
    int i = 0;
    float angle = 0.0;


    glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {
        angle = 2*PI*i/100;
        float rx,ry;

        rx=x+cos(angle) * radius_x;
        ry=y+ sin(angle) * radius_y;


        if(rx*rx+ry*ry<=radius_x*radius_x  && rx!=radius_x)
        {

            if(r2()>.5)
                glColor3f(petal_color_r-.1,petal_color_g-.1,petal_color_b-.1);

            else
                glColor3f(petal_color_r,petal_color_g,petal_color_b);

            glVertex3f (x+cos(angle) * radius_x,y+ sin(angle) * radius_y, 0);
        }
        else
        {




        }


    }
    glEnd();

}

void circle(float x, float y,float radius_x, float radius_y)
{

    int i = 0;
    float angle = 0.0;

    for(i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;

        if(i%  (int)((13-5)*r2()+5)==0)
        {

            petal( x+cos(angle) * radius_x, y+sin(angle) * radius_y,2, 2);

        }
    }

}


void circle_primitive(float x, float y,float radius_x, float radius_y)
{

    int i = 0;
    float angle = 0.0;

    glColor3f(1,1,1);

    glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {

        if(r2()>=.5)
            glColor3f(1,.9,1);

        else
        {

            glColor3f(1,1,1);

        }
        angle = 2 * PI * i / 100;
        glVertex3f (x+cos(angle) * radius_x, y+sin(angle) * radius_y, 0);


    }

    glEnd();




}


void circle_sun(float x, float y,float radius_x, float radius_y)
{

    int i = 0;
    float angle = 0.0;

    glColor3f(1,1,0);

    glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {

        if(r2()>=.5)
            glColor3f(1,.9,0);

        else
        {

            glColor3f(1,1,0);

        }
        angle = 2 * PI * i / 100;
        glVertex3f (x+cos(angle) * radius_x, y+sin(angle) * radius_y, 0);


    }

    glEnd();

}

void flower_primitive(float x, float y)
{


    float length = 10;

    glColor3f(0,0,0);

    glBegin(GL_POLYGON);

    glVertex2f (x-.1,y+0);
    glVertex2f (x+.1,y+0);
    glVertex2f (x+.1,y-length);
    glVertex2f (x-.1,y-length);



    glEnd();
    glRotatef(ty,r2(),r2(),r2());

    //2 2

    petal_color_r=r2();
    circle(x,y,1+r2(),1+r2());


}

void flower(float traslate_x,float traslate_y,float traslate_z)
{


    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);

    glTranslatef(traslate_x,traslate_y,traslate_z);
    glScaled(.5,.5,1);

    flower_primitive(0, 0);
    glPopMatrix();

}


void cloud(float traslate_x,float traslate_y,float traslate_z,float x,float y)
{

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);

    glTranslatef(traslate_x,traslate_y,traslate_z);
    for(int j=0; j<200; j++)
        circle_primitive(r2()*x,r2()*y,r2(),r2());


    glPopMatrix();

}



float sr,sg,sb;

void disp1()
{

    int skyrange=5;
//skycolor
    if(sunny==1)
    {
        glPushMatrix();
        glColor3f(0,1-r2_sticky(),1);
        glBegin(GL_POLYGON);
        glVertex2f(-(skyrange),skyrange);
        glColor3f(0,1-r2_sticky(),1);
        glVertex2f(skyrange,skyrange);
        glColor3f(0,1-r2(),1);
        glVertex2f(skyrange,-skyrange);
        glColor3f(0,1-r2(),1);
        glVertex2f(-skyrange,-skyrange);
        glColor3f(0,1-r2(),1);
        glEnd();


        glPushMatrix();
        glTranslated(0,4,0);
        glScaled(.5,.5,1);
        glColor3f(1,1,0);
        circle_sun(0,0,2,2);
        glPopMatrix();

        glPopMatrix();

    }

    else
    {

        glPushMatrix();

        glColor3f(sr,sg,sb);


        glBegin(GL_POLYGON);
        glVertex2f(-(skyrange),skyrange);
        glVertex2f(skyrange,skyrange);
        glVertex2f(skyrange,-skyrange);
        glVertex2f(-skyrange,-skyrange);
        glEnd();

        glPopMatrix();



    }

    glPushMatrix();


    for(float i = -5 ; i<=5 ; i=i+.5)
    {

        if(sunny==1)
        {
            if(r2()<.8)
            {

                petal_color_r=.9+r2()*.2;
                petal_color_g=0;
                petal_color_b=0;
            }
            else
            {

                petal_color_r=.9;
                petal_color_g=.9;
                petal_color_b=0;

            }

        }
        else
        {


            if(r2()<.8)
            {

                petal_color_r=.9+r2()*.2;
                petal_color_g=1;
                petal_color_b=1;
            }
            else
            {

                petal_color_r=1;
                petal_color_g=1;
                petal_color_b=1;

            }

        }

        glTranslatef(r2()*.00005,0,0);
        flower(i,r2()*(-3),r2_sticky()*2);







        if( (int)(r2()*100)%5==0 )
        {


            glPushMatrix();
            glTranslatef(0,2,0);
            glScaled(.5,.5,1);
            cloud(tx+(4)*r2()+4,4*r2()+2,2*r2(),i,r2()*2);
            glPopMatrix();

        }




    }




    glPopMatrix();

}

void grass()
{

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glColor3f(0,1-r2(),0);
    glVertex2f(r2()*.1+.1,.3);
    glColor3f(0,1-r2(),0);
    glVertex2f(r2()*.1+.1,.6);
    glColor3f(0,1-r2(),0);

    glVertex2f(0,.9);
    glColor3f(0,1-r2(),0);

    glVertex2f(r2()*-.05-.1,1.2);
    glColor3f(0,1-r2(),0);
    glVertex2f(0,r2()+1.5);
    glColor3f(0,1-r2(),0);


    glVertex2f(r2()*-.05-.1+.2,1.2);
    glColor3f(0,1-r2(),0);
    glVertex2f(0+.23,.9);
    glColor3f(0,1-r2(),0);
    glVertex2f(r2()*.25+.1,.6);
    glColor3f(0,1-r2(),0);
    glVertex2f(r2()*.1+.1+.27,.3);
    glColor3f(0,1-r2(),0);
    glVertex2f(.3,0);
    glColor3f(0,1-r2(),0);

    glEnd();

}


void disp2()
{

    glPushMatrix();




    glTranslatef(0,-5,0);

    for(int i=0 ; i<1000; i++)
    {
        glTranslatef(r2()*(5+5)-5,0,0);
        grass();

    }

    glPopMatrix();

}


float bpx,bpy;

float br=1;
float bu=1;
void animate_butterfly()
{

    seed=time(NULL);


    printf("%f\t%f\n",bpx,bpy);

    if(bpx>5)
    {
        br=0;
    }

    if(bpx<-5)
        br=1;


    if(br==1)
    {

        bpx+=r2()*(.05);



        bpy+=r2()*(.05);


    }
    else
    {

        bpx-=r2()*(.05);


        bpy-=r2()*(.05);


    }

    b_x+=30;

    seed=buffer_seed;
    glutPostRedisplay();



}

void disp3()
{

    glPushMatrix();


    glTranslatef(bpx,bpy,0);
    glRotatef(b_x,1,0,0 );
    glRotatef(180,1,1,0 );

    glBegin(GL_POLYGON);

    glVertex2f(0,.5);
    glColor3f(1,0,0);
    glVertex2f(1,0);
    glColor3f(0,1,0);
    glVertex2f(.5,1);
    glColor3f(0,0,1);
    glVertex2f(1,2);
    glColor3f(1,0,0);
    glVertex2f(0,1.5);
    glColor3f(0,0,1);
    glEnd();
    glPopMatrix();
}

float rx=0;
void rain()
{
    rx=rx+0.05;
    glPushMatrix();
    glPushMatrix();
    glTranslated(0,-(rx),0);

    for(int i=0; i<10000; i++)
        circle_primitive(r2()*10-5,r2()*100-50,.025,.05);

    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    for(int i=0; i<10000; i++)
        circle_primitive(r2()*10-5,r2()*(-1)-4,.025,.05);
    glPopMatrix();
    glutPostRedisplay();
}


double r2_timeless()
{

    srand(time(NULL));
    double r=(double)rand() ;
    srand(buffer_seed);
    printf("%f\n",r);
    return r;
}
void display(void)
{

    srand(seed);
    glClear(GL_COLOR_BUFFER_BIT);
    if(sunny==1)
    {

        disp1();
        disp2();
        disp3();
    }
    else
    {
        disp1();
        disp2();
        rain();

    }
    glFlush();
}



void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-5.0*e, 5.0*e, -5.0*e, 5.0*e, -5.0*e, 5.0*e);
}



void spe_key(int key, int x, int y)
{

    switch (key)
    {

    case GLUT_KEY_LEFT:

        tx -=.1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:

        tx +=.1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:

        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:

        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void animate_cloud_left()
{
    tx -=.01;
    glutPostRedisplay();
}
void my_keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 'n':
        reset_seed();
        seed=buffer_seed;
        glutPostRedisplay();
        break;

    case 'l':
        glutIdleFunc(animate_cloud_left);
        break;

    case 'b':
        bpx=-5;
        bpy=-1;
        glutIdleFunc(animate_butterfly);
        break;

    case 's':
        glutIdleFunc(NULL);
        sunny=1;
        glutPostRedisplay();
        break;

    case 'r':
        glutIdleFunc(NULL);
        rx=0;
        sunny=0;
        glutIdleFunc(rain);
        glutPostRedisplay();
        break;

    case 't':
        b_x=b_x-40;
        printf("%f\n",b_x);
        glutPostRedisplay();
        break;

    default:
        break;
    }
}
int main()
{
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1000, 1000);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Flower Garden");
    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(spe_key);//up,down,left,right
    glutMainLoop();


    return 0;   /* ANSI C requires main to return int. */
}

