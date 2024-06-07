#include <GL/glut.h>
#include <cmath>
#include <cstring>
# define PI 3.14159265358979323846

// Define initial positions and other constants
float flagWave = 0.0f;

// Define colors
GLfloat green[] = { 0.0, 0.5, 0.0 };
GLfloat red[] = { 0.75, 0.0, 0.0 };
GLfloat grey[] = { 0.4, 0.4, 0.4 };

// Function prototypes
void display();
void reshape(int, int);
void timer(int);
void init();
void drawSchool();
void drawField();
void drawRoad();
void drawSky();
void drawSun();
void drawClouds();
void cloud1();
void cloud2();
void cloud3();
void drawBird();
void animateBird();
void animateClouds();
void drawFlower(float, float);
void drawBoy();
void drawNewFlower(float, float);
void drawBench();
void drawCar();


void drawRectangle(float x, float y, float width, float height, GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a circle
void drawCircle(float cx, float cy, float radius, int segments, GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw the flag of Bangladesh with a waving effect
void drawFlag() {

    float waveAmplitude = 0.02f;
    float waveFrequency = 10.0f;
    glColor3fv(green);
    glBegin(GL_QUADS);
    for (int i = 0; i < 100; i++) {
        float x = -0.4f + i * 0.004f; // Adjusted x position
        float y = waveAmplitude * sin(waveFrequency * x + flagWave) + 0.3f; // Adjusted y position
        glVertex2f(x, y);
        glVertex2f(x + 0.004f, y);
        glVertex2f(x + 0.004f, y + 0.2f);
        glVertex2f(x, y + 0.2f);
    }
    glEnd();
    drawCircle(-0.2f, 0.4f, 0.05f, 50, red); // Adjusted flag circle position
}

// Function to draw the flag pole
void drawPole() {
    drawRectangle(-0.41f, -0.5f, 0.02f, 1.0f, grey); // Adjusted flag pole position
}


// Global variables for animation
float cloudPosition1 = -1.0f;
float cloudPosition2 = -0.5f;
float cloudPosition3 = 0.0f;
GLfloat speed = 0.004f;
float birdPositionX = -1.0f, birdPositionY = 0.5f;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(850, 600);
    glutCreateWindow("School Scene with Flag, Field, Road, Clouds, Bird, and Sun");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Set sky color
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the flag pole and flag
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    drawPole();
    drawFlag();
    glPopMatrix();

    drawSky();
    drawField();
    drawRoad();
    drawSchool();
    drawSun(); // Draw the sun
    drawClouds(); // Draw the clouds
    drawBird(); // Draw the bird
    drawBoy(); // Draw the boy


    // to set the bench to the right
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    drawBench();
    glPopMatrix();

    // adding the car on the left
    glPushMatrix();
    glTranslatef(-0.8f, 0.0f, 0.0f);
    drawCar();
    glPopMatrix();

    // Add  flowers around the school
    drawFlower(0.8f, -0.4f); // Flower plant 1, adjusted to touch the field
    drawFlower(0.9f, -0.4f); // Flower plant 2, adjusted to touch the field

    // Add new rectangular-petal flowers
    drawNewFlower(-0.8f, -0.4f); // New flower 1, adjusted to touch the field
    drawNewFlower(-0.7f, -0.4f); // New flower 2, adjusted to touch the field

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    // Update animations
    animateClouds(); // Animate the clouds
    animateBird(); // Animate the bird

    flagWave += 0.1f;
    if (flagWave > 2 * M_PI) {
        flagWave -= 2 * M_PI;
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0); // 60 FPS
}

void drawSchool() {
    // Draw school building
    glColor3f(0.7f, 0.3f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(0.6f, -0.2f);
    glVertex2f(0.6f, 0.3f);
    glVertex2f(-0.6f, 0.3f);
    glEnd();

    // Draw the roof
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(0.65f, 0.3f);
    glVertex2f(0.0f, 0.6f);
    glEnd();

    // Draw the door
    glColor3f(0.5f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, -0.2f);
    glVertex2f(0.1f, -0.2f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glEnd();

    // Draw windows
    glColor3f(0.8f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.3f, 0.2f);
    glVertex2f(-0.5f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.5f, 0.2f);
    glVertex2f(0.3f, 0.2f);
    glEnd();

    // Draw the school name
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.25f, 0.4f);
    const char* name = "RMSTU High School";
    for (const char* c = name; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }


    drawFlower(0.8f, -0.15f); // Flower plant 1
    drawFlower(0.85f, -0.05f); // Flower plant 2
    drawFlower(0.9f, -0.15f); // Flower plant 3


    // Draw a  tree beside the school
    glColor3f(0.6f, 0.3f, 0.1f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(0.7f, -0.2f);
    glVertex2f(0.78f, -0.2f);
    glVertex2f(0.78f, 0.3f);
    glVertex2f(0.7f, 0.3f);
    glEnd();

    glColor3f(0.0f, 0.7f, 0.1f); // Green color for the foliage
    glBegin(GL_TRIANGLES);
    glVertex2f(0.55f, 0.3f); // Adjusted  foliage
    glVertex2f(0.93f, 0.3f); // Adjusted  foliage
    glVertex2f(0.74f, 0.7f);
    glEnd();

}

void drawField() {
    // Draw a green field with grass
    glColor3f(0.0f, 0.5f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(-1.0f, -0.2f);
    glEnd();


    // Draw some grass
    glColor3f(0.0f, 0.8f, 0.0f);
    for (float x = -0.9f; x <= 0.9f; x += 0.1f) {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, -0.2f);
        glVertex2f(x + 0.05f, -0.2f);
        glVertex2f(x + 0.025f, -0.1f);
        glEnd();
    }

    // Draw flowers
    drawFlower(-0.8f, -0.15f); // Example flower position
    drawFlower(-0.6f, -0.1f); // Example flower position
    drawFlower(-0.4f, -0.12f); // Example flower position
    drawFlower(-0.2f, -0.15f); // Example flower position
    drawFlower(0.2f, -0.1f); // Example flower position
    drawFlower(0.4f, -0.15f); // Example flower position
    drawFlower(0.6f, -0.12f); // Example flower position

}

void drawRoad() {
    // Draw a road
    glColor3f(0.9f, 0.4f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, -1.0f);
    glVertex2f(0.15f, -1.0f);
    glVertex2f(0.15f, -0.2f);
    glVertex2f(-0.15f, -0.2f);
    glEnd();
}

void drawSky() {
    // Sky is already set as background color in init
}

void drawSun() {
    // Draw the sun
    glColor3f(1.0f, 0.7f, 0.0f); // orange color for the sun
    float cx = 0.8f; // Center x of the sun
    float cy = 0.8f; // Center y of the sun
    float radius = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawClouds() {
    // Draw clouds with animation
    glPushMatrix();
    glTranslatef(cloudPosition1, 0.0f, 0.0f);
    cloud1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cloudPosition2, 0.0f, 0.0f);
    cloud2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cloudPosition3, 0.0f, 0.0f);
    cloud3();
    glPopMatrix();
}

void drawBird() {

    // Draw a bird with animation
    glColor3f(0.4f, 0.4f, 0.4f);

    // Body
    glBegin(GL_POLYGON);
    glVertex2f(birdPositionX, birdPositionY);
    glVertex2f(birdPositionX + 0.05f, birdPositionY + 0.02f);
    glVertex2f(birdPositionX + 0.10f, birdPositionY);
    glVertex2f(birdPositionX + 0.05f, birdPositionY - 0.02f);
    glEnd();

    // Left wing
    glBegin(GL_TRIANGLES);
    glVertex2f(birdPositionX + 0.05f, birdPositionY + 0.02f);
    glVertex2f(birdPositionX + 0.07f, birdPositionY + 0.05f);
    glVertex2f(birdPositionX + 0.10f, birdPositionY + 0.02f);
    glEnd();

    // Right wing
    glBegin(GL_TRIANGLES);
    glVertex2f(birdPositionX + 0.05f, birdPositionY - 0.02f);
    glVertex2f(birdPositionX + 0.07f, birdPositionY - 0.05f);
    glVertex2f(birdPositionX + 0.10f, birdPositionY - 0.02f);
    glEnd();
}

void animateClouds() {
    cloudPosition1 += speed;
    cloudPosition2 += speed;
    cloudPosition3 += speed;
    if (cloudPosition1 > 1.5f) cloudPosition1 = -1.5f;
    if (cloudPosition2 > 1.5f) cloudPosition2 = -1.5f;
    if (cloudPosition3 > 1.5f) cloudPosition3 = -1.5f;
}

void animateBird() {
    // bird's x position to move left
    birdPositionX -= 0.005f;

    // set bird's position if it moves off the left side of the screen
    if (birdPositionX < -1.1f) {
        birdPositionX = 1.1f;  // Start from the right side of the screen again
    }

    // bird's y position with a sinusoidal pattern
    birdPositionY = 0.7f + 0.05f * sin(5 * birdPositionX);
}



void cloud1() {
    // Draw a cloud (distinct shape 1)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.1f, 0.9f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.1f + x, 0.9f + y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.15f, 0.85f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.15f + x, 0.85f + y);
    }
    glEnd();
}
void cloud2() {
    // Draw a cloud (distinct shape 2)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.1f, 0.8f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.1f + x, 0.8f + y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.15f, 0.75f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.15f + x, 0.75f + y);
    }
    glEnd();
}

