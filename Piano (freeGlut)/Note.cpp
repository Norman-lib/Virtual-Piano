#include "Note.h"

using namespace std;

Note::Note(char a) {
    couleur = 1.0f;
    c = a;
    MusicOn = false;
};

typedef struct {
    float x;
    float y;
    float z;
} vertex;

// Création des sommets du rectangle n1
vertex cube[4] = {
   {0.0f,0.0f, 0.0f},
   {0.0f, 2.0f, 0.0f},
   { 0.485f, 2.0f, 0.0f},
   { 0.485f,0.0f, 0.0f},
};

vertex cube1[4] = {
   {0.375f,1.0f, 0.0f},
   {0.375f, 2.0f,0.0f},
   { 0.625f, 2.0f, 0.0f},
   { 0.625f,1.0f, 0.0f},
};

void vBitmapOutput(int x, int y, char* string, void* font)
{
    glRasterPos2f(x, y); // Positionne le premier caractère de la chaîne
    glutBitmapCharacter(font, string[0]); // Affiche chaque caractère de la chaîne
}

GLvoid Note::drawNote(float couleur) {

    if (couleur == 1.0f) {

        glColor4f(R, G, B, 0.5f);
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; i++) {
            glVertex3f(cube[i].x, cube[i].y, cube[i].z);
        }
        glEnd();


    }
    else if (couleur == 0.0f) {
        glColor4f(R, G, B, 0.5f);

        glBegin(GL_QUADS);
        for (int i = 0; i < 4; i++) {
            glVertex3f(cube1[i].x, cube1[i].y, cube1[i].z);
        }

        glEnd();
    }
};

vector<vector<float>> cube3{
    {0.0f,0.0f, 0.0f},
   {0.0f, 2.0f, 0.0f},
   { 0.485f, 2.0f, 0.0f},
   { 0.485f,0.0f, 0.0f},
    {0.0f, 0.0f , -1.0f} ,
    {0.0f, 2.0f , -1.0f} ,
    {0.485f, 2.0f, -1.0f} ,
    {0.485f , 0.0f, -1.0f} };

vector<vector<float>> cube31{  /// à voir !!! 
    {0.0f, 0.0f, -0.1f}, // 1 entre dans le z
   {0.0f, 2.0f, 0.0f}, // 2 fixe
   { 0.485f, 2.0f, 0.0f},  //3 fixe entre dans le z 
   { 0.485f,0.0f, 0.0f - 0.1f}, //4
    {0.0f, 0.0f , -1.0f }, //1'
    {0.0f, 2.0f , -1.0f} , // 2'
    {0.485f, 2.0f, -1.0f} , //3' 
    {0.485f , 0.0f, -1.0f } }; //4'

vector<vector<float>>  cube4{
   {0.375f,1.0f, 0.0f},
   {0.375f, 2.0f,0.0f},
   { 0.625f, 2.0f, 0.0f},
   { 0.625f,1.0f, 0.0f},
    {0.375f,1.0f, -0.5f}, // 1'
   {0.375f, 2.0f,-0.5f},
   { 0.625f, 2.0f, -0.5f},
   { 0.625f,1.0f, -0.5f},
};

vector<vector<float>>  cube41{
   {0.375f,1.0f , -0.1f},
   {0.375f, 2.0f,0.0f},
   { 0.625f, 2.0f , 0.0f},
   { 0.625f,1.0f  , 0.0f - 0.1f},
    {0.375f,1.0f, -0.5f}, // 1'
   {0.375f, 2.0f,-0.5f},
   { 0.625f, 2.0f, -0.5f},
   { 0.625f,1.0f, -0.5f - 0.1f},
};

float distance2;

int face[6][4] = {
   {0,1,2,3},
   {3,2,6,7},
   {4,5,6,7},
   {0,1,5,4},
   {1,5,6,2},
   {0,4,7,3}
};

GLvoid Note::drawNote3(float couleur, bool musicOn) {
    // 3D 
    distance2 = 0.1f;
    if (!musicOn) // le piano est au repos
    {
        if (couleur == 1.0f) { // les blanches 
            glColor4f(R, G, B, 1.0f);
            for (int i = 0; i < 6; i++) {
                glColor4f(R, G, B, 1.0f);
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++) {
                    glVertex3f(cube3[face[i][j]][0], cube3[face[i][j]][1], cube3[face[i][j]][2]);
                }
                glEnd();

            }
            for (int i = 0; i < 6; i++) {
                glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                glBegin(GL_LINES);
                glLineWidth(10);
                for (int j = 0; j < 2; j++) {
                    glVertex3f(cube3[face[i][j]][0], cube3[face[i][j]][1], cube3[face[i][j]][2]);
                }
                glEnd();

            }

        }
        else { // les noires
            glBegin(GL_QUADS);
            glColor4f(R, G, B, 1.0f);
            for (int i = 0; i < 6; i++) {
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++) {
                    glVertex3f(cube4[face[i][j]][0], cube4[face[i][j]][1], cube4[face[i][j]][2]);
                }
                glEnd();
            }
            glEnd();
        }
    }
    else // les notes sont actives 
    {
        distance2 = -0.1f;

        if (couleur == 1.0f) {
            glBegin(GL_QUADS);
            glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
            for (int i = 0; i < 6; i++) {
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++) {
                    glVertex3f(cube31[face[i][j]][0], cube31[face[i][j]][1], cube31[face[i][j]][2]);
                }
                glEnd();
            }
            glEnd();
        }
        else {
            glBegin(GL_QUADS);
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

            for (int i = 0; i < 6; i++) {
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++) {
                    glVertex3f(cube41[face[i][j]][0], cube41[face[i][j]][1], cube41[face[i][j]][2]);
                }
                glEnd();
            }
            glEnd();
        }

    }
};

void Note::setCouleur(float a) {
    couleur = a;

};

void Note::setMusic(string m) {
    music = m;
};

float Note::getCouleur() {
    return (couleur);
};




void Note::drawChar(float couleur) {
    if (couleur == 1.0f) {
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.20f, 0.25f, distance2);
        char* ptr = &c;
        vBitmapOutput(0, 0, ptr, GLUT_BITMAP_HELVETICA_18);
        glPopMatrix();

    }
    else if (couleur == 0.0f) {
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.45f, 1.1f, distance2);
        char* ptr = &c;
        vBitmapOutput(0, 0, ptr, GLUT_BITMAP_HELVETICA_18);
        glPopMatrix();
    }
};

char Note::getChar() {
    return c;
};

void Note::playMusic() {
    //convertir un string to cost char s
    const char* s = music.c_str();
    ISoundEngine* SoundEngine = createIrrKlangDevice();
    //const char* c= &music;
    SoundEngine->play2D(s, false);

    // coloration de l'espace de note 

};
