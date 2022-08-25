//*****************************************************
//
// Trabalho Final
// Gabriela Miranda, João Victor Lopes Leal e Ramon Barros Gomes
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

// Declaração de variáveis globais
GLfloat winY = 40, winX = 60, velocidade = 0.5, angulo = 0;
int vidas = 4, pontuacao = 0, bonus = 0;
int A = -1, B = -1, C = -1, dificuldade = 0, count = 0;
bool iniciado = false, partida = false;
bool AVerificado = false, BVerificado = false, CVerificado = false;
//Movimento lixo A
GLfloat xInicialA = 0.0f , yInicialA = 26.0f;
GLfloat translacaoXA = 0.0f, translacaoYA = 0.0f;
//Movimento lixo B
GLfloat xInicialB = -50.0f , yInicialB = 30.0f;
GLfloat translacaoXB = 0.0f, translacaoYB = 0.0f;
//Movimento lixo C
GLfloat xInicialC = 50.0f , yInicialC = 22.0f;
GLfloat translacaoXC = 0.0f, translacaoYC = 0.0f;

GLfloat cores[5][3] = {
	{0.9294f, 0.1567f, 0.1255f},   //plastico
	{0.1765f, 0.3020f, 0.6275f},   //papel
	{0.1657f, 0.5373f, 0.2706f},   //vidro
	{1.0000f, 0.8725f, 0.0039f},   //metal
	{0.5059f, 0.3490f, 0.1059f},   //organico
};

void contagemDeVidas(){
	   	glColor3f (0, 0, 0);
	   	glRasterPos2f (33.0, 38.0);
	   	char* string;
	   	switch(vidas){
	   		case 1:
	   			string = (char*) "Voce ainda tem 1  vida.";
	   			break;
	   		case 2:
	   			string = (char*) "Voce ainda tem 2  vidas.";
	   			break;
	   		case 3:
	   			string = (char*) "Voce ainda tem 3  vidas.";
	   			break;
	   		case 4:
	   			string = (char*) "Voce ainda tem 4  vidas.";
	   			break;
			   	
		}
		
        while (*string)
             glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, *string++);
}

//Lixeiras
void desenharLixeira(GLfloat translacaoX = 0.0f,GLfloat cor[3] = cores[2]){
	GLfloat descer = 40.0f;
	glColor3f (cor[0], cor[1], cor[2]);
	glTranslatef(translacaoX, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-8.0f, 0.0f-descer);
		glVertex2f(-8.0f, 16.0f-descer);
		glVertex2f(8.0f, 16.0f-descer);
		glVertex2f(8.0f, 0.0f-descer);
		
		glVertex2f(-9.0f, 16.0f-descer);
		glVertex2f(-9.0f, 24.0f-descer);
		glVertex2f(9.0f, 24.0f-descer);
		glVertex2f(9.0f, 16.0f-descer);
	glEnd ();
	glLoadIdentity();
}
//Desenha todas as lixeiras
void DesenhaLixeiras (void){
	desenharLixeira(0.0f,cores[0]);
	desenharLixeira(25.0f,cores[1]);
	desenharLixeira(50.0f,cores[2]);
	desenharLixeira(-25.0f,cores[3]);
	desenharLixeira(-50.0f,cores[4]);
	glBegin(GL_QUADS);
		glColor3f (0.4059f, 0.2490f, 0.0059f);
		glVertex2f(-winX, -winY);
		glVertex2f(winX, -winY);
		glColor3f (0.0f, 0.8f, 0.0f);
		glVertex2f(winX, -winY+6);
		glVertex2f(-winX, -winY+6);
	glEnd ();
}

//desenho de cada tipo de lixo
void plastico(GLfloat cor[3] = cores[2]){
	glColor3f (cor[0], cor[1], cor[2]);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(-1.0f, 0.5f);
		glVertex2f(-1.0f, 2.0f);
		glVertex2f(-0.5f, 2.5f);
		glVertex2f(-0.5f, 3.0f);
		glVertex2f(0.5f, 3.0f);
		glVertex2f(0.5f, 2.5f);
		glVertex2f(1.0f, 2.0f);
		glVertex2f(1.0f, 0.5f);
		glVertex2f(0.5f, 0.0f);
	glEnd ();
	glLoadIdentity();
}

