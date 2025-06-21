#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "help.h"
#include <conio.h>
#include<string>


using namespace std;


// Constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 900;
const int ALIEN_ROWS = 10;
const int ALIEN_COLS = 5;
const int SHIELDS = 4;
const int MAX_ALIEN_BULLETS = 10;
const int MAX_PLAYER_BULLETS = 10;
const int NUM_MENU_OPTIONS = 4;  // Total menu options
const char* MENU_OPTIONS[NUM_MENU_OPTIONS] = { "START GAME", "HIGH SCORES", "   EXIT" ," Prev Game" };
const int SCORE_BOX_X = 20; // Position inside the screen, below the main area
const int SCORE_BOX_Y = SCREEN_HEIGHT + 10; // Position just below the screen boundary

const int LIVES_BOX_X = SCREEN_WIDTH / 2 + 20; // Position next to score box
const int LIVES_BOX_Y = SCREEN_HEIGHT + 10; // Position just below the screen boundary

const int BOX_WIDTH = 200; // Width of the box
const int BOX_HEIGHT = 80; // Height of the box
int selectedAlienType = 0; // 0 for ellipse alien, 1 for square alien
int selectedSpaceshipType = 0;
const int NUM_STARS = 300; // Number of stars
int starX[NUM_STARS];
int starY[NUM_STARS];
int starRadius[NUM_STARS];


// Variables
float playerX = 50, playerY = SCREEN_HEIGHT / 2;
float playerBulletX[MAX_PLAYER_BULLETS], playerBulletY[MAX_PLAYER_BULLETS];
bool playerBulletActive[MAX_PLAYER_BULLETS] = { false };
bool exitToMenu = false; // Global or passed to gameLoop as a reference
bool aliens[ALIEN_ROWS][ALIEN_COLS];
float alienX[ALIEN_ROWS][ALIEN_COLS], alienY[ALIEN_ROWS][ALIEN_COLS];
int alienSpeed = 20, alienDirection = 1, alienCycleDirection = 1, alienDrop = 30;
int selectedDifficultyOption;
float alienBulletX[MAX_ALIEN_BULLETS], alienBulletY[MAX_ALIEN_BULLETS];
bool alienBulletActive[MAX_ALIEN_BULLETS] = { false };
int selectedOption = 0;
int shieldX[SHIELDS], shieldY[SHIELDS], shieldHealth[SHIELDS];
int score = 0, lives = 3, highScore = 0, highScores[5] = { 0 };
bool isEasyDifficulty = true; // Default difficulty is easy
bool shieldVisible[SHIELDS]; // Array to track visibility of each shield
int handslegs = 0;

int handschangey = 0;
int legschangex = 0;
int legschangey = 0;


// Function Prototypes
void initializeGame();
void drawMenu();
void drawGame();
void handleInput();
void moveAliens();

void firePlayerBullet();
void movePlayerBullets();
void fireAlienBullet();
void moveAlienBullets();
void checkCollisions();
bool allAliensDestroyed();
void gameOver(bool win);
void eraseObject(float x1, float y1, float x2, float y2);
void saveHighScore();
void loadHighScore();
void drawHighScores();
void gameLoop();
void pauseGame();
void saveGameState();
void loadGameState();
void selectAlienMenu();
void drawAngryFace(float x, float y);
void  drawEllipseAlienPreview(float x, float y);
void  drawSquareAlienPreview(float x, float y);
void drawSpaceship(float x, float y);
void eraseSpaceship(float x, float y);

void initializeStars() {
    const int BORDER_PADDING = 20; // Ensure stars don't appear on the very edges
    for (int i = 0; i < NUM_STARS; i++) {
        // Generate random positions within the screen boundaries, leaving a padding
        starX[i] = rand() % (SCREEN_WIDTH - 2 * BORDER_PADDING) + BORDER_PADDING;
        starY[i] = rand() % (SCREEN_HEIGHT - 2 * BORDER_PADDING) + BORDER_PADDING;

        // Generate random radius for stars (very small)
        starRadius[i] = (rand() % 3) + 1;  // Radius between 1 and 3
    }
}



void selectSpaceshipMenu() {
    const int NUM_SPACESHIP_OPTIONS = 2;
    const char* SPACESHIP_NAMES[NUM_SPACESHIP_OPTIONS] = {
        "MAS 1",
        "MAS 2"
    };
    int selectedOption = 0;
    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear screen

    myLine(280, 80, 1600, 80, 220, 20, 60);
    myLine(280, 190, 1600, 190, 220, 20, 60);
    myLine(280, 330, 1600, 330, 220, 20, 60);
    myLine(280, 460, 1600, 460, 220, 20, 60);
    myLine(280, 80, 280, 460, 220, 20, 60);
    myLine(1600, 80, 1600, 460, 220, 20, 60);
    drawText(40, 520, 100, 1, 255, 72, "SELECT SPACESHIP TYPE");



    drawText(25, 430, 270, 1, 255, 72, SPACESHIP_NAMES[0]);
    selectedSpaceshipType = 0;
    drawSpaceship(460, 220);

    drawText(25, 1360, 270, 1, 255, 72, SPACESHIP_NAMES[1]);
    selectedSpaceshipType = 1;
    drawSpaceship(1400, 220);

    while (true) {

        // Highlight selected option
        if (selectedOption == 0) {
            drawText(30, 1280, 350, 220, 20, 60, "Selected");
            drawText(50, 320, 350, 203, 0, 245, "Selected");
        }
        else {
            drawText(30, 370, 350, 220, 20, 60, "Selected");
            drawText(50, 1130, 350, 203, 0, 245, "Selected");
        }
        // Handle user input
        int whichKey;
        if (isKeyPressed(whichKey)) {
            myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear screen

            myLine(280, 80, 1600, 80, 220, 20, 60);
            myLine(280, 190, 1600, 190, 220, 20, 60);
            myLine(280, 330, 1600, 330, 220, 20, 60);
            myLine(280, 460, 1600, 460, 220, 20, 60);
            myLine(280, 80, 280, 460, 220, 20, 60);
            myLine(1600, 80, 1600, 460, 220, 20, 60);
            drawText(40, 520, 100, 1, 255, 72, "SELECT SPACESHIP TYPE");



            drawText(25, 430, 270, 1, 255, 72, SPACESHIP_NAMES[0]);
            selectedSpaceshipType = 0;
            drawSpaceship(460, 220);

            drawText(25, 1360, 270, 1, 255, 72, SPACESHIP_NAMES[1]);
            selectedSpaceshipType = 1;
            drawSpaceship(1400, 220);

            if (whichKey == 8 || whichKey == 9) { // W or A
                selectedOption = 0;
            }
            else if (whichKey == 10 || whichKey == 11) { // S or D
                selectedOption = 1;
            }
            else if (whichKey == 12) { // Space key
                selectedSpaceshipType = selectedOption;
                return; // Exit menu
            }
        }

        drawText(20, 480, 810, 1, 255, 72, "Use W/S/A/D keys to navigate Press Space to select.");
        Sleep(16);
    }
}
void selectAlienMenu() {
    const int NUM_ALIEN_OPTIONS = 2;
    const char* ALIEN_NAMES[NUM_ALIEN_OPTIONS] = {
        "NIG 1",
        "NIG 2"
    };
    int selectedOption = 0;
    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear screen
    myLine(230, 80, 1600, 80, 220, 20, 60);
    myLine(230, 190, 1600, 190, 220, 20, 60);
    myLine(230, 330, 1600, 330, 220, 20, 60);
    myLine(230, 460, 1600, 460, 220, 20, 60);
    myLine(230, 80, 230, 460, 220, 20, 60);
    myLine(1600, 80, 1600, 460, 220, 20, 60);
    drawText(40, 600, 100, 1, 255, 72, "SELECT ALIEN TYPE");

    // Draw and label each alien type
    drawText(25, 440, 250, 1, 255, 72, ALIEN_NAMES[0]);
    drawEllipseAlienPreview(SCREEN_WIDTH / 4, 200);

    drawText(25, 1340, 250, 1, 255, 72, ALIEN_NAMES[1]);
    drawSquareAlienPreview(2.95 * SCREEN_WIDTH / 4 - 30, 200);

    while (true) {
        // Highlight selected option
        if (selectedOption == 0) {
            drawText(30, 1280, 350, 220, 20, 60, "Selected");
            drawText(50, 320, 350, 203, 0, 245, "Selected");
        }
        else {
            drawText(30, 370, 350, 220, 20, 60, "Selected");
            drawText(50, 1130, 350, 203, 0, 245, "Selected");
        }

        // Handle user input
        int whichKey;
        if (isKeyPressed(whichKey)) {
            myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear screen
            myLine(230, 80, 1600, 80, 220, 20, 60);
            myLine(230, 190, 1600, 190, 220, 20, 60);
            myLine(230, 330, 1600, 330, 220, 20, 60);
            myLine(230, 460, 1600, 460, 220, 20, 60);
            myLine(230, 80, 230, 460, 220, 20, 60);
            myLine(1600, 80, 1600, 460, 220, 20, 60);
            drawText(40, 600, 100, 1, 255, 72, "SELECT ALIEN TYPE");

            // Draw and label each alien type
            drawText(25, 440, 250, 1, 255, 72, ALIEN_NAMES[0]);
            drawEllipseAlienPreview(SCREEN_WIDTH / 4, 200);

            drawText(25, 1340, 250, 1, 255, 72, ALIEN_NAMES[1]);
            drawSquareAlienPreview(2.95 * SCREEN_WIDTH / 4 - 30, 200);

            if (whichKey == 8 || whichKey == 9) { // W or A
                selectedOption = 0;
            }
            else if (whichKey == 10 || whichKey == 11) { // S or D
                selectedOption = 1;
            }
            else if (whichKey == 12) { // Space key
                selectedAlienType = selectedOption;
                return; // Exit menu
            }
        }

        drawText(20, 480, 810, 1, 255, 72, "Use W/S/A/D keys to navigate Press Space to select");
        Sleep(16);
    }
}

