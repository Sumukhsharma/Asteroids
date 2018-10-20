#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
float px[3]={0.0,0.0,1.0};//point x of triangle
float py[3]={50.0,50.0,1.0};//point y of triangle
float pz[3]={100.0,0.0,1.0};//point z of triangle
float u[3]={0.0,0.0,0.0};//missile point
int k=0;//count of iterations
float speed=0.1;//decrement of y of the block
int i=0;
//float j = 0;
float m=0;//missile incremententation
int flag=0,welcome=1;
int flag2=1;//flag2 for speed reset
float a[3]={300.0,1000.0,0.0};//a co-ordinate of the block
float b[3],c[3],d[3];//other points of the block
float temp[3];//calculating the vaulve of u[1]+m and storing it (as u[1]=u[1]+m; was getting reinitalised
int collisionflag=0;
int asteroidflag=1;
float s1=1,s2=1,s3=1;
float colors[3][3];
int x1=0;
int points=0,count=0;
char points1[100];
void blocks();
void resize(float x1,float x2,float x3)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x1,x2,x3);
	glMatrixMode(GL_PROJECTION);
	glColor3f(colors[1][0],colors[1][1],colors[1][2]);
	glBegin(GL_TRIANGLES);//spaceship
	glVertex3fv(px);
	glVertex3fv(py);
	glVertex3fv(pz);
	glEnd();
}
//void spaceship(float x1,float x2,float x3)
//{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glScalef(x1,x2,x3);
//	glMatrixMode(GL_PROJECTION);
//	glColor3f(colors[1][0],colors[1][1],colors[1][2]);
//	//glColor3f(1,0,0);
//	glBegin(GL_TRIANGLES);//spaceship
//	glVertex3fv(px);
//	glVertex3fv(py);
//	glVertex3fv(pz);
//	glEnd();
//}
void asteroidcolor(int id)
{
	switch(id)
	{
	case 1:colors[0][0]=1;
			colors[0][1]=0;
			colors[0][2]=0;
		break;
	case 2:colors[0][0]=0;
			colors[0][1]=0;
			colors[0][2]=1;
		break;
	case 3:colors[0][0]=0;
			colors[0][1]=1;
			colors[0][2]=0;
		break;
	}
}
void shipcolor(int id)
{switch(id){
	case 4:colors[1][0]=1;
			colors[1][1]=0;
			colors[1][2]=0;
		break;
	case 5:colors[1][0]=0;
			colors[1][1]=0;
			colors[1][2]=1;
		break;
	case 6:colors[1][0]=0;
			colors[1][1]=1;
			colors[1][2]=0;
		break;
}
}
void top_menu(int id)
{
	switch(id)
	{
	
			case 7:exit(0);
	}
}

void font(void *font, char *text, int x, int y)
{
	glRasterPos2i(x, y);
	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}
void blocks()
{	
	if(temp[0]>=d[0]&&temp[1]>=d[1]&&temp[0]<=c[0])//check for collision
	{	sprintf(points1,"%d",points);
		points++;
		count++;
		collisionflag=1;//block will disappear(collision has occured)
		a[0]=rand()%800;
		a[1]=1000;
		u[0]=0;//assign the vaules of the missile to 0
		u[1]=0;//----"-----
		u[2]=0;//----"----
		collisionflag=0;//allow the creation of blocks again
		glutPostRedisplay();	
	}
	if(((py[0]+x1)>=d[0]&&py[1]>=d[1]&&(py[0]+x1)<=c[0]))//check for collision of the point with the spaceship
	{
		welcome=4;
		a[0]=rand()%800;
		a[1]=1000;
	}
	if(!collisionflag)//check for collision(if true the execute)
	{
		b[0]=a[0]+100;
		b[1]=a[1];
		b[2]=0;
		c[0]=b[0];
		c[1]=b[1]-100;
		c[2]=0;
		d[0]=c[0]-100;
		d[1]=c[1];
		d[2]=0;
		glColor3f(colors[0][0],colors[0][1],colors[0][2]);
		//glColor3f(1,0,0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glBegin(GL_POLYGON);//create square asteroid
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
		glVertex3fv(d);
		glEnd();
		glMatrixMode(GL_PROJECTION);
		glFlush();
		glutPostRedisplay();
		if(k==10)
		{
			if(count%6==0)
			{
				speed+=0.2;count+=1;
			}
			if(!flag2){speed=0.1;flag2=1;}
		a[1]=a[1]-speed;
		printf("%f\n",speed);//drop the square by speed distance
		k=0;//reassign k to zero
		}
	k++;
	if(d[1]<=0)//if the block goes below the window then reassign the block
	{
		a[0]=rand()%800;
		a[1]=1000;
	}
	}

}

void missile()
{
	if(flag){
	if(m<1000)
	{
			glPointSize(8);
			glColor3f(1.0,1.0,0.0);
			//glBegin(GL_POINTS);
			//glVertex3f(u[0],u[1]+m,u[2]);
			temp[0]=u[0];//temp to check the collision of the missile
			temp[1]=u[1]+m;
			temp[2]=u[2];
			glutPostRedisplay();
			glBegin(GL_LINE_LOOP);
			glVertex3f(u[0],u[1]+m,u[2]);//top left of the missile
			glVertex3f(u[0]+1,u[1]+m,u[2]);//top right of the missile
			glVertex3f(u[0]+1,u[1],u[2]);//bottom right of the missile
			glVertex3f(u[0],u[1],u[2]);//bottom left of the missile
			glEnd();
			glFlush();
			glColor3f(1.0,0.0,0.0);
	}
		m+=0.25;//increment the asteroid by the m in y-direction
		glutPostRedisplay();
		glFlush();
	}
	if(m==1000)//if it reaches the top then remove the missile
		flag=0,m=0;
	
}