void papel(GLfloat cor[3] = cores[2]){
	glColor3f (cor[0], cor[1], cor[2]);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
		glVertex2f(0.7f, 0.4f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(0.3f, 1.7f);
		glVertex2f(-1.0f, 1.0f);
		glVertex2f(-2.0f, 2.0f);
		glVertex2f(1.0f, 3.0f);
		glVertex2f(-1.0f, 2.0f);
		glVertex2f(-1.0f, 3.0f);
		glVertex2f(1.5f, 0.0f);
		glVertex2f(-0.6f, 0.6f);
		glVertex2f(-0.4f, 3.7f);
		glVertex2f(1.7f, 0.5f);
		glVertex2f(2.0f, 1.3f);
	glEnd ();
	glLoadIdentity();
}

void vidro(GLfloat cor[3] = cores[2]){
	glColor3f (cor[0], cor[1], cor[2]);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
		glVertex2f(-0.2f, 0.5f);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.2f, 0.5f);
		glVertex2f(0.2f, 2.0f);
		glVertex2f(0.467f, 2.34f);
		glVertex2f(0.734f, 2.67f);
		glVertex2f(1.0f, 3.0f);
		glVertex2f(-1.0f, 3.0f);
		glVertex2f(-0.734f, 2.67f);
		glVertex2f(-0.467f, 2.34f);
		glVertex2f(-0.2f, 2.0f);
	glEnd ();
	glLoadIdentity();
}

void metal(GLfloat cor[3] = cores[2]){
	glColor3f (cor[0], cor[1], cor[2]);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(-1.0f, 0.2f);
		glVertex2f(-1.0f, 2.6f);
		glVertex2f(-0.5f, 2.8f);
		glVertex2f(0.5f, 2.8f);
		glVertex2f(1.0f, 2.6f);
		glVertex2f(1.0f, 0.2f);
		glVertex2f(0.5f, 0.0f);
	glEnd ();
	glLoadIdentity();
}

void organico(GLfloat cor[3] = cores[2]){
	glColor3f (cor[0], cor[1], cor[2]);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
		for(int i = 0; i < 100; i++) { 
			angulo = i * 2 * 3.14 / 100; 
			glVertex2f(cos(angulo),sin(angulo)); 
		}
	glEnd ();
	glLoadIdentity();
}
//Faz o desenho do lixo
void desenharLixo(int lixo){
	glScalef(2.0f, 1.5f,0.0f);
	switch(lixo){
		case 0:
			plastico(cores[lixo]);
			break;
		case 1:
			papel(cores[lixo]);
			break;
		case 2:
			vidro(cores[lixo]);
			break;
		case 3:
			metal(cores[lixo]);
			break;
		case 4:
			organico(cores[lixo]);
			break;
	}
	glLoadIdentity();
}
//Sorteio de tipo de lixo
void escolherLixo(){
	A = rand()%5;
	if(dificuldade>=1) B = rand()%5;
	if(dificuldade==2) C = rand()%5;
	partida = true;
}
//Restaura a posição de cada lixo quando se inicia uma nova rodada
void posicaoInical(){
	int x1, x2, x3;
	translacaoXA = translacaoYA = 0.0f;
	translacaoXB = translacaoYB = 0.0f;
	translacaoXC = translacaoYC = 0.0f;
	x1 = rand()%120;
	if(B!=-1){
		do{
			x2 = rand()%120;
		}while(x2==x1);
	}
	if(C!=-1){
		do{
			x3 = rand()%120;
		}while(x3==x2||x3==x1);
	}
	
	if(x1<=60){
		x1 = (x1%60)*(-1);
		xInicialA = x1;
	}else{
		xInicialA = (x1%60);
	}
	if(x2<=60){
		x2 = (x2%60)*(-1);
		xInicialB = x2;
	}else{
		xInicialB = (x2%60);
	}
	if(x3<=60){
		x3 = (x3%60)*(-1);
		xInicialC = x3;
	}else{
		xInicialC = (x3%60);
	}
	
	
	
}
//inicai o jogo
void ConfiguraMouse (int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ // Alterar cor do fundo
		iniciado = true;
	}
    glutPostRedisplay();
}

