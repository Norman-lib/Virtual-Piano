#include "Note.h"
#include "vector3d.h"

#include <map>

// structure de données pour stocker les infos d'un vertex

// Souris
GLint oldX = 0;
GLint oldY = 0;
GLboolean boutonClick = false;

GLfloat position = 0;
GLfloat distance1 = 3;
GLfloat straffeSpeed = 0;
GLfloat upDownMove = 0;

Vector3D camPos;
Vector3D targetPos;
Vector3D forwardMove;
Vector3D at;
Vector3D rightMove;
Vector3D upWorld;
Vector3D forwardView;
Vector3D rightView;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;


//import des fichiers son .ogg

map<string, vector<float>> noteBlanches{
    {"piano\\white notes\\100.ogg", {1.0f,1.0f,1.0f}},
    {"piano\\white notes\\101.ogg", {1.0f,0.99f,1.0f}},
    {"piano\\white notes\\102.ogg",{1.0f,0.99f,0.99f}},
    {"piano\\white notes\\103.ogg",{1.0f,1.0f,0.99f} },
    {"piano\\white notes\\104.ogg", { 0.99f,1.0f,1.0f }},
    {"piano\\white notes\\105.ogg", { 0.99f,0.99f,1.0f }},
    {"piano\\white notes\\106.ogg", { 0.99f,0.99f,0.99f }},
    {"piano\\white notes\\107.ogg", { 1.0f,1.0f,0.98f }},
    {"piano\\white notes\\108.ogg", { 1.0f,0.98f,1.0f }},
    {"piano\\white notes\\109.ogg", { 0.98f,1.0f,1.0f }},
    {"piano\\white notes\\110.ogg", {0.98f,0.98f,1.0f }},
    {"piano\\white notes\\111.ogg", { 1.0f,0.98f,0.98f }},
    {"piano\\white notes\\112.ogg", { 0.98f,0.98f,0.98f }},
    {"piano\\white notes\\113.ogg", { 1.0f,1.0f,0.97f }},
};
vector<float> identifiantBlanc{ -111,-141,-441,-411,-114,-144,-444,-611,-161,-116,-166,-661,-666,-911 };

map<string, vector<float>> noteNoires{
    {"piano\\black notes\\100.ogg",{0.5f,0.5f,0.5f}},
    {"piano\\black notes\\101.ogg",{0.5f,0.49f,0.5f}},
    {"piano\\black notes\\102.ogg",{0.5f,0.5f,0.49f}},
    {"piano\\black notes\\103.ogg",{0.49f,0.5f,0.5f}},
    {"piano\\black notes\\104.ogg",{0.48f,0.5f,0.5f}},
    {"piano\\black notes\\105.ogg",{0.5f,0.48f,0.5f}},
    {"piano\\black notes\\106.ogg",{0.5f,0.5f,0.48f}},
    {"piano\\black notes\\107.ogg",{0.5f,0.49f,0.49f}},
    {"piano\\black notes\\108.ogg",{0.49f,0.49f,0.5f}},
    {"piano\\black notes\\109.ogg",{0.49f,0.49f,0.49f}},

};
vector<float> identifiantNoir{ -14208,-11678,11092,-13955,-13958,-11708,10792,13622,-11425 , 13875};
//les vecteurs de notes
vector<Note*> blanc;
vector<Note*> noir;

// vecteurs des keys 
const char* keyBlanc = "qsdfghjklmwxcv";
const char* keyNoir = "azertyuiop";

//un vecteur possedant les état enfoncé ou ralché des bouttons
vector<bool> isPressedBlanc(14, false);
vector<bool> isPressedNoir(10, false);

// Definition de la fonction d'affichage
// piano 3D


void cameraMovement(float dM, float dS) {
    // est-on en "fly" mode ou non ?
    // FPS mode
        camPos += dM * forwardMove;
        camPos += dS * rightMove;
        if (dS != 0) {
            targetPos = camPos;
        }
        if (dM != 0 ) {
            targetPos = camPos + forwardMove;
        }
    // Mettre a jour la cible

}


