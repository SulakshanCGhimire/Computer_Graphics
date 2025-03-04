// Bresenham's line drawing algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to draw a line using Bresenham's algorithm
void drawLineBresenham(int x0, int y0, int x1, int y1, int color) {
    int dx, dy;       // Differences in x and y
    int p;            // Decision parameter
    int x, y;         // Current pixel coordinates
    int xIncrement, yIncrement;
    // Calculate the absolute differences
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    // Determine the direction of increment
    xIncrement = (x0 < x1) ? 1 : -1;
    yIncrement = (y0 < y1) ? 1 : -1;
    // Initialize the starting point
    x = x0;
    y = y0;
    // Plot the first pixel
    putpixel(x, y, color);
    // For slope < 1
    if (dx > dy) {
        p = 2 * dy - dx; // Initial decision parameter
        for (int i = 0; i < dx; i++) {
            x += xIncrement; // Increment x
            if (p < 0) {
                p += 2 * dy; // Update decision parameter
            } else {
                y += yIncrement; // Increment y
                p += 2 * (dy - dx); // Update decision parameter
            }
            putpixel(x, y, color); // Plot the pixel
        }
    }
    // For slope >= 1
    else {
        p = 2 * dx - dy; // Initial decision parameter
        for (int i = 0; i < dy; i++) {
            y += yIncrement; // Increment y
            if (p < 0) {
                p += 2 * dx; // Update decision parameter
            } else {
                x += xIncrement; // Increment x
                p += 2 * (dx - dy); // Update decision parameter
            }
            putpixel(x, y, color); // Plot the pixel
        }
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    int x0 = 100, y0 = 200; // Start point of the line
    int x1 = 500, y1 = 300; // End point of the line
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw the line using Bresenham's algorithm
    drawLineBresenham(x0, y0, x1, y1, RED);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
