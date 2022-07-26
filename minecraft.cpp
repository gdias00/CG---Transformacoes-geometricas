//*******
// ObjetoComTransformacoesHierarquicas.cpp
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha e permite interagir com um objeto que é 
// modelado através da utilização de transformações
// hierárquicas.
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
// Alterações: Gabriel Dias Oliveira
// Disciplina : Computação Gráfica - UNIVASF
// Base de criação : Jogo "Minecraft" 
//EXTRAS: 
// ver regra do circulo para talvez seg*2  {inverter de 180 para 360} 
// -> Tx: colocar para 20+  é a posição inicial do boneco 1 para a direita 
// mudar linha  para if ( tx < -win/16 ) 	tx = -win/16; caso queira limitar o boneco 1 para a metade 
//*******

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0; //posição inicial do boneco 
GLfloat ang1 = 0, ang2 = -90;
GLfloat win = 25;

//Função para desenhar bandeira
void Bandeira()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);          //fundo branco
		glVertex2f(10,20);
		glVertex2f(25,20);
		glVertex2f(25,10);
		glVertex2f(10,10);
	glEnd();
	
	glColor3f(0.04f, 0.22f, 0.718f);
	glBegin(GL_POLYGON);         //linha azul cima
		glVertex2f(10,19);
		glVertex2f(25,19);
		glVertex2f(25,17);
		glVertex2f(10,17);
	glEnd();
	
	glBegin(GL_POLYGON);         //linha azul baixo
		glVertex2f(10,13);
		glVertex2f(25,13);
		glVertex2f(25,11);
		glVertex2f(10,11);
	glEnd(); 
	
	glLineWidth(3.5);
	glBegin(GL_LINE_LOOP);         //triangulo cima
		glVertex2f(15,14);
		glVertex2f(17.5,16.75);
		glVertex2f(20,14);
	glEnd();
	
	glBegin(GL_LINE_LOOP);         //triangulo cima
		glVertex2f(15,16);
		glVertex2f(20,16);
		glVertex2f(17.5,13.25);
	glEnd();
}
//Função para desenhar circulo
void drawCircleFill(float cx, float cy, float r, int num_segments)
{
    float theta = 3.1415926 * 2 / float(num_segments);
    float tangetial_factor = tanf(theta);// calcula fator tangencial
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    float radial_factor = cosf(theta);//calcula fator radial 
    float x = r;//iniciando angulo em 0 
    float y = 0;

    glBegin(GL_POLYGON);
    
    if (num_segments = 180) num_segments = num_segments/2; 
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//vertex de saída

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

// Função para desenhar um "braço" do objeto
void DesenhaSuperior()
{
	glBegin(GL_POLYGON);
		glVertex2f(1.0,2.6);
		glVertex2f(1.0,-2.8);
		glVertex2f(-1.0,-2.8);
		glVertex2f(-1.0,2.6);
	glEnd();
}

// Função para desenhar a base do objeto {short}          
void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_POLYGON);
		glVertex2f(1.8,0);
		glVertex2f(1.8,-3.5);
		glVertex2f(1.0,-3.5);
		glVertex2f(1.0,-3);
		glVertex2f(-1.0,-3);
		glVertex2f(-1.0,-3.5);
		glVertex2f(-1.8,-3.5);
		glVertex2f(-1.8,0);
	glEnd();
}
           
// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha o "chão"
	glColor3f(0.004f,0.364f,0.031f);
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win,-7.9);
		glVertex2f(win,-7.9);
	glEnd();
	
	//desenha o sol
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircleFill(-20,20,3,90);
	
	//desenha a bandeira de Israel
	Bandeira();
                               
	// Desenha um objeto modelado com transformações hierárquicas
	glPushMatrix();                   
	                
	glTranslatef(tx,0.0f,0.0f); // poe no meio
    
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);          //cinza
    drawCircleFill(-3.5, -7, 1.2, -180); // pé esquerdo
    drawCircleFill(3.5, -7, 1.2, -180); //pé direito
	glScalef(2.5f,2.0f,1.0f);
	glColor3f(0.31f,0.25f,0.75f);       //azul escuro
	DesenhaBase();                      //short
	glScalef(1.4f,1.4f,1.0f);
    
	glPopMatrix();
                    
	glTranslatef(0.0f,1.0f,0.0f);
	glRotatef(ang1,0.0f,0.0f,1.0f);    
	glScalef(6.0f,1.4f,1.0f);
	glColor3f(0.0f,0.69f,0.725f);
	DesenhaSuperior();                 //tronco
     

    glScalef(0.3f,0.8f,1.0f);
	glColor3f(0.92f,0.725f,0.564f);// color cabeça
	drawCircleFill(0, 4, 3, 90);   //cabeça
	
	glColor3f(1.0f,1.0f,1.0f);
	drawCircleFill(-1,4.4,0.5,90);   //olho esquerdo
	drawCircleFill(1,4.4,0.5,90);   //olho direito 
	glColor3f(0.5f,0.725f,0.564f);
	drawCircleFill(-1,4.4,0.3,90);  //iris esquerda
	drawCircleFill(1,4.4,0.3,90);   //iris direita
	
	glColor3f(0.4f,0.4f,0.4f);      
	drawCircleFill(0,2.4,1.0,-180); //boca
	glColor3f(0.094f,0.141f,0.173f);
	drawCircleFill(0,6.4,1.0,180);     //kipá  
	
	
	glScalef(1.0f,0.7f,1.0f);
	glColor3f(0.92f,0.725f,0.564f);                        
	glTranslatef(-5.5f,1.0f,0.0f);
	glRotatef(ang2,0.0f,0.0f,1.0f);
    DesenhaSuperior();               //braço esquerdo 
		
	glTranslatef(0.0f,11.0f,0.0f);
	DesenhaSuperior();              //braço direito
	  
	glPopMatrix();    
   ;
	  
	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
	{ 
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}              
	else 
	{ 
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;           
	}             
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=2;
		if ( tx < -win )
			tx = -win; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=2;
		if ( tx > win )
			tx = win; 
	}     

	// Rotaciona tronco
	if(key == GLUT_KEY_HOME && ang1 >= -20)
		ang1-=5;
	if(key == GLUT_KEY_END && ang1 <= 20)
		ang1+=5;
              
	// Rotaciona item interno 
	if(key == GLUT_KEY_UP && ang2 >= -100)
		ang2-=5;
		//ang3-=5;
		
	if(key == GLUT_KEY_DOWN && ang2 <= -80)
		ang2+=5;
		//ang3+=5;              
                                                
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
           
// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como marrom
	glClearColor(0.36f, 0.21f, 0.14f, 1.0f);
    
	// Exibe mensagem que avisa como interagir
	printf("Projeto Computacao Grafica - Um garoto minecraft em Israel:");
	printf("\nCOMANDOS:");
	printf("\nSetas para esquerda e para direita movimentam o personagem ");
	printf("\n Home e End rotacionam o tronco");
	printf("\n Setas para cima e para baixo movem os braços");    
}

// Programa Principal 
int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);  //Define a posição inicial na tela, do canto superior esquerdo a janela   
	glutInitWindowSize(700,600);  //Define o tamanho inicial da janela GLUT que será criada
	glutCreateWindow("Gabriel Dias - Minecraft no mineverso - Israel Edition"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);    

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