void cloud3() {
    // Draw a cloud (distinct shape 3)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.1f, 0.7f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.1f + x, 0.7f + y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.15f, 0.65f);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.1415926f / 20;
        float x = 0.1f * cosf(angle);
        float y = 0.05f * sinf(angle);
        glVertex2f(0.15f + x, 0.65f + y);
    }
    glEnd();
}


void drawFlower(float x, float y) {
    // Draw a flower at the specified position (x, y)

    // Flower stem
    glColor3f(1.0f, 0.5f, 1.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(x, y); // Bottom of the stem
    glVertex2f(x, y + 0.1f); // Top of the stem
    glEnd();

    // Flower petals
    glColor3f(1.0f, 1.0f, 0.0f); // yellow color for petals
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float angle = i * 3.14159f / 180;
        float petalX = x + 0.05f * cos(angle);
        float petalY = y + 0.05f * sin(angle);
        glVertex2f(petalX, petalY);
    }
    glEnd();

    // Flower center
    glColor3f(1.0f, 0.0f, 0.0f); // orange color for center
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 0.05f); // Center of the flower
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.14159f / 180;
        float centerRadius = 0.015f;
        float centerX = x + centerRadius * cos(angle);
        float centerY = y + 0.05f + centerRadius * sin(angle);
        glVertex2f(centerX, centerY);
    }
    glEnd();
}