void drawEllipseAlienPreview(float x, float y) {
    // Ellipse Alien Preview
    myEllipse(x, y, x + 30, y + 30, 75, 0, 130, 102, 51, 153);




    myLine(x + 15, y + 15, x - 13, y + 25, 102, 51, 153); // Left hand
    myLine(x + 15, y + 15, x + 43, y + 25, 102, 51, 153); // Right hand

    // Draw static legs
    myLine(x + 5, y + 30, x - 5, y + 40, 102, 51, 153);  // Left leg
    myLine(x + 25, y + 30, x + 35, y + 40, 102, 51, 153); // Right leg
    drawAngryFace(x, y);
}

void drawSquareAlienPreview(float x, float y) {
    // Square Alien Preview
    myRect(x, y, x + 30, y + 30, 139, 0, 0, 220, 20, 60);




    myLine(x + 15, y + 15, x - 13, y + 25, 220, 20, 60); // Left hand
    myLine(x + 15, y + 15, x + 43, y + 25, 220, 20, 60); // Right hand

    // Draw static legs
    myLine(x + 5, y + 30, x - 5, y + 40, 220, 20, 60);  // Left leg
    myLine(x + 25, y + 30, x + 35, y + 40, 220, 20, 60); // Right leg
    drawAngryFace(x, y);
}



void drawShields() {
    for (int i = 0; i < SHIELDS; i++) {
        if (shieldVisible[i]) { // Draw only visible shields
            myRect(shieldX[i], shieldY[i], shieldX[i] + 20, shieldY[i] + 100, 0, 168, 119, 60, 208, 112);
        }
    }
}


void updateHighScores(int currentScore) {
    // Insert the current score into the high scores list if it qualifies
    for (int i = 0; i < 5; i++) {
        if (currentScore > highScores[i]) {
            // Shift lower scores down
            for (int j = 4; j > i; j--) {
                highScores[j] = highScores[j - 1];
            }
            highScores[i] = currentScore;
            break;
        }
    }

    saveHighScore();  // Save the updated high scores
}



