#include "Note.h"
#include "vector3d.h"

#include <map>

// structure de données pour stocker les infos d'un vertex

// Souris
GLboolean boutonClick = false;
// mouvement effectué par les flèches du clavier
GLfloat straffeSpeed = 0;
GLfloat upDownMove = 0;
// Camera
Vector3D camPos;
Vector3D camPos2D = Vector3D(-0.5,0.5, 4);
Vector3D targetPos = Vector3D(0, 0, 0);;
Vector3D forwardMove;
Vector3D at;
Vector3D at2D = camPos2D + Vector3D(0,0,-1);
Vector3D rightMove;
Vector3D upWorld;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near1 = 0.1f;
float far1 = 100.0f;


//import des fichiers son (.ogg)

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

//les vecteurs de pointeurs notes
vector<Note*> blanc;
vector<Note*> noir;

// vecteurs des keys du clavier 
const char* keyBlanc = "qsdfghjklm4561";
const char* keyNoir = "zetyuop$*7";
string keyBlancStr = "qsdfghjklm4561";
string keyNoirStr = "zetyuop$*7";

//un vecteur possedant l'état enfoncé ou relaché des bouttons
vector<bool> isPressedBlanc(14, false);
vector<bool> isPressedNoir(10, false);

//fonction de mouvement de la camera

void cameraMovement(float dM, float dS) {
    
        camPos += dM * forwardMove;
        camPos += dS * rightMove;

        if (dS !=0) {
            at = Vector3D(camPos.getVx(), 1, 0 );
        }
}

bool testHB = false; 
bool testCP = false;
bool testCustom = false;
int iterateurHB = 0; 
int iterateurCP = 0;
int iterateurCustom = 0;
int oldIndex = -5;
int oldIndex2 = -5;
string HB = "qqsqfdqqsqgfqqkhgfduuhfgf-"; 
string Carr = "hklllm4445mmlklhklllm445mmlklhhklll4555677656llm4456ll4mm4l4m-";
string CustomSheet = "";

void playSong(bool test , string sheet, int number) {
    int iter;
    if (number == 1) {
        iter = iterateurHB;
    }
    else if (number == 2) {
        iter = iterateurCP;
    }
    else if (number == 3) {
        iter = iterateurCustom;
    }
    if (test && iter < sheet.size()) {
        int index = keyBlancStr.find(sheet[iter]);
        int index2 = keyNoirStr.find(sheet[iter]);
        if (oldIndex == -1 && oldIndex2 != -1) { isPressedNoir[oldIndex2] = false; }
        if (oldIndex2 == -1 && oldIndex !=-1) { isPressedBlanc[oldIndex] = false; }
        Sleep(100);
        if (index == -1 && index2 == -1) {

        }
        else if (index == -1) {
            noir[index2]->setMusicOn();
            isPressedNoir[index2] = true;
            noir[index2]->playMusic();
            Sleep(350);
        }
        else if (index2 == -1)
        {
            blanc[index]->setMusicOn();
            isPressedBlanc[index] = true;
            blanc[index]->playMusic();
            Sleep(350);
        }


        if (iter == sheet.size() - 1) {
            test = false;
            oldIndex = 0; oldIndex2 = 0; iter = 0;
            isPressedNoir.assign(isPressedNoir.size(), false);
            isPressedBlanc.assign(isPressedBlanc.size(), false);
            if (number == 1) {
                iterateurHB = 0;
                testHB = false;
            }
            else if (number == 2)
            {
                iterateurCP = 0;
                testCP = false;
            }
            else if (number == 3) {
                iterateurCustom = 0;
                testCustom = false;
            }
        }
        else {
            if (number == 1) {
               iterateurHB++;
            }
            else if (number == 2) 
            {
                iterateurCP++;
            }
            else if (number == 3) {
                iterateurCustom++;
            }
        }
        oldIndex = index;
        oldIndex2 = index2;
    }
}

// Definition de la fonction d'affichage
// piano 3D
GLvoid affichage3D() {

    cameraMovement(upDownMove, straffeSpeed);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //profondeur
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(camPos.getVx(), camPos.getVy(), camPos.getVz() , at.getVx(), at.getVy(), at.getVz(), upWorld.getVx(), upWorld.getVy(), upWorld.getVz());
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-4.0f, 0.0f, 0.0f);
  

    //sheet musics
    playSong(testHB, HB, 1);
    playSong(testCP, Carr, 2);
    playSong(testCustom, CustomSheet, 3);

    


  // on remplit blanc et noir en les dessinant 
    auto it = noteBlanches.begin();
    for (int i = 0; i < 14; i++) {
        glPushMatrix();
        glTranslatef(0.5f * i, 0.0f, 0.0f);
        Note* n = new Note(keyBlanc[i]);
        n->setCouleur(1.0f);
        n->setMusic(it->first);
        n->setR(it->second[0]);  n->setG(it->second[1]); n->setB(it->second[2]); n->setId(identifiantBlanc[i]);
        n->drawNote3(n->getCouleur(),isPressedBlanc[i]);
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
        Note* n = new Note(keyNoir[i]);
        n->setCouleur(0.0f);
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
        Note* n = new Note(keyNoir[i - 1]);
        n->setCouleur(0.0f);
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
        Note* n = new Note(keyNoir[i - 2]);
        n->setCouleur(0.0f);
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
        Note* n = new Note(keyNoir[i - 3]);
        n->setCouleur(0.0f);
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
    glFlush();
    glutSwapBuffers();

}

