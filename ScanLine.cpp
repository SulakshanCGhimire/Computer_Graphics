// Scan line Method
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Structure to represent an edge
typedef struct {
    int ymax;  // Maximum y-coordinate of the edge
    float x;   // Current x-coordinate of the edge
    float slope; // Slope of the edge (1/m)
} Edge;
// Function to initialize the Edge Table (ET)
void initEdgeTable(Edge ET[][10], int poly[][2], int n) {
    for (int i = 0; i < n; i++) {
        int x1 = poly[i][0], y1 = poly[i][1];
        int x2 = poly[(i + 1) % n][0], y2 = poly[(i + 1) % n][1];
        if (y1 != y2) { // Ignore horizontal edges
            Edge e;
            e.ymax = (y1 > y2) ? y1 : y2;
            e.x = (y1 > y2) ? x2 : x1;
            e.slope = (float)(x2 - x1) / (y2 - y1);
            int index = (y1 < y2) ? y1 : y2;
            for (int j = 0; j < 10; j++) {
                if (ET[index][j].ymax == 0) {
                    ET[index][j] = e;
                    break;
                }
            }
        }
    }
}
// Function to fill the polygon using the Scan Line Algorithm
void scanLineFill(int poly[][2], int n, int color) {
    Edge ET[480][10] = {0}; // Edge Table (assuming max height of 480)
    initEdgeTable(ET, poly, n);
    // Active Edge List (AEL)
    Edge AEL[100];
    int AELsize = 0;
    // Iterate through each scan line
    for (int y = 0; y < 480; y++) {
        // Add edges from ET to AEL
        for (int i = 0; i < 10; i++) {
            if (ET[y][i].ymax != 0) {
                AEL[AELsize++] = ET[y][i];
            }
        }
        // Sort AEL by x-coordinate
        for (int i = 0; i < AELsize - 1; i++) {
            for (int j = i + 1; j < AELsize; j++) {
                if (AEL[i].x > AEL[j].x) {
                    Edge temp = AEL[i];
                    AEL[i] = AEL[j];
                    AEL[j] = temp;
                }
            }
        }
        // Fill pixels between pairs of intersections
        for (int i = 0; i < AELsize; i += 2) {
            int x1 = (int)AEL[i].x;
            int x2 = (int)AEL[i + 1].x;
            for (int x = x1; x <= x2; x++) {
                putpixel(x, y, color);
            }
        }
        // Remove edges from AEL whose ymax == y
        int j = 0;
        for (int i = 0; i < AELsize; i++) {
            if (AEL[i].ymax != y) {
                AEL[j++] = AEL[i];
            }
        }
        AELsize = j;
        // Update x-coordinates in AEL for the next scan line
        for (int i = 0; i < AELsize; i++) {
            AEL[i].x += AEL[i].slope;
        }
    }
}
// Function to draw a polygon
void drawPolygon(int poly[][2], int n, int color) {
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        line(poly[i][0], poly[i][1], poly[next][0], poly[next][1]);
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
    // Define the polygon vertices (example: a hexagon)
    int poly[][2] = {{200, 100}, {300, 150}, {300, 250}, {200, 300}, {100, 250}, {100, 150}};
    int n = sizeof(poly) / sizeof(poly[0]);
    // Draw the polygon outline
    setcolor(WHITE);
    drawPolygon(poly, n, WHITE);
    // Fill the polygon using the Scan Line Algorithm
    scanLineFill(poly, n, RED);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