void eraseSpaceship(float x, float y) {

    if (selectedSpaceshipType == 0) {
        myRect(x, y, x + 50, y + 25, 0, 0, 26, 0, 0, 26);  // Blue body with a red border

        // Nose of the spaceship - Rotated to point towards the aliens
        for (float i = 0; i <= 10; i += 2.5) {

            myRect(x - 2.5 - i, y + 12.5 - i / 2, x - i, y + 12.5 + i / 2, 0, 0, 26, 0, 0, 26); // Red-filled gradient rectangles
        }

        // Top Wing - Single line tilted forward

        myLine(x + 10, y, x - 5, y - 15, 0, 0, 26); // Top wing line

        // Bottom Wing - Single line tilted forward

        myLine(x + 10, y + 25, x - 5, y + 40, 0, 0, 26); // Bottom wing line

        // Cockpit - Smaller Ellipse on the body

        myEllipse(x + 15, y + 5, x + 35, y + 20, 0, 0, 26, 0, 0, 26); // Yellow cockpit

        // Booster flames - Proportional to smaller size

        myLine(x - 10, y + 5, x - 20, y, 0, 0, 26);

        myLine(x - 10, y + 18, x - 20, y + 23, 0, 0, 26); // Bottom flame

        // Nose proportions
        float noseWidth = 25;    // Width of the triangle
        float noseHeight = 15;   // Height of the triangle
        float rectWidth = 2.5;   // Width of each rectangle

        // Position the nose to the right side of the spaceship
        float noseStartX = x + 50; // Front edge of the spaceship
        float noseCenterY = y + 12.5; // Center of the spaceship's height

        // Draw the filled triangular nose
        for (float i = 0; i < noseWidth; i += rectWidth) {
            float rectHeight = noseHeight * (1 - i / noseWidth); // Reduce height as we move to the right

            myRect(noseStartX + i, noseCenterY - rectHeight / 2,
                noseStartX + i + rectWidth, noseCenterY + rectHeight / 2,
                0, 0, 26); // Single color (Red)
        }
    }
    else {
        myEllipse(x, y, x + 50, y + 25, 0, 0, 26, 0, 0, 26);  // Blue body with a red border

        // Nose of the spaceship - Rotated to point towards the aliens
        for (float i = 0; i <= 10; i += 2.5) {

            myRect(x - 2.5 - i, y + 12.5 - i / 2, x - i, y + 12.5 + i / 2, 0, 0, 26); // Red-filled gradient rectangles
        }

        // Top Wing - Single line tilted forward

        myLine(x + 10, y, x - 5, y - 15, 0, 0, 26); // Top wing line
        myLine(x + 27, y, x + 12, y - 15, 0, 0, 26); // Top wing line
        // Bottom Wing - Single line tilted forward

        myLine(x + 10, y + 25, x - 5, y + 40, 0, 0, 26); // Bottom wing line
        myLine(x + 27, y + 25, x + 12, y + 40, 0, 0, 26);
        // Cockpit - Smaller Ellipse on the body

        myRect(x + 15, y + 8, x + 35, y + 18, 0, 0, 26, 0, 0, 26); // Yellow cockpit

        // Booster flames - Proportional to smaller size

        myLine(x - 10, y + 5, x - 20, y, 0, 0, 26);

        myLine(x - 10, y + 18, x - 20, y + 23, 0, 0, 26); // Bottom flame

        // Nose proportions
        float noseWidth = 25;    // Width of the triangle
        float noseHeight = 15;   // Height of the triangle
        float rectWidth = 2.5;   // Width of each rectangle

        // Position the nose to the right side of the spaceship
        float noseStartX = x + 50; // Front edge of the spaceship
        float noseCenterY = y + 12.5; // Center of the spaceship's height

        // Draw the filled triangular nose
        for (float i = 0; i < noseWidth; i += rectWidth) {
            float rectHeight = noseHeight * (1 - i / noseWidth); // Reduce height as we move to the right

            myRect(noseStartX + i, noseCenterY - rectHeight / 2,
                noseStartX + i + rectWidth, noseCenterY + rectHeight / 2,
                0, 0, 26); // Single color (Red)
        }
    }
}
void drawSpaceship(float x, float y) {
    // Main body - Smaller Filled Rectangle
    if (selectedSpaceshipType == 0) {
        myRect(x, y, x + 50, y + 25, 119, 136, 153, 145, 163, 176);  // Blue body with a red border

        // Nose of the spaceship - Rotated to point towards the aliens
        for (float i = 0; i <= 10; i += 2.5) {

            myRect(x - 2.5 - i, y + 12.5 - i / 2, x - i, y + 12.5 + i / 2, 220, 20, 60); // Red-filled gradient rectangles
        }

        // Top Wing - Single line tilted forward

        myLine(x + 10, y, x - 5, y - 15, 164, 0, 0); // Top wing line

        // Bottom Wing - Single line tilted forward

        myLine(x + 10, y + 25, x - 5, y + 40, 164, 0, 0); // Bottom wing line

        // Cockpit - Smaller Ellipse on the body

        myEllipse(x + 15, y + 5, x + 35, y + 20, 0, 0, 26, 173, 216, 230); // Yellow cockpit

        // Booster flames - Proportional to smaller size

        myLine(x - 10, y + 5, x - 20, y, 255, 140, 0);

        myLine(x - 10, y + 18, x - 20, y + 23, 255, 140, 0); // Bottom flame

        // Nose proportions
        float noseWidth = 25;    // Width of the triangle
        float noseHeight = 15;   // Height of the triangle
        float rectWidth = 2.5;   // Width of each rectangle

        // Position the nose to the right side of the spaceship
        float noseStartX = x + 50; // Front edge of the spaceship
        float noseCenterY = y + 12.5; // Center of the spaceship's height

        // Draw the filled triangular nose
        for (float i = 0; i < noseWidth; i += rectWidth) {
            float rectHeight = noseHeight * (1 - i / noseWidth); // Reduce height as we move to the right

            myRect(noseStartX + i, noseCenterY - rectHeight / 2,
                noseStartX + i + rectWidth, noseCenterY + rectHeight / 2,
                164, 0, 0); // Single color (Red)
        }
    }
    else {
        myEllipse(x, y, x + 50, y + 25, 220, 220, 220, 248, 248, 255);  // Blue body with a red border

        // Nose of the spaceship - Rotated to point towards the aliens
        for (float i = 0; i <= 10; i += 2.5) {

            myRect(x - 2.5 - i, y + 12.5 - i / 2, x - i, y + 12.5 + i / 2, 143, 0, 255); // Red-filled gradient rectangles
        }

        // Top Wing - Single line tilted forward

        myLine(x + 10, y, x - 5, y - 15, 143, 0, 255); // Top wing line
        myLine(x + 27, y, x + 12, y - 15, 143, 0, 255); // Top wing line
        // Bottom Wing - Single line tilted forward

        myLine(x + 10, y + 25, x - 5, y + 40, 143, 0, 255); // Bottom wing line
        myLine(x + 27, y + 25, x + 12, y + 40, 143, 0, 255);
        // Cockpit - Smaller Ellipse on the body

        myRect(x + 15, y + 8, x + 35, y + 18, 76, 51, 113, 198, 230, 251); // Yellow cockpit

        // Booster flames - Proportional to smaller size

        myLine(x - 10, y + 5, x - 20, y, 203, 0, 245);

        myLine(x - 10, y + 18, x - 20, y + 23, 203, 0, 245); // Bottom flame

        // Nose proportions
        float noseWidth = 25;    // Width of the triangle
        float noseHeight = 15;   // Height of the triangle
        float rectWidth = 2.5;   // Width of each rectangle

        // Position the nose to the right side of the spaceship
        float noseStartX = x + 50; // Front edge of the spaceship
        float noseCenterY = y + 12.5; // Center of the spaceship's height

        // Draw the filled triangular nose
        for (float i = 0; i < noseWidth; i += rectWidth) {
            float rectHeight = noseHeight * (1 - i / noseWidth); // Reduce height as we move to the right

            myRect(noseStartX + i, noseCenterY - rectHeight / 2,
                noseStartX + i + rectWidth, noseCenterY + rectHeight / 2,
                143, 0, 255); // Single color (Red)
        }
    }
}

void drawAngryFace(float x, float y) {
    // Adjustments for face size relative to alien body
    float faceWidth = 30;  // Width of the alien's face
    float faceHeight = 30;

    // Center offsets for face features within the ellipse
    float centerX = x + faceWidth / 2;
    float centerY = y + faceHeight / 2;

    // Eyebrows (Angry, slanting inward like \ /)
    myLine(centerX - 5, centerY - 5, centerX - 10, centerY - 10, 0, 0, 0);  // Left eyebrow
    myLine(centerX + 5, centerY - 5, centerX + 10, centerY - 10, 0, 0, 0);  // Right eyebrow

    // Eyes (Small ellipses positioned below eyebrows)
    myEllipse(centerX - 8, centerY - 5, centerX - 4, centerY - 1, 255, 255, 255);  // Left eye
    myEllipse(centerX + 4, centerY - 5, centerX + 8, centerY - 1, 255, 255, 255);  // Right eye

    // Mouth (Downward curve for angry expression)
    myLine(centerX - 4, centerY + 5, centerX + 4, centerY + 5, 0, 0, 0);  // Middle flat
}

// Function to erase objects
void eraseObject(float x1, float y1, float x2, float y2) {
    myRect(x1, y1, x2, y2, 0, 0, 26, 0, 0, 26);
}