// piano 2D
GLvoid affichage2D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(camPos2D.getVx(), camPos2D.getVy(), camPos2D.getVz(), at2D.getVx(), at2D.getVy(), at2D.getVz(), upWorld.getVx(), upWorld.getVy(), upWorld.getVz());
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-4.0f, 0.0f, 0.0f);

    //sheet musics
    playSong(testHB, HB, 1);
    playSong(testCP, Carr, 2);
    playSong(testCustom, CustomSheet, 3);

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
        n->drawNote(n->getCouleur(),isPressedBlanc[i]);
        it++;
        glTranslatef(0.0f, 0.0f, 0.1);
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
        n->drawNote(n->getCouleur(), isPressedNoir[i]);
        ++itN;
        glTranslatef(0.0f, 0.0f, 0.1);
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
        n->drawNote(n->getCouleur(), isPressedNoir[i-1]);
        itN++;
        glTranslatef(0.0f, 0.0f, 0.1);
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
        n->drawNote(n->getCouleur(), isPressedNoir[i-2]);
        itN++;
        glTranslatef(0.0f, 0.0f, 0.1);
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
        n->drawNote(n->getCouleur(), isPressedNoir[i-3]);;
        itN++;
        glTranslatef(0.0f, 0.0f, 0.1);
        n->drawChar(n->getCouleur());
        noir.push_back(n);
        glPopMatrix();
    }

    glFlush();
    glutSwapBuffers();

}

// fonction du clavier relaché
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

//la fonction gerant les input clavier
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
    if (touche == '9') {
            testHB = true; 
            testCP = false;
            testCustom = false;
    }
    else if (touche == '2') {
            testCP = true;
            testHB = false;
            testCustom = false;
    }
    else if (touche == '8' && CustomSheet != "") {
        testCP = false;
        testHB = false;
        testCustom = true;
    }
    if (touche == '0') {
        testHB = false; testCP = false;  isPressedNoir.assign(isPressedNoir.size(), false);
        isPressedBlanc.assign(isPressedBlanc.size(), false); oldIndex = 0; oldIndex2 = 0;
        iterateurHB = 0; iterateurCP = 0;
    }
    
   
    glutPostRedisplay();
}

// fonction qui retourne le char de la note et sa couleur avec son id entré en paramètre
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
    return pickedID;
}
float A;
map<char, int> Dict{ {'a',1} };
// gestion des clics de la souris
GLvoid souris(int boutton, int etat, int x, int y)
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

void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
        camPos.setVz(camPos.getVz() - 0.1);
    }
    else
    {
        camPos.setVz(camPos.getVz() + 0.1);
    }
    glutPostRedisplay();

    return;
}

// fonction de gestion des flèches du clavier
void catchKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        straffeSpeed = -0.01f;
        break;
    case GLUT_KEY_RIGHT:
        straffeSpeed = +0.01f;
        break;
    case GLUT_KEY_UP:
        upDownMove = 0.01f;
        break;
    case GLUT_KEY_DOWN:
        upDownMove = -0.01f;
        break;
    }
}

// fonction de gestion des flèches enfoncès du clavier 
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

// fonction de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
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
    glMatrixMode(GL_MODELVIEW);
}


void main(int argc, char* argv[])
{
    //choix du type du piano
    cout << "Veuillez choisir le mode d'affichage \n'1' pour l'affichage 2D \n'2' pour l'affichage 3D \n'3' pour  enregistrer une chanson a jouer (sequence de lettres)" << endl;
    int a;
    cin >> a;
    cout << endl;
    // si les valeurs sont différents de 1 ou 2 on affiche le piano 3D
    
    if (a == 3) {
        cout << "Veuillez entrer la séquence de notes a jouer"<< endl;
        cin >> CustomSheet;
        CustomSheet += "-";
        cout << "Veuillez choisir le mode d'affichage \n'1' pour l'affichage 2D \n'2' pour l'affichage 3D" << endl;
        cin >> a;
    }
    
    if (a != 1 && a != 2) {
        a = 2;
   }
    cout << "Apres avoir choisir le type, appuyez sur :" << endl ;
    cout << "2 pour jouer le debut des pirates des caraibes" << endl;
    cout << "9 pour jouer le debut de joyeux anniversaire" << endl;
    if (CustomSheet != "") {
        cout << "8 pour jouer la music que vous avez entrez" << endl;
    }
    cout << "0 pour arreter la musique" << endl;
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
     // Position initiale de la fenetre GLUT
    glutInitWindowPosition(200, 200);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("Piano");
    // Définition de la couleur d'effacement du framebuffer (rouge bordeaux)
    glClearColor(0.4f, 0.0f, 0.0f, 0.0f);
    // Définition des fonctions de callbacks
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUp);
    glutMouseFunc(souris);
    glutSpecialFunc(catchKey);
    glutSpecialUpFunc(catchKeyDown);
    glutMouseWheelFunc(mouseWheel);
    glutReshapeFunc(redimensionner);
    camPos = Vector3D(-0.5, -1, 4);
    // on initialise les vecteurs de la camera
    upWorld = Vector3D(0, 1, 0);
    forwardMove = Vector3D(0, 0, 1);
    at = Vector3D(-0.5,1,0);
    rightMove = Vector3D(1, 0, 0);
    targetPos = Vector3D(0,3,0);
    
    if (a == 1) {
        glutDisplayFunc(affichage2D);
        glutIdleFunc(affichage2D);
    }
    else if (a ==2) {
        glutDisplayFunc(affichage3D);
        glutIdleFunc(affichage3D);
    }

    // Lancement de la boucle infinie GLUT
    glutMainLoop();
    
}