GLvoid affichage2() {

    cameraMovement(upDownMove, straffeSpeed);
   // cout << upDownMove << endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //animation
    glLoadIdentity();
    gluLookAt(camPos.getVx(), camPos.getVy(), camPos.getVz() + distance1, targetPos.getVx(), targetPos.getVx(), targetPos.getVx(), upWorld.getVx(), upWorld.getVy(), upWorld.getVz());
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-4.0f, 0.0f, 0.0f);

    auto it = noteBlanches.begin();
    for (int i = 0; i < 14; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.0f);
        vector<float> v(3, 1.0f);
        Note* n = new Note(keyBlanc[i]);
        n->setCouleur(1.0);
        vector<float> vec{ -4.0f + 1.0f * i ,0.0f };
        n->setMusic(it->first);
        n->setR(it->second[0]);  n->setG(it->second[1]); n->setB(it->second[2]);
        n->setId(identifiantBlanc[i]);
        n->drawNote3(n->getCouleur(), isPressedBlanc[i]);
        it++;
        n->drawChar(n->getCouleur());
        blanc.push_back(n);
        glPopMatrix();
    }

    glPopMatrix();

    auto itN = noteNoires.begin();

    // les noires 
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.2f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]); n->setG(itN->second[1]); n->setB(itN->second[2]);
        n->setId(identifiantNoir[i]);
        n->drawNote3(n->getCouleur(), isPressedNoir[i]);
        ++itN;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    for (int i = 3; i < 6; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.2f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 1]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 1]);
        n->drawNote3(n->getCouleur(), isPressedNoir[i - 1]);
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }
    for (int i = 7; i < 9; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.2f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 2]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 2]);
        n->drawNote3(n->getCouleur(), isPressedNoir[i - 2]);
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    for (int i = 10; i < 13; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.2f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 3]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 3]);
        n->drawNote3(n->getCouleur(), isPressedNoir[i - 3]);
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    glDisable(GL_DEPTH_TEST); 
    glFlush();
    glutSwapBuffers();

}

// piano 2D
GLvoid affichage2D() {

    cameraMovement(upDownMove, straffeSpeed);
    // cout << upDownMove << endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //animation
    glLoadIdentity();
    gluLookAt(camPos.getVx(), camPos.getVy(), camPos.getVz(), 0, 0, 0, upWorld.getVx(), upWorld.getVy(), upWorld.getVz());
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-4.0f, 0.0f, 0.0f);

    auto it = noteBlanches.begin();
    for (int i = 0; i < 14; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.0f);
        vector<float> v(3, 1.0f);
        Note* n = new Note(keyBlanc[i]);
        n->setCouleur(1.0);
        vector<float> vec{ -4.0f + 1.0f * i ,0.0f };
        n->setMusic(it->first);
        n->setR(it->second[0]);  n->setG(it->second[1]); n->setB(it->second[2]);
        n->setId(identifiantBlanc[i]);
        n->drawNote(n->getCouleur());
        it++;
        n->drawChar(n->getCouleur());
        blanc.push_back(n);
        glPopMatrix();
    }

    glPopMatrix();

    auto itN = noteNoires.begin();

    // les noires 
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.01f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]); n->setG(itN->second[1]); n->setB(itN->second[2]);
        n->setId(identifiantNoir[i]);
        n->drawNote(n->getCouleur());
        ++itN;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    for (int i = 3; i < 6; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.01f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 1]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 1]);
        n->drawNote(n->getCouleur());
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }
    for (int i = 7; i < 9; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.01f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 2]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 2]);
        n->drawNote(n->getCouleur());
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    for (int i = 10; i < 13; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.01f);
        vector<float> v(3, 0.0f);
        Note* n = new Note(keyNoir[i - 3]);
        n->setCouleur(0.0);
        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
        n->setMusic(itN->first);
        n->setR(itN->second[0]);
        n->setG(itN->second[1]);
        n->setB(itN->second[2]);
        n->setId(identifiantNoir[i - 3]);
        n->drawNote(n->getCouleur());
        itN++;
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }


    glFlush();
    glutSwapBuffers();

}
//GLvoid affichage() {
//    // Effacement du frame buffer + Z buffer
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    // ModelView
//    glMatrixMode(GL_MODELVIEW);
//    glTranslatef(-4.0f, 0.0f, 0.0f);
//    for (int i = 0; i < 14; i++) {
//        glPushMatrix();
//        glTranslatef(0.5f * i, 0.0f, 0.0f); 
//        vector<float> v(3,1.0f); 
//         Note *n = new Note(keyBlanc[i]);
//        n->setCouleur(1.0);
//        vector<float> vec{-4.0f+ 1.0f * i ,0.0f};
//        n->setMusic(noteBlanches[i]);
//        n->drawNote(n-> getCouleur());
//        n->drawChar(n->getCouleur());
//       
//        blanc.push_back(n); 
//        glPopMatrix(); 
//    }
//
//    glPopMatrix();
//      
//    for (int i = 0; i < 2; i++) {
//        glPushMatrix();
//        glTranslatef(0.5f * i, 0.0f, 0.0f);
//        vector<float> v(3, 0.0f);
//        Note* n = new Note(keyNoir[i]);
//        n->setCouleur(0.0);
//        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
//        n->setMusic(noteNoires[i]);
//        n->drawNote(n->getCouleur());
//        n->drawChar(n->getCouleur());
//        noir.push_back(n);
//        glPopMatrix();
//    }
//    for (int i = 3; i < 6; i++) {
//        glPushMatrix();
//        glTranslatef(0.5f * i, 0.0f, 0.0f);
//        vector<float> v(3, 0.0f);
//        Note* n = new Note(keyNoir[i-1]);
//        n->setCouleur(0.0);
//        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
//        n->setEspace(vec, n->getCouleur());
//        n->setMusic(noteNoires[i-1]);
//        n->drawNote(n->getCouleur());
//        n->drawChar(n->getCouleur());
//        noir.push_back(n);
//        glPopMatrix();
//    }
//    for (int i = 7; i < 9; i++) {
//        glPushMatrix();
//        glTranslatef(0.5f * i, 0.0f, 0.0f);
//        vector<float> v(3, 0.0f);
//        Note* n = new Note(keyNoir[i-2]);
//        n->setCouleur(0.0);
//        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
//        n->setMusic(noteNoires[i-2]);
//        n->drawNote(n->getCouleur());
//        n->drawChar(n->getCouleur());
//        noir.push_back(n);
//        glPopMatrix();
//    }
//    for (int i = 10; i < 13; i++) {
//        glPushMatrix();
//        glTranslatef(0.5f * i, 0.0f, 0.0f);
//        vector<float> v(3, 0.0f);
//        Note* n = new Note(keyNoir[i-3]);
//        n->setCouleur(0.0);
//        vector<float> vec{ -4.0f + 0.5f * i ,1.0f };
//        n->setMusic(noteNoires[i-3]);
//        n->drawNote(n->getCouleur());
//        n->drawChar(n->getCouleur());
//        noir.push_back(n);
//        glPopMatrix();
//    }
//
//    
//    glFlush();
//    glutSwapBuffers();
//}

