// A-buffer 
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
#include <stdlib.h>   // Include standard library for dynamic memory allocation
// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// Structure to represent a surface fragment
typedef struct Fragment {
    int z;          // Depth of the fragment
    int color;      // Color of the fragment
    struct Fragment* next; // Pointer to the next fragment in the list
} Fragment;
// A-Buffer: Array of linked lists
Fragment* aBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
// Function to initialize the A-Buffer
void initializeABuffer() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            aBuffer[x][y] = NULL; // Initialize each pixel's fragment list to NULL
        }
    }
}
// Function to add a fragment to the A-Buffer
void addFragment(int x, int y, int z, int color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        // Create a new fragment
        Fragment* newFragment = (Fragment*)malloc(sizeof(Fragment));
        newFragment->z = z;
        newFragment->color = color;
        newFragment->next = NULL;
        // Insert the fragment into the A-Buffer
        if (aBuffer[x][y] == NULL) {
            aBuffer[x][y] = newFragment; // First fragment in the list
        } else {
            // Insert the fragment in sorted order (front-to-back)
            Fragment* current = aBuffer[x][y];
            Fragment* previous = NULL;
            while (current != NULL && current->z < z) {
                previous = current;
                current = current->next;
            }
            if (previous == NULL) {
                newFragment->next = aBuffer[x][y];
                aBuffer[x][y] = newFragment; // Insert at the beginning
            } else {
                newFragment->next = current;
                previous->next = newFragment; // Insert in the middle or end
            }
        }
    }
}
// Function to render the A-Buffer to the screen
void renderABuffer() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            if (aBuffer[x][y] != NULL) {
                // Use the color of the closest fragment (first in the list)
                putpixel(x, y, aBuffer[x][y]->color);
            }
        }
    }
}
// Function to draw a 3D triangle using the A-Buffer algorithm
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
                // Add the fragment to the A-Buffer
                addFragment(x, y, z, color);
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
    // Initialize the A-Buffer
    initializeABuffer();
    // Define the vertices of a 3D triangle
    int x1 = 100, y1 = 100, z1 = 100;
    int x2 = 300, y2 = 100, z2 = 200;
    int x3 = 200, y3 = 300, z3 = 150;
    // Draw the triangle using the A-Buffer algorithm
    drawTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, RED);
    // Render the A-Buffer to the screen
    renderABuffer();
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
