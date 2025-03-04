// Polygon Clipping Algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Define the clipping window boundaries
#define X_MIN 100
#define X_MAX 400
#define Y_MIN 100
#define Y_MAX 300
// Structure to represent a point
typedef struct {
    int x, y;
} Point;
// Function to clip the polygon against a single edge of the clipping window
void clipPolygon(Point input[], int inputSize, Point output[], int *outputSize, int edge) {
    *outputSize = 0; // Initialize the output polygon size
    Point prevPoint = input[inputSize - 1]; // Start with the last point
    for (int i = 0; i < inputSize; i++) {
        Point currPoint = input[i];
        // Calculate the position of the current and previous points relative to the edge
        int currInside = 0, prevInside = 0;
        switch (edge) {
            case 0: // Left edge
                currInside = (currPoint.x >= X_MIN);
                prevInside = (prevPoint.x >= X_MIN);
                break;
            case 1: // Right edge
                currInside = (currPoint.x <= X_MAX);
                prevInside = (prevPoint.x <= X_MAX);
                break;
            case 2: // Bottom edge
                currInside = (currPoint.y >= Y_MIN);
                prevInside = (prevPoint.y >= Y_MIN);
                break;
            case 3: // Top edge
                currInside = (currPoint.y <= Y_MAX);
                prevInside = (prevPoint.y <= Y_MAX);
                break;
        }
        // If the current point is inside the edge, add it to the output
        if (currInside) {
            output[(*outputSize)++] = currPoint;
        }
        // If the line crosses the edge, calculate the intersection and add it to the output
        if (currInside != prevInside) {
            Point intersect;
            if (edge == 0 || edge == 1) { // Left or right edge
                float slope = (float)(currPoint.y - prevPoint.y) / (currPoint.x - prevPoint.x);
                intersect.y = prevPoint.y + slope * ((edge == 0 ? X_MIN : X_MAX) - prevPoint.x);
                intersect.x = (edge == 0) ? X_MIN : X_MAX;
            } else { // Bottom or top edge
                float slope = (float)(currPoint.x - prevPoint.x) / (currPoint.y - prevPoint.y);
                intersect.x = prevPoint.x + slope * ((edge == 2 ? Y_MIN : Y_MAX) - prevPoint.y);
                intersect.y = (edge == 2) ? Y_MIN : Y_MAX;
            }
            output[(*outputSize)++] = intersect;
        }
        prevPoint = currPoint; // Move to the next edge
    }
}
// Function to draw a polygon
void drawPolygon(Point polygon[], int size) {
    for (int i = 0; i < size; i++) {
        int next = (i + 1) % size;
        line(polygon[i].x, polygon[i].y, polygon[next].x, polygon[next].y);
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Define the input polygon vertices
    Point inputPolygon[] = {{50, 150}, {200, 50}, {350, 150}, {350, 250}, {200, 350}, {50, 250}};
    int inputSize = sizeof(inputPolygon) / sizeof(inputPolygon[0]);
    // Draw the clipping window
    rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);
    // Draw the original polygon
    setcolor(WHITE);
    drawPolygon(inputPolygon, inputSize);
    // Clip the polygon against each edge of the clipping window
    Point outputPolygon[100]; // Temporary storage for clipped polygon
    int outputSize;
    for (int edge = 0; edge < 4; edge++) {
        clipPolygon(inputPolygon, inputSize, outputPolygon, &outputSize, edge);
        inputSize = outputSize; // Update input polygon for the next edge
        for (int i = 0; i < outputSize; i++) {
            inputPolygon[i] = outputPolygon[i];
        }
    }
    // Draw the clipped polygon
    setcolor(RED);
    drawPolygon(inputPolygon, inputSize);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
