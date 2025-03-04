// Basic 2D transformation
#include <graphics.h> // For graphical functions like line(), circle(), etc.
#include <stdio.h>    // For standard input/output functions like printf(), scanf()
#include <conio.h>    // For console input/output functions like getch()
#include <math.h>     // For mathematical functions like sin(), cos()
int main() {
    int gm, gd = DETECT, midx, midy, c;
    float x1, x2, x3, y1, y2, y3; // Original triangle coordinates
    float x11, x22, x33, y11, y22, y33; // Transformed triangle coordinates
    float sfx, sfy, tpx, tpy, ang, t, a, b;
    // Initialize graphics mode
    initgraph(&gd, &gm, "..\\bgi");
    // Get the center of the screen
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    // Draw X and Y axes
    line(midx, 0, midx, getmaxy()); // Y-axis
    line(0, midy, getmaxx(), midy); // X-axis
    // Input the triangle coordinates
    printf("2D Transformation: Translation, Rotation, Scaling, and Reflection\n");
    printf("Enter the points (x1,y1), (x2,y2), and (x3,y3) of the triangle:\n");
    scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3);
    // Draw the original triangle
    setcolor(WHITE);
    line(midx + x1, midy - y1, midx + x2, midy - y2);
    line(midx + x2, midy - y2, midx + x3, midy - y3);
    line(midx + x3, midy - y3, midx + x1, midy - y1);
    // Menu for transformations
    while (1) {
        printf("\n1. Translation\n2. Rotation\n3. Scaling\n4. Reflection\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1: // Translation
                printf("Enter the translation factors (tx, ty): ");
                scanf("%f%f", &tpx, &tpy);
                // Apply translation
                x11 = x1 + tpx;
                y11 = y1 + tpy;
                x22 = x2 + tpx;
                y22 = y2 + tpy;
                x33 = x3 + tpx;
                y33 = y3 + tpy;
                // Draw the translated triangle
                setcolor(RED);
                line(midx + x11, midy - y11, midx + x22, midy - y22);
                line(midx + x22, midy - y22, midx + x33, midy - y33);
                line(midx + x33, midy - y33, midx + x11, midy - y11);
                break;
            case 2: // Rotation
                printf("Enter the angle of rotation (in degrees): ");
                scanf("%f", &ang);
                printf("Enter the rotation point (a, b): ");
                scanf("%f%f", &a, &b);
                // Convert angle to radians
                t = 3.14 * ang / 180;
                // Apply rotation
                x11 = (x1 - a) * cos(t) - (y1 - b) * sin(t) + a;
                y11 = (x1 - a) * sin(t) + (y1 - b) * cos(t) + b;
                x22 = (x2 - a) * cos(t) - (y2 - b) * sin(t) + a;
                y22 = (x2 - a) * sin(t) + (y2 - b) * cos(t) + b;
                x33 = (x3 - a) * cos(t) - (y3 - b) * sin(t) + a;
                y33 = (x3 - a) * sin(t) + (y3 - b) * cos(t) + b;
                // Draw the rotated triangle
                setcolor(BLUE);
                line(midx + x11, midy - y11, midx + x22, midy - y22);
                line(midx + x22, midy - y22, midx + x33, midy - y33);
                line(midx + x33, midy - y33, midx + x11, midy - y11);
                break;
            case 3: // Scaling
                printf("Enter the scaling factors (sx, sy): ");
                scanf("%f%f", &sfx, &sfy);
                printf("Enter the scaling point (a, b): ");
                scanf("%f%f", &a, &b);
                // Apply scaling
                x11 = x1 * sfx + a * (1 - sfx);
                y11 = y1 * sfy + b * (1 - sfy);
                x22 = x2 * sfx + a * (1 - sfx);
                y22 = y2 * sfy + b * (1 - sfy);
                x33 = x3 * sfx + a * (1 - sfx);
                y33 = y3 * sfy + b * (1 - sfy);
                // Draw the scaled triangle
                setcolor(YELLOW);
                line(midx + x11, midy - y11, midx + x22, midy - y22);
                line(midx + x22, midy - y22, midx + x33, midy - y33);
                line(midx + x33, midy - y33, midx + x11, midy - y11);
                break;
            case 4: // Reflection
                printf("Reflection Options:\n");
                printf("1. Reflect over X-axis\n2. Reflect over Y-axis\n3. Reflect over origin\n");
                printf("Enter your choice: ");
                int reflectionChoice;
                scanf("%d", &reflectionChoice);
                // Apply reflection
                switch (reflectionChoice) {
                    case 1: // Reflect over X-axis
                        x11 = x1;
                        y11 = -y1;
                        x22 = x2;
                        y22 = -y2;
                        x33 = x3;
                        y33 = -y3;
                        break;
                    case 2: // Reflect over Y-axis
                        x11 = -x1;
                        y11 = y1;
                        x22 = -x2;
                        y22 = y2;
                        x33 = -x3;
                        y33 = y3;
                        break;
                    case 3: // Reflect over origin
                        x11 = -x1;
                        y11 = -y1;
                        x22 = -x2;
                        y22 = -y2;
                        x33 = -x3;
                        y33 = -y3;
                        break;
                    default:
                        printf("Invalid reflection choice!\n");
                        break;
                }
                // Draw the reflected triangle
                setcolor(GREEN);
                line(midx + x11, midy - y11, midx + x22, midy - y22);
                line(midx + x22, midy - y22, midx + x33, midy - y33);
                line(midx + x33, midy - y33, midx + x11, midy - y11);
                break;
            case 5: // Exit
                closegraph();
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    getch();
    closegraph();
    return 0;
}