void mostrarPontuacao(){
	int i = 0;
	glLineWidth(2);
	std::string s = "Pontuacao: ";
	s += ((pontuacao / 100000) % 10) + '0';
	s += ((pontuacao / 10000) % 10) + '0';
	s += ((pontuacao / 1000) % 10) + '0';
    s += ((pontuacao / 100) % 10) + '0';
    s += ((pontuacao / 10) % 10) + '0';
    s += (pontuacao % 10) + '0';   
	s += '\0';

	glColor3f(0.0f,0.0f,0.0f);
	glScalef(0.02f, 0.02f,0.0f);
	glTranslatef(-2950.0f, 1850.0f, 0.0f);
	while (s[i] != '\0'){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i++]);
	}
	
	glLoadIdentity();
}

void ComoJogar(){
		glColor3f(0.0f,0.0f,0.0f);
			GLfloat x = -58, y = 20;     
        	char* instruction = (char*) "Como jogar";
        	char* i1 = (char*) "1. A ideia é jogar o lixo na sua lixeira correspondente;";
        	char* i2 = (char*) "2. O jogo possui 3 niveis de dificuldade, cada dificuldade aumeta o";
        	char* i2_2 = (char*) "numero de lixos caindo";
        	char* i3 = (char*) "3. Os conjuntos de teclas direita e esquerda, A e D ou J e L"; 
			char* i3_2 = (char*) "direcionam cada lixo para lixeira que deseja acertar.";
        	char* i4 = (char*) "4. A velocidade que o lixo desce em direcao a lixeira aumenta com";
			char* i4_2 = (char*) "cada rodada";
        	char* i5 = (char*) "5. A quantidade de lixos para acertar na lixeira também variam com o";
			char* i5_2 = (char*) "nível de dificuldade.";
        	glRasterPos2f(x, y+13); 
        	while (*instruction != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *instruction++);
            }
            glRasterPos2f(x, y+9);
            while (*i1 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i1++);
            }
            glRasterPos2f(x, y+ 6);
            while (*i2 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i2++);
        	}
            glRasterPos2f(x, y+ 4);
            while (*i2_2 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i2_2++);
            }
            glRasterPos2f(x, y+1);
            while (*i3 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i3++);
            }
            glRasterPos2f(x, y-1);
            while (*i3_2 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i3_2++);
            }
            glRasterPos2f(x, y-4);
            while (*i4 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i4++);
            }
            glRasterPos2f(x, y-6);
            while (*i4_2 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i4_2++);
            }
            glRasterPos2f(x, y-9);
            while (*i5 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i5++);
            }
            glRasterPos2f(x, y-11);
            while (*i5_2 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i5_2++);
            }
            glRasterPos2f(x, y-23);
            char* i6 = (char*) "*TOQUE NA TELA PARA INICIAR";
            while (*i6 != '\0'){ glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i6++);
            }
}
//queda dos lixos
void descimento(){
	translacaoYA -= velocidade;
	translacaoYB -= velocidade;
	translacaoYC -= velocidade;
}
//O que aparece na tela
void Desenha(){
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);
	
	if(!iniciado){
		ComoJogar();
		glLoadIdentity();
		velocidade = 0.5;
		pontuacao = bonus = 0;
		vidas = 4;
		escolherLixo();
		posicaoInical();
	}else{
		if(!partida) escolherLixo();
		
		glTranslatef (xInicialA+translacaoXA,yInicialA+translacaoYA , 0.0f);
		desenharLixo(A);
		
		if(dificuldade>=1) {
			glTranslatef (xInicialB+translacaoXB,yInicialB+translacaoYB , 0.0f);
			desenharLixo(B);
		}
		if(dificuldade==2){
			glTranslatef (xInicialC+translacaoXC,yInicialC+translacaoYC , 0.0f);
			desenharLixo(C);	
		}
	}
	  
	glLoadIdentity();
	mostrarPontuacao();
	contagemDeVidas();
	DesenhaLixeiras();

	glFlush();
}