// Function to draw the high scores
void drawHighScores() {

    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);  // Clear the screen
    while (true)
    {
        drawText(50, 700, 100, 1, 255, 72, "HIGH SCORES");

        for (int i = 0; i < 5; i++) {
            char scoreStr[20];
            sprintf_s(scoreStr, "%d", highScores[i]);  // Convert score to string
            char rankStr[30];
            sprintf_s(rankStr, "%d. %s", i + 1, scoreStr);  // Add rank to score
            drawText(30, 850, 250 + i * 100, 203, 0, 245, rankStr);  // Adjust Y-coordinate for each score
        }

        drawText(20, 600, SCREEN_HEIGHT - 80, 1, 255, 72, "Press any key to return to the menu.");
        int whichKey;
        if (isKeyPressed(whichKey))
            break;
    }
}


// Initialize game
void initializeGame() {
    playerX = 50;
    playerY = SCREEN_HEIGHT / 2;
    score = 0;
    lives = 3;

    // Initialize aliens

    const int horizontalSpacing = 70; // Increase horizontal spacing
    const int verticalSpacing = 50;  // Increase vertical spacing

    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            aliens[i][j] = true;
            alienX[i][j] = SCREEN_WIDTH - (ALIEN_COLS - j) * horizontalSpacing;
            alienY[i][j] = i * verticalSpacing + 50;
        }
    }

    // Initialize shields
    for (int i = 0; i < SHIELDS; i++) {
        shieldX[i] = playerX + 150;
        shieldY[i] = (SCREEN_HEIGHT / SHIELDS) * i + 80;
        shieldHealth[i] = 5;
        shieldVisible[i] = true; // All shields start visible
    }

    // Initialize bullets
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        playerBulletActive[i] = false;
    }
    for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
        alienBulletActive[i] = false;
    }


    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);  // Game boundary
    initializeStars();

}

// Draw Menu
void drawMenu() {

    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);  // Draw game boundary
    myLine(600, 50, 1330, 50, 255, 0, 56);
    myLine(600, 770, 1330, 770, 255, 0, 56);
    myLine(600, 50, 600, 770, 255, 0, 56);
    myLine(1330, 50, 1330, 770, 255, 0, 56);

    myLine(600, 180, 1330, 180, 255, 0, 56);
    myLine(600, 320, 1330, 320, 255, 0, 56);
    myLine(600, 470, 1330, 470, 255, 0, 56);
    myLine(600, 630, 1330, 630, 255, 0, 56);
    drawText(40, 650, 70, 1, 255, 72, "Destroying GNFOS");

    for (int i = 0; i < NUM_MENU_OPTIONS; i++) {
        if (i == selectedOption) {
            drawText(50, SCREEN_WIDTH / 2 - 260, 200 + (i * 150), 203, 0, 245, MENU_OPTIONS[i]);
        }
        else {
            drawText(30, SCREEN_WIDTH / 2 - 160, 200 + (i * 150), 220, 20, 60, MENU_OPTIONS[i]);
        }
    }

    drawText(20, 690, 810, 1, 255, 72, "Created By Ahmad Mursaleen");
}
void checkAliensLeftBoundaryCollision() {
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j]) {  // Check only active aliens
                if (alienX[i][j] <= 20) {  // Left boundary condition (20 for game boundary)
                    gameOver(false);  // Trigger game over with a loss
                    return;  // Exit the function as the game is over
                }
            }
        }
    }
}

void drawDifficultyMenu() {
    const int NUM_DIFFICULTY_OPTIONS = 2;
    const char* DIFFICULTY_OPTIONS[NUM_DIFFICULTY_OPTIONS] = {
        "  Easy",
        "Difficult"
    };
    selectedDifficultyOption = 0; // Track the currently selected difficulty option

    // Calculate center positioning
    int menuStartX = SCREEN_WIDTH / 2 - 100; // Center the menu horizontally
    int menuStartY = SCREEN_HEIGHT / 3;       // Center the menu vertically

    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear the screen
    drawText(50, SCREEN_WIDTH / 2 - 400, 80, 1, 255, 72, "SELECT DIFFICULTY");
    myLine(550, 50, 1425, 50, 255, 0, 56);
    myLine(550, 560, 1425, 560, 255, 0, 56);
    myLine(550, 250, 1425, 250, 255, 0, 56);
    myLine(550, 430, 1425, 430, 255, 0, 56);
    myLine(550, 50, 550, 560, 255, 0, 56);
    myLine(1425, 50, 1425, 560, 255, 0, 56);       myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear the screen
    drawText(50, SCREEN_WIDTH / 2 - 400, 80, 1, 255, 72, "SELECT DIFFICULTY");
    myLine(550, 50, 1425, 50, 255, 0, 56);
    myLine(550, 560, 1425, 560, 255, 0, 56);
    myLine(550, 250, 1425, 250, 255, 0, 56);
    myLine(550, 430, 1425, 430, 255, 0, 56);
    myLine(550, 50, 550, 560, 255, 0, 56);
    myLine(1425, 50, 1425, 560, 255, 0, 56);
    while (true) {



        // Draw difficulty options with proper spacing and alignment
        for (int i = 0; i < NUM_DIFFICULTY_OPTIONS; i++) {
            int yPosition = menuStartY + (i * 100); // Space between each option
            if (i == selectedDifficultyOption) {
                drawText(45, menuStartX - 70, yPosition + 50 * i, 203, 0, 245, DIFFICULTY_OPTIONS[i]);
            }
            else {
                drawText(30, menuStartX - 10, yPosition + 50 * i, 220, 20, 60, DIFFICULTY_OPTIONS[i]);
            }
        }

        // Handle user input for selecting difficulty
        int whichKey;
        if (isKeyPressed(whichKey)) {
            myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear the screen
            drawText(50, SCREEN_WIDTH / 2 - 400, 80, 1, 255, 72, "SELECT DIFFICULTY");
            myLine(550, 50, 1425, 50, 255, 0, 56);
            myLine(550, 560, 1425, 560, 255, 0, 56);
            myLine(550, 250, 1425, 250, 255, 0, 56);
            myLine(550, 430, 1425, 430, 255, 0, 56);
            myLine(550, 50, 550, 560, 255, 0, 56);
            myLine(1425, 50, 1425, 560, 255, 0, 56);
            if (whichKey == 9) { // W
                selectedDifficultyOption = (selectedDifficultyOption - 1 + NUM_DIFFICULTY_OPTIONS) % NUM_DIFFICULTY_OPTIONS;
            }
            else if (whichKey == 10) { //S
                selectedDifficultyOption = (selectedDifficultyOption + 1) % NUM_DIFFICULTY_OPTIONS;
            }
            else if (whichKey == 12) { // Space
                // Set the selected difficulty level based on user choice
                if (selectedDifficultyOption == 0) {
                    isEasyDifficulty = true;
                }
                else if (selectedDifficultyOption == 1) {
                    isEasyDifficulty = false;
                }


                // Return to the main menu after selecting difficulty
                return;
            }
        }
        drawText(24, 250, 750, 1, 255, 72, "Use W or S keys to navigate And Press Space to select");
        Sleep(16); // Delay for smoother interaction
    }

}