GLvoid clavierUp(unsigned char touche, int x, int y) {
    //Blancs
    for (int i = 0; i < 14; i++) {
        if (touche == keyBlanc[i]) {
            isPressedBlanc[i] = false;
            break;
        };
    };
    // Noirs
    for (int j = 0; j < 10; j++) {
        if (touche == keyNoir[j]) {
            isPressedNoir[j] = false;
            break;
        };
    };
    glutPostRedisplay();
};

// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) { // selon input 
    // Blanc
    for (int i = 0; i < 14; i++) {
        if (touche == keyBlanc[i]) {
            if (!isPressedBlanc[i]) {
                blanc[i]->setMusicOn();
                blanc[i]->playMusic();
                isPressedBlanc[i] = true;
            };
            break;
        };
    };
    // Noir
    for (int i = 0; i < 10; i++) {
        if (touche == keyNoir[i]) {
            if (!isPressedNoir[i]) {
                noir[i]->setMusicOn();
                noir[i]->playMusic();
                isPressedNoir[i] = true;    
            };
            break;
        };
    };
    switch (touche) {
    case '+':
        //activer le test du tampon de profondeur
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case '-':
        //desactiver le test du tampon de profondeur
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    }
    glutPostRedisplay();
}


map<char, int> findid(float f) {
    // liste de banc 
    for (int i = 0; i < blanc.size(); i++) {
        if (blanc[i]->getId() == f)
        {
            blanc[i]->setMusicOn();
            blanc[i]->playMusic();
            isPressedBlanc[i] = true;
            glutPostRedisplay();
            return (map<char, int>{ {'b', i}});
        }
    }
    for (int i = 0; i < noir.size(); i++) {
        if (noir[i]->getId() == f)
        {
            noir[i]->setMusicOn();
            noir[i]->playMusic();
            isPressedNoir[i] = true;
            glutPostRedisplay();
            return (map<char, int>{ {'n', i}});
        }
    }
    return map<char, int>{ {'a', 0}};


}