void AlteraTamanhoJanela(GLsizei width, GLsizei height){
	if(height != 0 && width != 0) {
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(width <= height) {
			gluOrtho2D (-60.0f, 60.0f, -40.0f * (height / width), 40.0f * (height / width));
			winX = 60.0f;
			winY = 40.0f * (height / width);
		} else {
			gluOrtho2D (-60.0f * (width / height), 60.0f  * (width / height), -40.0f , 40.0f);
			winX = 60.0f * (width / height);
			winY = 40.0f;	
		}	
	}
}
//Gerencia de novas rodadas 
void novaRodada(){
	if(count==dificuldade+1){
		posicaoInical();
		AVerificado = BVerificado = CVerificado = partida = false;
		count = 0;
		if(velocidade<23){
			velocidade += 0.1;
		}
	}
}

void AddPontuacao(){
	pontuacao += 8+bonus;
	bonus += 8;
	count++;
	novaRodada();
}

void PerdeVida(){
	vidas--;
	bonus = 0;
	if(vidas==0){
		exit(0);
	}
	count++;
	novaRodada();
}

//identificação de choque com cada lixeira	
bool entrarNaLixeira0(GLfloat x, GLfloat y){
	if((x>=-9)&&(x<=9)&&(y<=-14)){	
			return true;
	}
	return false;
}
bool entrarNaLixeira1(GLfloat x, GLfloat y){
	if((x>=16)&&(x<=34)&&(y<=-14)){	
			return true;
	}
	return false;
}
bool entrarNaLixeira2(GLfloat x, GLfloat y){
	if((x>=41)&&(x<=59)&&(y<=-14)){	
			return true;
	}
	return false;
}
bool entrarNaLixeira3(GLfloat x, GLfloat y){
	if((x>=-34)&&(x<=-16)&&(y<=-14)){	
			return true;
	}
	return false;
}
bool entrarNaLixeira4(GLfloat x, GLfloat y){
	if((x>=-59)&&(x<=-41)&&(y<=-14)){	
			return true;
	}
	return false;
}
int Verificacao(int tipo, GLfloat x, GLfloat y){
	if(entrarNaLixeira0(x, y)){
		if(tipo==0){
			return 1;
		}else{
			return 0;
		}
	}
	if(entrarNaLixeira1(x, y)){
		if(tipo==1){
			return 1;
		}else{
			return 0;
		}
	}
	if(entrarNaLixeira2(x, y)){
		if(tipo==2){
			return 1;
		}else{
			return 0;
		}
	}
	if(entrarNaLixeira3(x, y)){
		if(tipo==3){
			return 1;
		}else{
			return 0;
		}
	}
	if(entrarNaLixeira4(x, y)){
		if(tipo==4){
			return 1;
		}else{
			return 0;
		}
	}
	return -1;
}