// Menu key handling
void handleMenuInput() {
    int whichKey;
    if (isKeyPressed(whichKey)) {
        if (whichKey == 9) {  // W
            selectedOption = (selectedOption - 1 + NUM_MENU_OPTIONS) % NUM_MENU_OPTIONS;
        }
        else if (whichKey == 10) {  // S
            selectedOption = (selectedOption + 1) % NUM_MENU_OPTIONS;
        }
        else if (whichKey == 12) {  // Space
            if (selectedOption == 0) {  // "START GAME"
                drawDifficultyMenu();
                selectAlienMenu();
                selectSpaceshipMenu();
                initializeGame();
                drawSpaceship(playerX, playerY);
                gameLoop();
            }
            else if (selectedOption == 1) {  // "HIGH SCORES"
                drawHighScores();  // Show high scores
            }
            else if (selectedOption == 2) {  // "EXIT"
                exit(0);  // Exit game
            }
            else if (selectedOption == 3)
            {
                myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);  // Game boundary
                loadGameState();
                initializeStars();
                drawShields();
                drawSpaceship(playerX, playerY);
                gameLoop();
            }
        }
    }
    Sleep(16);
}
void drawStars() {
    for (int i = 0; i < NUM_STARS; i++) {
        if (starX[i] >= 20 && starX[i] <= SCREEN_WIDTH - 20 &&
            starY[i] >= 20 && starY[i] <= SCREEN_HEIGHT - 20) {
            // Draw each star
            myEllipse(starX[i], starY[i], starX[i] + starRadius[i], starY[i] + starRadius[i], 255, 255, 255);
        }
    }
}


// Draw game
void drawGame() {


    drawShields();
    drawStars();



    // Erase and draw player bullets
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (playerBulletActive[i]) {

            myRect(playerBulletX[i], playerBulletY[i], playerBulletX[i] + 10, playerBulletY[i] - 5, 0, 0, 26, 0, 0, 26);  // Erase old bullet
            if (playerBulletX[i] < (SCREEN_WIDTH - 45))
            {
                playerBulletX[i] += 15;  // Move the bullet
                myRect(playerBulletX[i], playerBulletY[i], playerBulletX[i] + 10, playerBulletY[i] - 5, 60, 179, 113, 60, 179, 113);  // Draw new bullet
            }
            else
                playerBulletActive[i] = false;
        }
    }

    // Erase and draw alien bullets
    for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
        if (alienBulletActive[i]) {
            myRect(alienBulletX[i], alienBulletY[i], alienBulletX[i] + 10, alienBulletY[i] + 5, 0, 0, 26, 0, 0, 26);  // Erase old bullet
            if (alienBulletX[i] > 45)//check for alienbullet closing in on boundary
            {
                alienBulletX[i] -= 10;  // Move the bullet
                myRect(alienBulletX[i], alienBulletY[i], alienBulletX[i] + 10, alienBulletY[i] + 5, 199, 21, 133, 199, 21, 133);
            }
            else
                alienBulletActive[i] = false;//deactivate bullet if reached boundary
        }

    }



    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j]) {

                // Draw alien body
                if (selectedAlienType == 0) {
                    myEllipse(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 75, 0, 130, 102, 51, 153);
                    //shifting alien legs and hands
                    if (handslegs % 6 == 0) {
                        handschangey = -10;
                        legschangey = 0;
                        legschangex = 0;
                    }
                    else if (handslegs % 6 == 1) {
                        handschangey = 0;
                        legschangey = +5;
                        legschangex = -10;
                    }
                    else if (handslegs % 6 == 2) {
                        handschangey = -20;
                        legschangey = -5;
                        legschangex = 5;
                    }
                    else if (handslegs % 6 == 3) {
                        handschangey = 10;
                        legschangey = 0;
                        legschangex = 0;
                    }
                    else if (handslegs % 6 == 4) {
                        handschangey = 0;
                        legschangey = -5;
                        legschangex = -5;
                    }
                    else if (handslegs % 6 == 5) {
                        handschangey = -15;
                        legschangey = 5;
                        legschangex = 10;
                    }


                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Left hand
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Right hand

                    // Draw dynamic hands
                    myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26);  // Left leg
                    myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26); // Right leg
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 102, 51, 153); // Left hand
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 102, 51, 153); // Right hand

                    // Draw dynamic legs
                    myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 102, 51, 153);  // Left leg
                    myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 102, 51, 153); // Right leg
                    drawAngryFace(alienX[i][j], alienY[i][j]);
                }
                else {
                    //Draw alien body for second alien choice
                    myRect(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 139, 0, 0, 220, 20, 60);
                    //shifting alien legs and hands
                    if (handslegs % 6 == 0) {
                        handschangey = -10;
                        legschangey = 0;
                        legschangex = 0;
                    }
                    else if (handslegs % 6 == 1) {
                        handschangey = 0;
                        legschangey = +5;
                        legschangex = -10;
                    }
                    else if (handslegs % 6 == 2) {
                        handschangey = -20;
                        legschangey = -5;
                        legschangex = 5;
                    }
                    else if (handslegs % 6 == 3) {
                        handschangey = 10;
                        legschangey = 0;
                        legschangex = 0;
                    }
                    else if (handslegs % 6 == 4) {
                        handschangey = 0;
                        legschangey = -5;
                        legschangex = -5;
                    }
                    else if (handslegs % 6 == 5) {
                        handschangey = -15;
                        legschangey = 5;
                        legschangex = 10;
                    }

                    //draw dynamic hands
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Left hand
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Right hand

                    // Draw dynamic legs
                    myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26);  // Left leg
                    myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26); // Right leg

                    //draw dynamic hands
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 220, 20, 60); // Left hand
                    myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 220, 20, 60); // Right hand

                    // Draw dynamic legs
                    myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 220, 20, 60);  // Left leg
                    myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 220, 20, 60); // Right leg
                    drawAngryFace(alienX[i][j], alienY[i][j]);

                }

            }
        }


    }


    // Erase previous score box and redraw
    eraseObject(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT);
    myRect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT, 220, 20, 60, 0, 0, 26); // White box
    drawText(20, SCORE_BOX_X + 10, SCORE_BOX_Y + 20, 60, 179, 113, "SCORE: ");
    drawText(20, SCORE_BOX_X + 130, SCORE_BOX_Y + 20, 60, 179, 113, to_string(score).c_str());

    // Erase previous lives box and redraw
    eraseObject(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT);
    myRect(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT, 220, 20, 60, 0, 0, 26); // White box
    drawText(20, LIVES_BOX_X + 10, LIVES_BOX_Y + 20, 60, 179, 113, "LIVES: ");
    drawText(20, LIVES_BOX_X + 130, LIVES_BOX_Y + 20, 60, 179, 113, to_string(lives).c_str());
}