float getPixelColor(GLint x, GLint y) {
    glFlush();
    glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GLbyte data[4];
    glReadBuffer(GL_FRONT);
    glReadPixels(x, windowH - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    float pickedID = data[0] + data[1] * 10 + data[2] * 100;
    cout << "le id est " << pickedID << endl;
    return pickedID;
}
float A;
map<char, int> Dict{ {'a',1} };

GLvoid souris3(int boutton, int etat, int x, int y)
{
    if (boutton == GLUT_LEFT_BUTTON)
    {
        switch (etat) {
        case (GLUT_DOWN):
            if (getPixelColor(x, y) != 102) {

                A = getPixelColor(x, y);
                Note* ptr;
                Dict = findid(A);
            }
            
            boutonClick = true;
            break;
        case GLUT_UP:
            if (Dict.begin()->first == 'b') { isPressedBlanc[Dict.begin()->second] = false; }
            else if (Dict.begin()->first == 'n') { isPressedNoir[Dict.begin()->second] = false; }
           
            boutonClick = false;
            break;
        default:
            break;

        }
    }



    glutPostRedisplay();
}

void catchKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        straffeSpeed = 0.001f;
        break;
    case GLUT_KEY_RIGHT:
        straffeSpeed = -0.001f;
        break;
    case GLUT_KEY_UP:
        upDownMove = 0.001f;
        break;
    case GLUT_KEY_DOWN:
        upDownMove = -0.001f;
        break;
    }
   // cout << position << endl;
}

void catchKeyDown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        straffeSpeed = 0;
        break;
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        upDownMove = 0;
        break;
    }
}


// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;
    // eviter une division par 0
    if (windowH == 0)
        windowH = 1;
    float ratio = (float)windowW / (float)windowH;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glViewport(0, 0, windowW, windowH);
    gluPerspective(focale, w * 1.0 / h, near1, far1);
    // gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
        distance1 -= 0.1f;
    }
    else
    {
        distance1 += 0.1f;
        distance1 += 0.1f;
    }

    return;
}


void main(int argc, char* argv[])
{
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
     // Position initiale de la fenetre GLUT
    glutInitWindowPosition(200, 200);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("PIANO3D");
    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.4f, 0.0f, 0.0f, 0.0f);
    // Définition des fonctions de callbacks
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUp);
    glutMouseFunc(souris3);
    glutSpecialFunc(catchKey);
    glutSpecialUpFunc(catchKeyDown);
    glutMouseWheelFunc(mouseWheel);
    glutReshapeFunc(redimensionner);
    camPos = Vector3D(0, -1, 3);
    // on initialise les vecteurs 'view'
    forwardView = Vector3D(0, 0, 0);
    upWorld = Vector3D(0, 1, 0);
    rightView = Vector3D(1, 0, 0);
    // Pour le FPS mode
    forwardMove = Vector3D(0, 0, -1);
    at = Vector3D(0,1,0);
    rightMove = Vector3D(1, 0, 0);
    // on initialise la cible a partir de la camera et du vecteur vision
    targetPos = camPos + forwardView;

    glutDisplayFunc(affichage2);
   // glutIdleFunc(affichage2);
    glClearColor(0.4f, 0.0f, 0.0f, 0.0f);
     

    // pour voir un piano 2D 
    glutCreateWindow("PIANO2D");
    glClearColor(0.4f, 0.0f, 0.0f, 0.0f);
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUp);
    glutMouseFunc(souris3);
    glutSpecialFunc(catchKey);
    glutSpecialUpFunc(catchKeyDown);
    glutMouseWheelFunc(mouseWheel);
    glutReshapeFunc(redimensionner);
    camPos = Vector3D(0, -1, 3);
    // on initialise les vecteurs 'view'
    forwardView = Vector3D(0, 0, 0);
    upWorld = Vector3D(0, 1, 0);
    rightView = Vector3D(1, 0, 0);
    // Pour le FPS mode
    forwardMove = Vector3D(0, 0, -1);
    at = Vector3D(0, 1, 0);
    rightMove = Vector3D(1, 0, 0);
    // on initialise la cible a partir de la camera et du vecteur vision
    targetPos = camPos + forwardView;

    glutDisplayFunc(affichage2D);
    ////glutIdleFunc(affichage2D);
    // Lancement de la boucle infinie GLUT
    glutMainLoop();
    
}



