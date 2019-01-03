/*


  Simple Demo for GLSL

  www.lighthouse3d.com

*/
#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glut.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

#ifndef GLSHADER_H
#define GLSHADER_H

#include "GL/glew.h"

GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif

using namespace std;

#pragma comment(lib, "glew32.lib")

GLuint v,f,f2,p;
float lpos[4] = {1,0.5,1,0};

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);


}
float a = 0;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glRotatef(a,0,1,1);
	glutSolidSphere(1.5,100,100);

	a+=0.1;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

const GLchar* readFromFile(const GLchar* pathToFile)
{
	string content;
	std::ifstream fileStream(pathToFile, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	std::cout << "'" << content << "'" << std::endl;
	return content.c_str();
}

void setShaders() {

	const char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);
	//TCHAR full_path[MAX_PATH];

	//GetFullPathName("minimal.frag", MAX_PATH, full_path, NULL);
	//cout << full_path;
	//vs = "void main()"
	//	"{"
	//	"gl_Position = ftransform();"
	//	"}";

	//fs = readFromFile("C:\\Users\\Smkgames\\source\\repos\\OpenGLPractice\\Project1\\minimal.frag");

	GLuint program = LoadShader("C:\\Users\\Smkgames\\source\\repos\\OpenGLPractice\\Project1\\shader.vert", "C:\\Users\\Smkgames\\source\\repos\\OpenGLPractice\\Project1\\shader.frag");
	glUseProgram(program);

	//const char * vv = vs;
	//const char * ff = fs;

	//glShaderSource(v, 1, &vv,NULL);
	//glShaderSource(f, 1, &ff,NULL);

	////free(vs);free(fs);

	//glCompileShader(v);
	//glCompileShader(f);

	//printShaderInfoLog(v);
	//printShaderInfoLog(f);
	//printShaderInfoLog(f2);

	//p = glCreateProgram();
	//glAttachShader(p,v);
	//glAttachShader(p,f);

	//glLinkProgram(p);
	//printProgramInfoLog(p);

	//glUseProgram(p);

}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("OpenGL");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_CULL_FACE);

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	setShaders();

	glutMainLoop();

	return 0;
}