// Pause game
void pauseGame() {
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    const int NUM_PAUSE_OPTIONS = 4; // Number of pause menu options
    const char* PAUSE_OPTIONS[NUM_PAUSE_OPTIONS] = {
        " Resume Game",
        " Restart Game",
        " Exit to Menu",
        " Save and Exit"
    };
    int selectedOption = 0; // Tracks the currently selected option
    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear the screen
    drawText(60, SCREEN_WIDTH / 2 - 200 + 40, SCREEN_HEIGHT / 4 - 100, 1, 255, 72, "PAUSED");

    myLine(550, 100, 1380, 100, 220, 20, 60);
    myLine(550, 290, 1380, 290, 220, 20, 60);
    myLine(550, 450, 1380, 450, 220, 20, 60);
    myLine(550, 600, 1380, 600, 220, 20, 60);
    myLine(550, 750, 1380, 750, 220, 20, 60);
    myLine(550, 100, 550, SCREEN_HEIGHT, 220, 20, 60);
    myLine(1380, 100, 1380, SCREEN_HEIGHT, 220, 20, 60);
    while (true) {
        // Draw the pause menu


        for (int i = 0; i < NUM_PAUSE_OPTIONS; i++) {
            int xOffset = (i == 3) ? -20 : 0;

            if (i == selectedOption) {
                drawText(50, SCREEN_WIDTH / 2 - 400 + 60 + xOffset, SCREEN_HEIGHT / 2 + (i * 150) - 120, 203, 0, 245, PAUSE_OPTIONS[i]); // Highlight selected
            }
            else {
                drawText(30, SCREEN_WIDTH / 2 - 250 + 60 + xOffset, SCREEN_HEIGHT / 2 + (i * 150) - 120, 220, 20, 60, PAUSE_OPTIONS[i]);
            }
        }

        // Handle user input for menu navigation
        int whichKey;
        if (isKeyPressed(whichKey)) {
            myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26); // Clear the screen
            drawText(60, SCREEN_WIDTH / 2 - 200 + 40, SCREEN_HEIGHT / 4 - 100, 1, 255, 72, "PAUSED");

            myLine(550, 100, 1380, 100, 220, 20, 60);
            myLine(550, 290, 1380, 290, 220, 20, 60);
            myLine(550, 450, 1380, 450, 220, 20, 60);
            myLine(550, 600, 1380, 600, 220, 20, 60);
            myLine(550, 750, 1380, 750, 220, 20, 60);
            myLine(550, 100, 550, SCREEN_HEIGHT, 220, 20, 60);
            myLine(1380, 100, 1380, SCREEN_HEIGHT, 220, 20, 60);
            if (whichKey == 9) { // W arrow
                selectedOption = (selectedOption - 1 + NUM_PAUSE_OPTIONS) % NUM_PAUSE_OPTIONS;
            }
            else if (whichKey == 10) { // S arrow
                selectedOption = (selectedOption + 1) % NUM_PAUSE_OPTIONS;
            }
            else if (whichKey == 12) { // space
                switch (selectedOption) {
                case 0: // Resume Game
                    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);  // Game boundary
                    return; // Exit the pause menu and return to the game
                case 1: // Restart Game
                    initializeGame(); // Reset game state
                    drawSpaceship(playerX, playerY);
                    gameLoop(); // Restart game loop
                    return; // Exit pause menu
                case 2: // Exit to Menu
                    cin.sync();
                    exitToMenu = true;
                    myRect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                    myRect(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);

                    return; // Exit the pause menu and let main menu handle logic
                case 3: // Save and Exit
                    saveGameState();
                    cin.sync();
                    exitToMenu = true;
                    myRect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                    myRect(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                    // Save the current game state
                    return; // Exit to the main menu
                }
            }
        }

        Sleep(16); // Delay for smoother interaction
    }
}






// Handle input
void handleInput() {
    int whichKey;
    if (isKeyPressed(whichKey)) {

        eraseSpaceship(playerX, playerY);
        // Move left
        if (whichKey == 8 && playerX > 30) {
            playerX -= 30; // Move spaceship left
        }
        // Move up
        else if (whichKey == 9 && playerY > 30) {
            playerY -= 30; // Move spaceship up
        }
        // Move right
        else if (whichKey == 11 && playerX < SCREEN_WIDTH - 60) {
            playerX += 30; // Move spaceship right
        }
        // Move down
        else if (whichKey == 10 && playerY < SCREEN_HEIGHT - 40) {
            playerY += 30; // Move spaceship down
        }
        // Fire bullet
        else if (whichKey == 12) {
            firePlayerBullet(); // Fire the bullet
        }
        // Pause game
        else if (whichKey == 7) {
            pauseGame(); // Pause game
        }
        drawSpaceship(playerX, playerY);

    }
}

void moveAliens() {
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter % 5 != 0) return;  // Adjust speed by skipping frames

    bool hitEdge = false;


    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j]) {
                // Erase only when moving
                if (selectedAlienType == 0)
                    myEllipse(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 0, 0, 26, 0, 0, 26);
                else
                    myRect(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 0, 0, 26, 0, 0, 26);
                //adjustment of hands and legs for erasing the same as the ones drawn
                if (handslegs % 6 == 0) {
                    handschangey = -10;
                    legschangey = 0;
                    legschangex = 0;
                }
                else if (handslegs % 6 == 1) {
                    handschangey = 0;
                    legschangey = +5;
                    legschangex = -10;
                }
                else if (handslegs % 6 == 2) {
                    handschangey = -20;
                    legschangey = -5;
                    legschangex = 5;
                }
                else if (handslegs % 6 == 3) {
                    handschangey = 10;
                    legschangey = 0;
                    legschangex = 0;
                }
                else if (handslegs % 6 == 4) {
                    handschangey = 0;
                    legschangey = -5;
                    legschangex = -5;
                }
                else if (handslegs % 6 == 5) {
                    handschangey = -15;
                    legschangey = 5;
                    legschangex = 10;
                }

                //erase dynamic hands
                myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Left hand
                myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Right hand

                // erase dynamic legs
                myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26);  // Left leg
                myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26); // Right leg

                //erase dynamic hands
                myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Left hand
                myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Right hand

                // erase dynamic legs
                myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26);  // Left leg
                myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26); // Right leg
                // Move alien position
                alienY[i][j] += alienDirection * alienSpeed;
                if (alienY[i][j] <= 30 || alienY[i][j] >= SCREEN_HEIGHT - 70) {
                    hitEdge = true;
                }
            }
        }
    }
    handslegs++;

    // Handle edge collision
    if (hitEdge) {
        alienDirection = -alienDirection;
        for (int i = 0; i < ALIEN_ROWS; i++) {
            for (int j = 0; j < ALIEN_COLS; j++) {
                alienX[i][j] -= alienDrop;
            }
        }
    }
}



// Fire player bullet
void firePlayerBullet() {
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (!playerBulletActive[i]) {
            PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
            playerBulletX[i] = playerX + 75; // Start from the front of the spaceship
            playerBulletY[i] = playerY + 15;
            playerBulletActive[i] = true;
            break;
        }
    }
}

// Move player bullets
void movePlayerBullets() {
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (playerBulletActive[i]) {
            myRect(playerBulletX[i], playerBulletY[i], playerBulletX[i] + 10, playerBulletY[i] - 5, 0, 0, 26, 0, 0, 26);
            playerBulletX[i] += 15;
            myRect(playerBulletX[i], playerBulletY[i], playerBulletX[i] + 10, playerBulletY[i] - 5, 60, 179, 113, 60, 179, 113);

            if (playerBulletX[i] >= SCREEN_WIDTH - 5) {
                playerBulletActive[i] = false;
            }
        }
    }
}

