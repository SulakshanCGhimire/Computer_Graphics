// Boundary-fill 8 connected
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to perform 8-connected boundary fill
void boundaryFill8(int x, int y, int fillColor, int boundaryColor) {
    // Get the color of the current pixel
    int currentColor = getpixel(x, y);
    // If the current pixel is not the boundary color and not the fill color, fill it
    if (currentColor != boundaryColor && currentColor != fillColor) {
        putpixel(x, y, fillColor); // Fill the pixel with the fill color
        // Recursively fill the 8-connected neighbors
        boundaryFill8(x + 1, y, fillColor, boundaryColor);     // Right
        boundaryFill8(x - 1, y, fillColor, boundaryColor);     // Left
        boundaryFill8(x, y + 1, fillColor, boundaryColor);     // Bottom
        boundaryFill8(x, y - 1, fillColor, boundaryColor);     // Top
        boundaryFill8(x + 1, y + 1, fillColor, boundaryColor); // Bottom-Right
        boundaryFill8(x - 1, y + 1, fillColor, boundaryColor); // Bottom-Left
        boundaryFill8(x + 1, y - 1, fillColor, boundaryColor); // Top-Right
        boundaryFill8(x - 1, y - 1, fillColor, boundaryColor); // Top-Left
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw a rectangle as the boundary
    rectangle(100, 100, 300, 300);
    // Perform boundary fill starting from a seed point inside the rectangle
    boundaryFill8(150, 150, RED, WHITE);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
