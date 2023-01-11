#pragma once
#include <vector>
#include <iostream>
#include <windows.h>
#include <string>
#include <irrKlang.h>

using namespace irrklang;

//#include <cairo.h>

// Fichiers d'en-têtes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL\freeglut.h>
//#include <GL\glew.h>
#endif

using namespace std;




class Note {
private:
	float couleur;
	float R, G, B, id;
	char c; // le caractere de la note
	string music;
	bool MusicOn;
	bool isPressed = false; 
	// file music 
public:
	//constrcuteurs 
	Note(char);
	// setters
	void setCouleur(float);
	void setMusic(string);
	void setMusicOn() { MusicOn = true; };
	void setR(float rouge) { R = rouge; }
	void setG(float green) { G = green; }
	void setB(float bleu) { B = bleu; }
	void setId(float ident) { id = ident; };
	void setIsPressed(bool x) { isPressed = x; };
	//getters
	float getCouleur();
	float getId() { return id; };
	char getChar();
	bool getIsPressed() { return isPressed; };
	//methodes
	GLvoid drawNote(float , bool);
	GLvoid drawNote3(float , bool);
	void playMusic();
	void drawChar(float);
};