void drawBoy() {
    // Draw the boy
    glColor3f(0.0f, 0.9f, 0.9f); // Black color for the boy
    // Body
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, -0.2f);
    glVertex2f(0.05f, -0.2f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(-0.05f, -0.05f);
    glEnd();

    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // Skin color for the head
    float headRadius = 0.025f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, -0.025f); // Center of the head
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.14159f / 180;
        float x = headRadius * cos(angle);
        float y = headRadius * sin(angle);
        glVertex2f(x, y - 0.025f);
    }
    glEnd();

    // Arms
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the arms
    glBegin(GL_LINES);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(-0.1f, -0.15f);
    glVertex2f(0.05f, -0.1f);
    glVertex2f(0.1f, -0.15f);
    glEnd();

    // Legs
    glBegin(GL_LINES);
    glVertex2f(-0.05f, -0.2f);
    glVertex2f(-0.05f, -0.3f);
    glVertex2f(0.05f, -0.2f);
    glVertex2f(0.05f, -0.3f);
    glEnd();
}

// Function to draw a new flower shape with rectangular petals
void drawNewFlower(float x, float y) {
    // Draw the stem
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + 0.1f);
    glEnd();

    // Draw the rectangular petals
    drawRectangle(x - 0.01f, y + 0.09f, 0.02f, 0.03f, red);
    drawRectangle(x - 0.03f, y + 0.07f, 0.02f, 0.03f, red);
    drawRectangle(x + 0.01f, y + 0.07f, 0.02f, 0.03f, red);
    drawRectangle(x - 0.03f, y + 0.11f, 0.02f, 0.03f, red);
    drawRectangle(x + 0.01f, y + 0.11f, 0.02f, 0.03f, red);

    // Draw the center of the flower
    drawCircle(x, y + 0.1f, 0.01f, 20, green);
}
void drawBench() {
    // Draw the seat of the bench
    drawRectangle(-0.3f, -0.6f, 0.6f, 0.05f, grey);

    // Draw the backrest of the bench
    drawRectangle(-0.3f, -0.55f, 0.6f, 0.05f, grey);

    // Draw the legs of the bench
    drawRectangle(-0.3f, -0.7f, 0.05f, 0.1f, grey);
    drawRectangle(0.25f, -0.7f, 0.05f, 0.1f, grey);
}



void drawCar() {
    // Car wheels
    float wheelColor[3] = { 0.0f, 0.0f, 0.0f }; // Black color
    drawRectangle(-0.12f, -0.72f, 0.06f, 0.06f, wheelColor); // Left wheel
    drawRectangle(0.06f, -0.72f, 0.06f, 0.06f, wheelColor);  // Right wheel

    // Car body
    float carBodyColor[3] = { 0.0f, 0.0f, 1.0f }; // Blue color
    drawRectangle(-0.15f, -0.65f, 0.3f, 0.1f, carBodyColor);

    // Car roof
    float carRoofColor[3] = { 0.0f, 0.0f, 0.5f }; // Darker blue color
    drawRectangle(-0.1f, -0.55f, 0.2f, 0.05f, carRoofColor);
}