void fireAlienBullet() {
    static int fireTimer = 0;
    fireTimer++;

    if (fireTimer >= 4) {
        bool alienFound = false;

        for (int r = 0; r < ALIEN_ROWS; r++) {
            for (int c = 0; c < ALIEN_COLS; c++) {
                if (aliens[r][c]) {
                    // For easy mode, any alien can fire bullet
                    if (isEasyDifficulty == true) {
                        if (rand() % 400 < 5) {
                            for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
                                if (!alienBulletActive[i]) {
                                    alienBulletX[i] = alienX[r][c] - 10;
                                    alienBulletY[i] = alienY[r][c] + 15;
                                    alienBulletActive[i] = true;
                                    alienFound = true;
                                    break;
                                }
                            }

                        }
                    }
                    else {

                        // For hard mode, only fire if the alien's y-coordinate is aligned with the spaceship's y position or close to it
                        for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
                            if (!alienBulletActive[i]) {
                                // The alien is aligned with the spaceship, so fire a bullet
                                if (alienY[r][c] <= playerY + 50 && alienY[r][c] + 30 >= playerY) {
                                    alienBulletX[i] = alienX[r][c] - 10;
                                    alienBulletY[i] = alienY[r][c] + 15;
                                    alienBulletActive[i] = true;
                                    alienFound = true;
                                    break;
                                }
                            }
                        }
                    }

                    if (alienFound) {
                        break; // Exit the loop after finding and firing from one alien
                    }
                }
            }
        }
        fireTimer = 0;
    }
}


// Move alien bullets
void moveAlienBullets() {
    for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
        if (alienBulletActive[i]) {
            eraseObject(alienBulletX[i], alienBulletY[i], alienBulletX[i] + 10, alienBulletY[i] + 5);
            alienBulletX[i] -= 10;
            myRect(alienBulletX[i], alienBulletY[i], alienBulletX[i] + 10, alienBulletY[i] + 5, 199, 21, 133, 199, 21, 133);

            if (alienBulletX[i] < 0) {
                alienBulletActive[i] = false;
                eraseObject(alienBulletX[i], alienBulletY[i], alienBulletX[i] + 10, alienBulletY[i] + 5); // Erase bullet when deactivated
            }

        }
    }
}

// Check collisions
void checkCollisions() {
    for (int b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if (playerBulletActive[b]) {
            for (int i = 0; i < ALIEN_ROWS; i++) {
                for (int j = 0; j < ALIEN_COLS; j++) {
                    if (aliens[i][j] &&
                        playerBulletX[b] >= alienX[i][j] && playerBulletX[b] <= alienX[i][j] + 30 &&
                        playerBulletY[b] >= alienY[i][j] && playerBulletY[b] <= alienY[i][j] + 30) {
                        aliens[i][j] = false;
                        playerBulletActive[b] = false;
                        myRect(playerBulletX[b], playerBulletY[b] - 5, playerBulletX[b] + 10, playerBulletY[b], 0, 0, 26, 0, 0, 26);
                        if (selectedAlienType == 0)
                            myEllipse(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 0, 0, 26, 0, 0, 26);
                        else
                            myRect(alienX[i][j], alienY[i][j], alienX[i][j] + 30, alienY[i][j] + 30, 0, 0, 26, 0, 0, 26);
                        //adjusting handslegs for collision erasing done later
                        if (handslegs % 6 == 0) {
                            handschangey = -10;
                            legschangey = 0;
                            legschangex = 0;
                        }
                        else if (handslegs % 6 == 1) {
                            handschangey = 0;
                            legschangey = +5;
                            legschangex = -10;
                        }
                        else if (handslegs % 6 == 2) {
                            handschangey = -20;
                            legschangey = -5;
                            legschangex = 5;
                        }
                        else if (handslegs % 6 == 3) {
                            handschangey = 10;
                            legschangey = 0;
                            legschangex = 0;
                        }
                        else if (handslegs % 6 == 4) {
                            handschangey = 0;
                            legschangey = -5;
                            legschangex = -5;
                        }
                        else if (handslegs % 6 == 5) {
                            handschangey = -15;
                            legschangey = 5;
                            legschangex = 10;
                        }

                        //collision erasing of hands dynamic
                        myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] - 13, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Left hand
                        myLine(alienX[i][j] + 15, alienY[i][j] + 15, alienX[i][j] + 43, alienY[i][j] + 25 + handschangey, 0, 0, 26); // Right hand

                        // collision easing of legs dynamic
                        myLine(alienX[i][j] + 5, alienY[i][j] + 30, alienX[i][j] - 5 + legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26);  // Left leg
                        myLine(alienX[i][j] + 25, alienY[i][j] + 30, alienX[i][j] + 35 - legschangex, alienY[i][j] + 40 + legschangey, 0, 0, 26); // Right leg
                        PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        score += 10;
                        break;
                    }
                }
            }
        }
    }
    for (int s = 0; s < SHIELDS; s++) {
        if (shieldVisible[s] && shieldHealth[s] > 0) {
            for (int b = 0; b < MAX_PLAYER_BULLETS; b++) {
                if (playerBulletActive[b] &&
                    playerBulletX[b] >= shieldX[s] && playerBulletX[b] <= shieldX[s] + 20 &&
                    playerBulletY[b] >= shieldY[s] && playerBulletY[b] <= shieldY[s] + 100) {
                    playerBulletActive[b] = false;
                    shieldHealth[s]--;
                    if (shieldHealth[s] <= 0) {
                        shieldVisible[s] = false; // Hide the shield
                        myRect(shieldX[s], shieldY[s], shieldX[s] + 20, shieldY[s] + 100, 0, 0, 26, 0, 0, 26); // Erase shield
                    }
                }
            }

            for (int b = 0; b < MAX_ALIEN_BULLETS; b++) {
                if (alienBulletActive[b] &&
                    alienBulletX[b] >= shieldX[s] && alienBulletX[b] <= shieldX[s] + 30 &&
                    alienBulletY[b] >= shieldY[s] && alienBulletY[b] <= shieldY[s] + 100) {
                    alienBulletActive[b] = false;
                    myRect(alienBulletX[b], alienBulletY[b], alienBulletX[b] + 10, alienBulletY[b] + 5, 0, 0, 26, 0, 0, 26);
                    shieldHealth[s]--;
                    if (shieldHealth[s] <= 0) {
                        shieldVisible[s] = false; // Hide the shield

                        myRect(shieldX[s], shieldY[s], shieldX[s] + 20, shieldY[s] + 100, 0, 0, 26, 0, 0, 26); // Erase shield
                    }
                }
            }
        }
    }

    for (int b = 0; b < MAX_ALIEN_BULLETS; b++) {
        if (alienBulletActive[b] &&
            alienBulletX[b] >= playerX && alienBulletX[b] <= playerX + 75 &&
            alienBulletY[b] >= playerY && alienBulletY[b] <= playerY + 30) {
            alienBulletActive[b] = false;
            myRect(alienBulletX[b], alienBulletY[b], alienBulletX[b] + 10, alienBulletY[b] + 5, 0, 0, 26, 0, 0, 26);
            lives--;//One life is lost by the spaceship as it just got hit by alien bullet
            if (lives <= 0) {
                gameOver(false);
            }
        }
    }
}
void checkPlayerAlienCollision() {
    // Loop through each alien
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j]) {  // Only check active aliens
                // Spaceship's rectangular area
                float spaceshipLeft = playerX;
                float spaceshipRight = playerX + 50;  // Width of spaceship
                float spaceshipTop = playerY;
                float spaceshipBottom = playerY + 25; // Height of spaceship

                // Alien's rectangular area
                float alienLeft = alienX[i][j];
                float alienRight = alienX[i][j] + 30;  // Width of alien
                float alienTop = alienY[i][j];
                float alienBottom = alienY[i][j] + 30; // Height of alien

                // Check for overlap (collision)
                if (spaceshipRight + 40 > alienLeft && spaceshipLeft < alienRight &&
                    spaceshipBottom > alienTop && spaceshipTop < alienBottom) {
                    // Collision detected
                    lives--; // Trigger one life lost
                    Sleep(1000);//waiting time for spaceship to get away
                    if (lives == 0)
                    {
                        gameOver(false);//after three lives lost trigger game over with a lose
                    }


                    return;  // Exit the function as the game is over
                }
            }
        }

    }
}