void VerificarSeCaiuNoLixo(){
	if(A>-1&&!AVerificado){
		int verificacaoA = Verificacao(A, xInicialA+translacaoXA+1, yInicialA+translacaoYA+1);
		if(verificacaoA == 1){
			AVerificado = true;
			AddPontuacao();
		}else if(verificacaoA==0||yInicialA+translacaoYA+1<=-15){
			AVerificado = true;
			PerdeVida();
		}
	}
	if(B>-1&&!BVerificado){
		int verificacaoB = Verificacao(B, xInicialB+translacaoXB+1, yInicialB+translacaoYB+1);
		//std::cout << "\n" << verificacaoB << "    " << xInicialB+translacaoXB+1 << "     " << yInicialB+translacaoYB+1;
		if(verificacaoB == 1){
			BVerificado = true;
			AddPontuacao();
		}else if(verificacaoB == 0||yInicialB+translacaoYB+1<=-15){
			BVerificado = true;
			PerdeVida();
	    }
	}
	if(C>-1&&!CVerificado){
		int verificacaoC = Verificacao(C, xInicialC+translacaoXC+1, yInicialC+translacaoYC+1);
		if(verificacaoC == 1){
			CVerificado = true;
			AddPontuacao();
		}else if(verificacaoC == 0||yInicialC+translacaoYC+1<=-15){
			CVerificado = true;
			PerdeVida();
		}
	}
}

void TeclasSpecial(int key, int x, int y){

	if(key == GLUT_KEY_HOME){
		A = B = C = -1;
		dificuldade = count = 0;
   		iniciado = partida = false;
	} 

	if(key == GLUT_KEY_LEFT){
		if(xInicialA+translacaoXA - 2 > -winX){
			translacaoXA -= 2;
			glutPostRedisplay(); 	
		} 
	}else if(key == GLUT_KEY_RIGHT){
		if(xInicialA+translacaoXA + 2 < winX){
			translacaoXA += 2;
			glutPostRedisplay(); 	
		} 
	}
	
	descimento();
	VerificarSeCaiuNoLixo();
}
 
void Teclado (unsigned char key, int x, int y){
	if (key == 27)
		exit(0);
		
	switch (key) {
            case 'a': 
            		if(xInicialB+translacaoXB - 2 > -winX){
						translacaoXB -= 2;
					} 
                    break;
            case 'd': 
            		if(xInicialB+translacaoXB + 2 < winX ){
						translacaoXB += 2;
					} 
                    break;
            case 'j': 
            		if(xInicialC+translacaoXC - 2 > -winX ){
						translacaoXC -= 2;
					} 
                    break;
            case 'l': 
            		if(xInicialC+translacaoXC + 2 < winX ){
						translacaoXC += 2;
					} 
                    break;
    }
	
	if(dificuldade>=1) descimento();
	
	if(dificuldade>=1) VerificarSeCaiuNoLixo();
	
	glutPostRedisplay();
}
        
void MenuNivel(int op) {
	switch(op) {
            case 0:
            		dificuldade = 0;
                    break;
            case 1:
            		dificuldade = 1;
                    break;
            case 2:
            		dificuldade = 2;
                    break;
    }
    iniciado=false;
    glutPostRedisplay();
}

void MenuPrincipal(int option){
	if(option == 3)
		exit(1);
}

void Menu(){
	int menuMain, subMenu;
	
	subMenu = glutCreateMenu(MenuNivel);
	glutAddMenuEntry("Nivel 1", 0);
	glutAddMenuEntry("Nivel 2", 1);
	glutAddMenuEntry("Nivel 3", 2);
	
	
	menuMain = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Nivel de dificuldade", subMenu);
	glutAddSubMenu("Sair", 3);
}
		   
void Inicializa (void){   
	// Define a cor de fundo da janela de visualização
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
}

// Programa Principal 
int main(int argc, char *argv[]){
	
	glutInit( & argc, argv );//Obs.: Professor, tivemos que colocar esta linha por que a nossa instalação do GLUT foi seguindo 
	//uma video aula, e foi diferente da mostrada em sala, se precissar pode comentar isso
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(600,5);    
	glutInitWindowSize (700,900); 
	glutCreateWindow("Trash Right");
	glutDisplayFunc(Desenha);  
	glutReshapeFunc(AlteraTamanhoJanela);    
	glutSpecialFunc(TeclasSpecial);
	glutKeyboardFunc(Teclado);
	glutMouseFunc(ConfiguraMouse); 
	Menu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	Inicializa(); 
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