void myInit()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,1000.0,0.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
}
void myKey(unsigned char key,int a,int b)
{
	switch(key)
	{
	case 'a':if(x1>=0)
			 {
				x1-=30;
				resize(x1,0,0);
			 }
			break;
		case 'd':
			if(x1<=930)
			{
				x1+=30;
				resize(x1,0,0);
			}
			break;
		case ' ':flag = 1;  //launch the missile
			glutPostRedisplay();
			u[0]=py[0]+x1;
			u[1]=py[1];
			u[2]=py[2];
			break;
		//case '+':if(s1<=1.9){
		//		s1+=0.5;
		//		s2+=0.5;
		//		}
		//		break;
		//case '-':if(s1>=0.6){
		//		s1-=0.5;
		//		s2-=0.5;
		//		 }
		//		break;
		case '1':welcome=2;
			glutPostRedisplay();
			break;
		 case '2':welcome=3;
			glutPostRedisplay();
			break;
		 case 'r':welcome=1;
			 points=0;
			 sprintf(points1,"%d",points);
			 flag2=0;
		 		glutPostRedisplay();
				break;
	
	} 
}
void mymouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && welcome==3)
	{
		////if(px[0]>=0){//move to left
	/*	px[0]-=30.0;
		py[0]-=30.0;
		pz[0]-=30.0;
		i=0;
		glutPostRedisplay();*/
		if(x1>=0)
		{
			x1-=30;
			resize(x1,0,0);
		}
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN && welcome==3)
	{	
		//if(px[0]<=900){ //move to right
		/*px[0]+=30.0;
		py[0]+=30.0;
		pz[0]+=30.0;
		i=0;
		glutPostRedisplay();*/
		if(x1<=930)
		{
			x1+=30;
			resize(x1,0,0);
		}
	}
	if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN && welcome==3)
	{
		flag = 1;  //launch the missile
		glutPostRedisplay();
		u[0]=py[0]+x1;
		u[1]=py[1];
		u[2]=py[2];
	}
}

void display()
{	
	int Asteroid,Spaceship;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	if(welcome==1)
	{
		font(GLUT_BITMAP_HELVETICA_18, "...........WELCOME TO ASTEROID GAME ........", 500.0, 700.0);
		font(GLUT_BITMAP_HELVETICA_18, " A MINI PROJECT ON COMPUTER GRAPHICS ", 550.0, 80.0);
		font(GLUT_BITMAP_HELVETICA_18, "DEPATMENT OF CSE", 670.0, 50.0);
		font(GLUT_BITMAP_HELVETICA_18, "Under The Guidence Of:-> ", 650.0, 300.0);
		font(GLUT_BITMAP_HELVETICA_18, "BATCH:-> ", 650.0, 350.0);
		font(GLUT_BITMAP_HELVETICA_18, "SECTION:-> ", 650.0, 400.0);
		font(GLUT_BITMAP_HELVETICA_18, "USN:->", 650.0, 450.0);
		font(GLUT_BITMAP_HELVETICA_18, "NAME:->", 650.0, 500.0);
		font(GLUT_BITMAP_HELVETICA_18, "*******************************************************************************************************************************", 400.0, 600.0);	
		font(GLUT_BITMAP_HELVETICA_18, "Press 1 to select color of spaceship and asteroid",200,80);
		font(GLUT_BITMAP_HELVETICA_18, "Press 2 to start the game",200,50);	
		//print(100,100,0,str);
	}
	else if(welcome==2)
	{
		font(GLUT_BITMAP_HELVETICA_18, "...........SELECT COLOR OF ASTEROID AND SPACESHIP, RIGHT CLICK FOR OPTIONS........", 300.0, 500.0);
		font(GLUT_BITMAP_HELVETICA_18, "Press 2 to start the game",400,80);	
		Asteroid=glutCreateMenu(asteroidcolor);
		glutAddMenuEntry("Red",1);
		glutAddMenuEntry("Blue",2);
		glutAddMenuEntry("Green",3);
		Spaceship=glutCreateMenu(shipcolor);
		glutAddMenuEntry("Red",4);
		glutAddMenuEntry("Blue",5);
		glutAddMenuEntry("Green",6);
		glutCreateMenu(top_menu);
		glutAddSubMenu("Asteroid",Asteroid);
		glutAddSubMenu("Spaceship",Spaceship);
		glutAddMenuEntry("Quit",7);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	else if(welcome==3)
	{
		font(GLUT_BITMAP_HELVETICA_18, "", 500.0, 800.0);
		glutDetachMenu(GLUT_RIGHT_BUTTON);
		resize(x1,0,0);
		//spaceship(s1,s2,s3);
		blocks();
		missile();
		glutPostRedisplay();
	}
	else if(welcome==4)
	{
	glutPostRedisplay();
	font(GLUT_BITMAP_HELVETICA_18, "SCORE=", 300.0, 700.0);
	font(GLUT_BITMAP_HELVETICA_18, points1, 500.0, 700.0);
	font(GLUT_BITMAP_HELVETICA_18, "GAME OVER!!!!!", 300.0, 500.0);
	font(GLUT_BITMAP_HELVETICA_18, "Press R key to go to MAIN MENU", 300.0, 400.0);
	}
glFlush();
}

void main(int argc,char **argv)
{	
	
	glutInit(&argc,argv);
	//float ambient[]={1,1,1,1};
	//float light_pos[]={27,80,2,3};
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Asteroid");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKey);
	glutMouseFunc(mymouse);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glMaterialfv(GL_FRONT,GL_SPECULAR,ambient);
	//glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	myInit();
	glutMainLoop();
}