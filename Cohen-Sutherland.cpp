// Cohen-Sutherland line clipping algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Define region codes for the Cohen-Sutherland algorithm
#define INSIDE 0    // 0000
#define LEFT 1      // 0001
#define RIGHT 2     // 0010
#define BOTTOM 4    // 0100
#define TOP 8       // 1000
// Define the clipping window boundaries
#define X_MIN 100
#define X_MAX 400
#define Y_MIN 100
#define Y_MAX 300
// Function to compute the region code for a point (x, y)
int computeRegionCode(int x, int y) {
    int code = INSIDE;
    if (x < X_MIN) code |= LEFT;       // Left of the window
    else if (x > X_MAX) code |= RIGHT; // Right of the window
    if (y < Y_MIN) code |= BOTTOM;     // Below the window
    else if (y > Y_MAX) code |= TOP;   // Above the window
    return code;
}
// Function to clip a line using the Cohen-Sutherland algorithm
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1, code2; // Region codes for the endpoints
    int accept = 0;   // Flag to indicate if the line is accepted
    while (1) {
        // Compute region codes for the endpoints
        code1 = computeRegionCode(x1, y1);
        code2 = computeRegionCode(x2, y2);
        if (code1 == 0 && code2 == 0) {
            // Both endpoints are inside the window
            accept = 1;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside the same region (e.g., both to the left)
            break;
        } else {
            // Line is partially inside the window
            int x, y;
            int codeOut = code1 ? code1 : code2; // Choose the endpoint outside the window
            // Find the intersection point
            if (codeOut & TOP) {
                // Point is above the window
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codeOut & BOTTOM) {
                // Point is below the window
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codeOut & RIGHT) {
                // Point is to the right of the window
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (codeOut & LEFT) {
                // Point is to the left of the window
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }
            // Update the endpoint outside the window
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2);
            }
        }
    }
    // If the line is accepted, draw the clipped line
    if (accept) {
        setcolor(RED);
        line(x1, y1, x2, y2);
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw the clipping window
    rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);
    // Define the line endpoints
    int x1 = 50, y1 = 150; // Start point
    int x2 = 450, y2 = 250; // End point
    // Draw the original line
    setcolor(WHITE);
    line(x1, y1, x2, y2);
    // Clip and draw the line using the Cohen-Sutherland algorithm
    cohenSutherlandClip(x1, y1, x2, y2);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
