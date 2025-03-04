// Z-buffer (Depth Buffer) Algorithm 
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
#include <limits.h>   // Include limits.h for INT_MAX
// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// Depth buffer and color buffer
int zBuffer[SCREEN_WIDTH][SCREEN_HEIGHT]; // Depth buffer (z-buffer)
int colorBuffer[SCREEN_WIDTH][SCREEN_HEIGHT]; // Color buffer
// Function to initialize the depth buffer and color buffer
void initializeBuffers() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            zBuffer[x][y] = INT_MAX; // Initialize depth buffer to maximum depth
            colorBuffer[x][y] = BLACK; // Initialize color buffer to black
        }
    }
}
// Function to draw a pixel using the depth buffer algorithm
void drawPixel(int x, int y, int z, int color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        if (z < zBuffer[x][y]) { // Check if the fragment is closer to the viewer
            zBuffer[x][y] = z; // Update depth buffer
            colorBuffer[x][y] = color; // Update color buffer
        }
    }
}
// Function to render the color buffer to the screen
void renderColorBuffer() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            putpixel(x, y, colorBuffer[x][y]); // Draw the pixel
        }
    }
}
// Function to draw a 3D triangle using the depth buffer algorithm
void drawTriangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int color) {
    // Calculate the bounding box of the triangle
    int minX = (x1 < x2) ? (x1 < x3 ? x1 : x3) : (x2 < x3 ? x2 : x3);
    int maxX = (x1 > x2) ? (x1 > x3 ? x1 : x3) : (x2 > x3 ? x2 : x3);
    int minY = (y1 < y2) ? (y1 < y3 ? y1 : y3) : (y2 < y3 ? y2 : y3);
    int maxY = (y1 > y2) ? (y1 > y3 ? y1 : y3) : (y2 > y3 ? y2 : y3);
    // Iterate over the bounding box
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            // Calculate barycentric coordinates
            float denominator = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
            if (denominator == 0) continue; // Avoid division by zero
            float alpha = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denominator;
            float beta = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denominator;
            float gamma = 1 - alpha - beta;
            // Check if the point is inside the triangle
            if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                // Interpolate the depth (z-coordinate)
                int z = (int)(alpha * z1 + beta * z2 + gamma * z3);
                // Draw the pixel using the depth buffer algorithm
                drawPixel(x, y, z, color);
            }
        }
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, (char*)""); // Cast the string literal to char*
    if (graphresult() != grOk) {
        printf("Graphics initialization failed!\n");
        return 1; // Exit the program if initialization fails
    }
    // Initialize the depth buffer and color buffer
    initializeBuffers();
    // Define the vertices of a 3D triangle
    int x1 = 100, y1 = 100, z1 = 100;
    int x2 = 300, y2 = 100, z2 = 200;
    int x3 = 200, y3 = 300, z3 = 150;
    // Draw the triangle using the depth buffer algorithm
    drawTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, RED);
    // Render the color buffer to the screen
    renderColorBuffer();
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