// Game over
void gameOver(bool win) {
    // Clear the screen
    myRect(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT, 255, 0, 56, 0, 0, 26);
    //erase scores and lives separately as they are out of the boundary 

    // Display game over or victory message
    if (win) {
        drawText(60, 750, 300, 1, 255, 72, "YOU WIN!");
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC); //winning text and music
    }
    else {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
        drawText(60, 700, 300, 220, 20, 60, "WOMP WOMP!");//losing text and music
    }

    updateHighScores(score);
    // Display options for restarting or going to the menu
    drawText(20, 700, 500, 203, 0, 245, "   Press SHIFT to RESTART.");
    drawText(20, 650, 600, 203, 0, 245, "Press ESCAPE to return to the MENU.");

    int whichKey;
    while (true) {
        if (isKeyPressed(whichKey)) {
            if (whichKey == 6) { // Shift key
                myRect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                myRect(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                saveHighScore();
                initializeGame();// Restart the game
                drawSpaceship(playerX, playerY);
                gameLoop();        // Start the game loop
                return;            // Exit the function after restarting
            }
            else if (whichKey == 7) {
                myRect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_X + BOX_WIDTH, SCORE_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                myRect(LIVES_BOX_X, LIVES_BOX_Y, LIVES_BOX_X + BOX_WIDTH, LIVES_BOX_Y + BOX_HEIGHT, 0, 0, 0, 0, 0, 0);
                saveHighScore();
                PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
                exitToMenu = true;
                cin.sync();
                return;  // Exit to the menu
            }
        }
        Sleep(16);  // Add a small delay to prevent CPU overuse
    }
}



// Game loop


void gameLoop() {
    while (lives > 0 && !exitToMenu) { // Stop the game loop if exitToMenu is true  or lives are less than 0

        drawGame();
        handleInput();
        movePlayerBullets();
        fireAlienBullet();
        moveAlienBullets();
        moveAliens();

        checkCollisions();
        checkPlayerAlienCollision();
        checkAliensLeftBoundaryCollision();

        if (allAliensDestroyed()) {
            gameOver(true);
            break;
        }


    }

    if (exitToMenu) {
        cin.sync();

        return; // Exit to main menu
    }

    saveHighScore(); // Save score if the game ends normally
}


// Main function
int main() {
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC );
    srand(static_cast<unsigned>(time(0)));  // Seed random number generator
    loadHighScore();  // Load the high score at the start of the game

    while (true) {
        exitToMenu = false;
        drawMenu();  // Draw the menu
        handleMenuInput();
        // Handle key press input for menu navigation and selection
        Sleep(16);
        // Small delay for smoother menu interaction
    }

    return 0;
}


// Check if all aliens are destroyed
bool allAliensDestroyed() {
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j]) {
                return false;  // If any alien is still alive, return false
            }
        }
    }
    return true;  // All aliens are destroyed
}

// Save high score to a file
void saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            file << highScores[i] << std::endl;  // Save the highest scores to file
        }
        file.close();
    }
    else {
        std::cerr << "Error: Unable to save high scores." << std::endl;
    }
}


// Load high score from file
void loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            file >> highScores[i];  // Read the high scores from file
        }
        file.close();
    }
    else {
        for (int i = 0; i < 5; i++) {
            highScores[i] = 0;  // If file doesn't exist, set high scores to 0
        }
    }
}




//  game state to a file
void saveGameState() {
    std::ofstream file("gamestate.txt");
    if (file.is_open()) {
        // Save player position, score, lives, selected alien types and spacetypes as well as the difficulty level
        file << playerX << " " << playerY << std::endl;
        file << score << " " << lives << std::endl;
        file << selectedAlienType << std::endl;
        file << selectedSpaceshipType << std::endl;
        file << isEasyDifficulty << std::endl;
        // Save aliens' states and positions
        for (int i = 0; i < ALIEN_ROWS; i++) {
            for (int j = 0; j < ALIEN_COLS; j++) {
                file << aliens[i][j] << " " << alienX[i][j] << " " << alienY[i][j] << std::endl;
            }
        }

        // Save shields' positions and health as well as if they should be visible or not
        for (int i = 0; i < SHIELDS; i++) {
            file << shieldX[i] << " " << shieldY[i] << " " << shieldHealth[i] << " " << shieldVisible[i] << std::endl;
        }

        // Save player bullets' positions and states
        for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
            file << playerBulletActive[i] << " " << playerBulletX[i] << " " << playerBulletY[i] << std::endl;
        }

        // Save alien bullets' positions and states
        for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
            file << alienBulletActive[i] << " " << alienBulletX[i] << " " << alienBulletY[i] << std::endl;
        }

        file.close();
    }
}


// Load game state from file
void loadGameState() {
    std::ifstream file("gamestate.txt");
    if (file.is_open()) {
        // Load player position, score, lives, selected alien types and spacetypes as well as the difficulty level
        file >> playerX >> playerY;
        file >> score >> lives;
        file >> selectedAlienType;
        file >> selectedSpaceshipType;
        file >> isEasyDifficulty;
        // Load aliens' states and positions
        for (int i = 0; i < ALIEN_ROWS; i++) {
            for (int j = 0; j < ALIEN_COLS; j++) {
                file >> aliens[i][j] >> alienX[i][j] >> alienY[i][j];
            }
        }

        // Load shields' positions and health as well as if they should be visible or not
        for (int i = 0; i < SHIELDS; i++) {
            file >> shieldX[i] >> shieldY[i] >> shieldHealth[i] >> shieldVisible[i];
        }

        // Load player bullets' positions and states
        for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
            file >> playerBulletActive[i] >> playerBulletX[i] >> playerBulletY[i];
        }

        // Load alien bullets' positions and states
        for (int i = 0; i < MAX_ALIEN_BULLETS; i++) {
            file >> alienBulletActive[i] >> alienBulletX[i] >> alienBulletY[i];
        }

        file.close();
    }
}