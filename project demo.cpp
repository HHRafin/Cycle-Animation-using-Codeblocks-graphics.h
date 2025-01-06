#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <cmath>
#include <cstdlib> // for random positioning
#include <math.h>

using namespace std;
//float M_PI=3.1416;

class cycle {
public:
    void body();
};

void Letters();
void Close();

void Letters() {
    for (int i = 0; i < 50; i++) {
        settextstyle(3, HORIZ_DIR, 4);
        outtextxy(400, 200, "An animation is going to happen...");
        settextstyle(3, HORIZ_DIR, 10);
        outtextxy(660, 260, "3");
        setcolor(LIGHTBLUE);
        delay(30);
        cleardevice();
    }

    for (int j = 0; j < 30; j++) {
        settextstyle(3, HORIZ_DIR, 4);
        outtextxy(400, 200, "An animation is going to happen...");
        settextstyle(3, HORIZ_DIR, 10);
        outtextxy(660, 260, "2");
        setcolor(YELLOW);
        delay(50);
        cleardevice();
    }

    for (int k = 0; k < 20; k++) {
        settextstyle(3, HORIZ_DIR, 4);
        outtextxy(400, 200, "An animation is going to happen...");
        settextstyle(3, HORIZ_DIR, 10);
        outtextxy(660, 260, "1");
        setcolor(LIGHTMAGENTA);
        delay(50);
        cleardevice();
    }
}

void drawWindmill(int centerX, int centerY, int bladeLength, float angle);
void drawMountains(int backgroundShift);
void drawWheelWithRims(int centerX, int centerY, int radius, float angle);
void drawDesertAndCactus(int backgroundShift);
void drawSun(int centerX, int centerY, int radius);
void drawTrunk(int x, int y);
void drawLeaves(int x, int y);
void drawSmallTrunk(int x, int y);
void drawSmallLeaves(int x, int y);
void drawCloud(int x, int y, int size);
void drawBuilding(int x, int y, int width, int height, int floors);
void drawHalfMoon(int x, int y, int radius);


void cycle::body() {
    int backgroundShift = 0;
    float angle = 0;
    int roadLineOffset = 0;
    bool windmillAndMountainVisible = true;

    int page = 0; // To switch between pages for double buffering

    for (int frameCount = 0; frameCount < 1350; frameCount++) {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        // Draw fixed clouds
        drawCloud(100, 200, 60);  // First cloud at a fixed position
        drawCloud(600, 170, 80);  // Second cloud at a fixed position
        drawCloud(300, 100, 50);  // Third cloud at a fixed position
        drawCloud(900, 100, 70);  // Third cloud at a fixed position
        drawCloud(1250, 150, 50);  // Third cloud at a fixed position


        // Animate the background and road lines from right to left
        if (windmillAndMountainVisible) {
            backgroundShift -= 5;

            if (backgroundShift < -1100) {
                windmillAndMountainVisible = false;
            }

            drawMountains(backgroundShift);
        }

        // Animate the sun moving from right to left only when the mountains are not visible
        if (!windmillAndMountainVisible) {
            int sunCenterX = 2900 + backgroundShift; // 2900 is the sun position
            int sunCenterY = 100; // Fixed vertical position near the top
            int sunRadius = 50;
            drawSun(sunCenterX, sunCenterY, sunRadius);
        }
        if (!windmillAndMountainVisible) {
    // Animate cacti
    drawDesertAndCactus(backgroundShift);

    // Animate 5 trees after cactus, moving in the same manner
    int initialTreeXPosition = 4800 + backgroundShift;  // Set the starting position for the first tree
    int treeSpacing = 400;  // Space between each tree

    for (int i = 0; i < 10; i++) {
    int treeXPosition = initialTreeXPosition + (i * treeSpacing);  // Calculate position for each tree

    // Alternate between big and small trees
    if (i % 2 == 0) {
        drawTrunk(treeXPosition, 533);   // Draw large tree trunk
        drawLeaves(treeXPosition, 533);  // Draw large tree leaves
    } else {
        drawSmallTrunk(treeXPosition, 533);   // Draw small tree trunk
        drawSmallLeaves(treeXPosition, 533);  // Draw small tree leaves

        //int cloudXPosition = treeXPosition;       // Align cloud with the tree
        //int cloudYPosition = 533 - 400;           // Position cloud above the tree
        //drawCloud(cloudXPosition, cloudYPosition, 50 + (i % 2) * 20); // Varied size
    }

}
    int initialBuildingXPosition = 8800 + backgroundShift; // Set initial building position
    int buildingSpacing = 300; // Space between buildings
    for (int i = 0; i < 10; i++) {
    int buildingXPosition = initialBuildingXPosition + (i * buildingSpacing);
    int buildingHeight = (i % 2 == 0) ? 400 : 250 ; // Alternate heights
    int floors = (i % 2 == 0) ? 9 : 5; // Alternate floors
    drawBuilding(buildingXPosition, 533, 120, buildingHeight, floors); //building position
    }

    // Separate moon animation
    static int moonShift = 0;  // Separate variable for the moon's position shift
    if (frameCount % 1== 0) { // Update moon position every other frame to slow it down
        moonShift -= 1;
    }
    // Draw a single large half-moon on top of the building section
    int moonCenterX = initialBuildingXPosition + 12000; // Adjust to center above buildings
    int moonCenterY = 80;                            // Vertical position for the moon
    int moonRadius = 65;                              // Size of the moon
    drawHalfMoon(moonCenterX + backgroundShift, moonCenterY, moonRadius);

    backgroundShift -= 2; // Continue moving the trees along with the cactus
}

        // Fixed position for the cycle
        int cycleX = 700;

        //upper road line
        setcolor(WHITE);
        line(0, 536, getmaxx(), 536);
        line(0, 538, getmaxx(), 538);

        // Draw the cycle at a fixed position
        setcolor(WHITE);
        line(cycleX - 50, 555, cycleX, 555);
        line(cycleX - 25, 525, cycleX + 25, 525);
        line(cycleX - 50, 555, cycleX - 25, 525);
        line(cycleX, 555, cycleX + 25, 525);
        line(cycleX + 50, 555, cycleX, 495);
        line(cycleX - 25, 525, cycleX - 25, 520);
        line(cycleX - 30, 520, cycleX - 20, 520);
        line(cycleX - 20, 495, cycleX, 495);

        // Draw rotating cycle wheels with rims
        drawWheelWithRims(cycleX + 50, 555, 30, angle);
        drawWheelWithRims(cycleX - 50, 555, 30, angle);

        // Draw the road and road lines

        setcolor(WHITE);
        line(0, 650, getmaxx(), 650);
        line(0, 652, getmaxx(), 652);


        int roadLineWidth = 60;
        int roadLineGap = 80;

        setfillstyle(SOLID_FILL,WHITE);

        for (int j = 0; j < 30; j++) {

            int x1 = (roadLineWidth + roadLineGap) * j + roadLineOffset;
            int x2 = x1 + roadLineWidth;
            rectangle(x1, 590, x2, 596);
            floodfill(x1 + 1, 591, WHITE);
            floodfill(x2 + 1, 596, WHITE);

        }
        roadLineOffset -= 5;
        if (roadLineOffset <= -(roadLineWidth + roadLineGap)) {
            roadLineOffset = 0;
        }

        // Windmill and cactus animations
        if (windmillAndMountainVisible) {
            setcolor(YELLOW);
            rectangle(400 + backgroundShift, 200, 405 + backgroundShift, 536);
            rectangle(800 + backgroundShift, 200, 805 + backgroundShift, 536);
            rectangle(1200 + backgroundShift, 200, 1205 + backgroundShift, 536);
            rectangle(1600 + backgroundShift, 200, 1605 + backgroundShift, 536);

            setcolor(WHITE);
            drawWindmill(403 + backgroundShift, 200, 90, angle);
            drawWindmill(803 + backgroundShift, 200, 90, angle);
            drawWindmill(1203 + backgroundShift, 200, 90, angle);
            drawWindmill(1603 + backgroundShift, 200, 90, angle);
        } else {
            // Animate cacti after windmill animation ends
            drawDesertAndCactus(backgroundShift);
            backgroundShift -= 7; // Continue moving the cacti
        }

        // Update the angle for the animation
        angle += 0.06; //windmill blade animation speed

        delay(10); //main animation speed

        // Swap the active and visible pages
        page = 1 - page;
    }
}
void drawWheelWithRims(int centerX, int centerY, int radius, float angle) {
    int numSpokes = 8;
    float spokeAngleIncrement = 2 * M_PI /(float) numSpokes;

    setcolor(WHITE);
    circle(centerX, centerY, radius);

    setcolor(CYAN);
    circle(centerX, centerY, radius - 3);

    for (int i = 0; i < numSpokes; i++) {
        float currentAngle = angle + i * spokeAngleIncrement;

        int spokeX = centerX + (radius - 5) * cos(currentAngle);
        int spokeY = centerY + (radius - 5) * sin(currentAngle);

        line(centerX, centerY, spokeX, spokeY);
    }
}

void drawWindmill(int centerX, int centerY, int bladeLength, float angle) {
    int slimnessFactor = 10;

    for (int i = 0; i < 3; i++) {
        float currentAngle = angle + i * 2 * M_PI / 3;

        int tipX = centerX + bladeLength * cos(currentAngle);
        int tipY = centerY + bladeLength * sin(currentAngle);

        int base1X = centerX + (bladeLength / slimnessFactor) * cos(currentAngle + M_PI / 6);
        int base1Y = centerY + (bladeLength / slimnessFactor) * sin(currentAngle + M_PI / 6);

        int base2X = centerX + (bladeLength / slimnessFactor) * cos(currentAngle - M_PI / 6);
        int base2Y = centerY + (bladeLength / slimnessFactor) * sin(currentAngle - M_PI / 6);

        setcolor(WHITE);
        line(centerX, centerY, tipX, tipY);
        line(tipX, tipY, base1X, base1Y);
        line(tipX, tipY, base2X, base2Y);
    }
}

void drawMountains(int backgroundShift) {
    setcolor(LIGHTGREEN);
    setlinestyle(SOLID_LINE, 0, 3);
    setfillstyle(SOLID_FILL,WHITE);


    //1st mountain
    line(0 + backgroundShift, 199, 200 + backgroundShift, 100);
    arc(220 + backgroundShift, 157, 49, 118, 60);
    line(259 + backgroundShift, 112, 460 + backgroundShift, 300);

    //2nd mountain
    line(353 + backgroundShift, 200, 600 + backgroundShift, 60);
    arc(625 + backgroundShift, 115, 49, 118, 60);
    line(654 + backgroundShift, 62, 800 + backgroundShift, 200);

    //3rd mountain
    line(800 + backgroundShift, 199, 1000 + backgroundShift, 100);
    arc(1020 + backgroundShift, 157, 49, 118, 60);
    line(1059 + backgroundShift, 112, 1300 + backgroundShift, 300);

    //4th mountain
    line(1153 + backgroundShift, 200, 1400 + backgroundShift, 60);
    arc(1425 + backgroundShift, 115, 49, 118, 60);
    line(1454 + backgroundShift, 62, 1600 + backgroundShift, 200);
}

void drawDesertAndCactus(int backgroundShift) {
    int cactusBaseY = 533;

    setcolor(WHITE);
    //setfillstyle(SOLID_FILL, BLACK);
    //rectangle(0, cactusBaseY, getmaxx(), getmaxy());
    //floodfill(1, cactusBaseY + 1, WHITE);

    // Updated positions for 18 cacti
    int cactusXPositions[] = {900, 1100, 1300, 1500, 1700, 1900, 2100, 2300, 2500, 2700,
                              2900, 3100, 3300, 3500, 3700,3900,4100,4300,4500,4700 };

    for (int i = 0; i < 18; i++) {
        int baseX = cactusXPositions[i] + backgroundShift;

        // Determine cactus size (large or small)
        int cactusHeight = (i % 2 == 0) ? 300 : 150; // Large for even indices, small for odd
        int armHeight = (i % 2 == 0) ? 100 : 50;     // Taller arms for large cactus, shorter for small

        // Draw main cactus body with rounded top
        setcolor(GREEN);
        rectangle(baseX, cactusBaseY - cactusHeight, baseX + 60, cactusBaseY);
        arc(baseX + 30, cactusBaseY - cactusHeight, 0, 180, 30); // Rounded top for the main body

        // Draw left arm with rounded top
        rectangle(baseX - 20, cactusBaseY - (cactusHeight / 2), baseX, cactusBaseY - (cactusHeight / 2) - armHeight);
        arc(baseX - 10, cactusBaseY - (cactusHeight / 2) - armHeight, 0, 180, 10); // Rounded top for left arm

        // Draw right arm with rounded top
        rectangle(baseX + 60, cactusBaseY - (cactusHeight / 2), baseX + 80, cactusBaseY - (cactusHeight / 2) - armHeight);
        arc(baseX + 70, cactusBaseY - (cactusHeight / 2) - armHeight, 0, 180, 10); // Rounded top for right arm

        // Draw fixed spikes on the cactus body
        setcolor(DARKGRAY);
        int spikePositions[][2] = {
            {baseX + 15, cactusBaseY - cactusHeight + 30},
            {baseX + 45, cactusBaseY - cactusHeight + 60},
            {baseX + 25, cactusBaseY - cactusHeight + 90},
            {baseX + 35, cactusBaseY - cactusHeight + 120},
            {baseX + 5, cactusBaseY - cactusHeight + 150},
            {baseX + 50, cactusBaseY - cactusHeight + 180},
        };
        for (int j = 0; j < 6; j++) {
            line(spikePositions[j][0], spikePositions[j][1], spikePositions[j][0] + 5, spikePositions[j][1] - 10);
        }

        // Draw fixed spikes on the left arm
        int leftArmSpikes[][2] = {
            {baseX - 10, cactusBaseY - (cactusHeight / 2) - 10},
            {baseX - 10, cactusBaseY - (cactusHeight / 2) - armHeight + 20},
        };
        for (int j = 0; j < 2; j++) {
            line(leftArmSpikes[j][0], leftArmSpikes[j][1], leftArmSpikes[j][0] + 5, leftArmSpikes[j][1] - 10);
        }

        // Draw fixed spikes on the right arm
        int rightArmSpikes[][2] = {
            {baseX + 70, cactusBaseY - (cactusHeight / 2) - 10},
            {baseX + 70, cactusBaseY - (cactusHeight / 2) - armHeight + 20},
        };
        for (int j = 0; j < 2; j++) {
            line(rightArmSpikes[j][0], rightArmSpikes[j][1], rightArmSpikes[j][0] + 5, rightArmSpikes[j][1] - 10);
        }
    }
}


void drawSun(int centerX, int centerY, int radius) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(centerX, centerY, radius);
    floodfill(centerX, centerY, YELLOW);

    // Drawing sun rays
    int rayLength = radius + 20; // Length of the rays
    for (int angle = 0; angle < 360; angle += 15) { // Adjust the angle increment for more or fewer rays
        // Calculate the end points of the rays
        int rayX = centerX + rayLength * cos(angle * M_PI / 180.0);
        int rayY = centerY + rayLength * sin(angle * M_PI / 180.0);

        // Draw the ray
        line(centerX, centerY, rayX, rayY);
    }
}

void drawTrunk(int x, int y) {
    int trunkWidth = 40;
    int trunkHeight = 150;

    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(x - trunkWidth / 2, y, x + trunkWidth / 2, y - trunkHeight);
    floodfill(x, y - trunkHeight / 2, BROWN);
}

void drawLeaves(int x, int y) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);

    pieslice(x, y - 280, 0, 180, 70);   // center half-circle (big)
    pieslice(x - 80, y - 235, 0, 360, 60); // left half-circle (medium)
    pieslice(x + 80, y - 235, 0, 360, 60); // right half-circle (medium)
    pieslice(x, y - 220, 0, 180, 80);      // center half-circle (medium)
    pieslice(x - 100, y - 180, 0, 360, 60); // left half-circle (medium)
    pieslice(x + 100, y - 180, 0, 360, 60); // right half-circle (medium)
    pieslice(x, y - 150, 0, 180, 80);       // center half-circle (medium)
    pieslice(x - 80, y - 150, 180, 360, 60);  // left half-circle (small, upside-down)
    pieslice(x + 80, y - 150, 180, 360, 60);  // right half-circle (small, upside-down)
    pieslice(x, y - 150, 180, 360, 60);       // center half-circle (small, upside-down)
}
void drawSmallTrunk(int x, int y) {
    int trunkWidth = 20; // Decrease trunk width
    int trunkHeight = 75; // Decrease trunk height

    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(x - trunkWidth / 2, y, x + trunkWidth / 2, y - trunkHeight);
    floodfill(x, y - trunkHeight / 2, BROWN);
}

void drawSmallLeaves(int x, int y) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);

    pieslice(x, y - 140, 0, 180, 35);   // center half-circle (big)
    pieslice(x - 40, y - 117, 0, 360, 30); // left half-circle (medium)
    pieslice(x + 40, y - 117, 0, 360, 30); // right half-circle (medium)
    pieslice(x, y - 110, 0, 180, 40);      // center half-circle (medium)
    pieslice(x - 50, y - 90, 0, 360, 30); // left half-circle (medium)
    pieslice(x + 50, y - 90, 0, 360, 30); // right half-circle (medium)
    pieslice(x, y - 75, 0, 180, 40);       // center half-circle (medium)
    pieslice(x - 40, y - 75, 180, 360, 30);  // left half-circle (small, upside-down)
    pieslice(x + 40, y - 75, 180, 360, 30);  // right half-circle (small, upside-down)
    pieslice(x, y - 75, 180, 360, 30);       // center half-circle (small, upside-down)
}

void drawCloud(int x, int y, int size) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    // Main body of the cloud
    fillellipse(x, y, size, size / 2);  // Central part of the cloud

    // Additional circles to create a fluffy, realistic look
    fillellipse(x - size / 1.5, y, size / 1.5, size / 2);       // Left circle
    fillellipse(x + size / 1.5, y, size / 1.5, size / 2);       // Right circle
    fillellipse(x, y - size / 2, size / 1.5, size / 2.2);       // Top middle circle
    fillellipse(x - size / 3, y + size / 4, size / 1.8, size / 1.75); // Bottom left circle
    fillellipse(x + size / 3, y + size / 4, size / 1.8, size / 1.75); // Bottom right circle



}

void drawBuilding(int x, int y, int width, int height, int floors) {
    int buildingTop = y - height;

    // Draw the building structure
    setfillstyle(SOLID_FILL, COLOR(100, 100, 100)); // Gray color
    bar(x, buildingTop, x + width, y);

    // Draw windows on the building
    int windowSize = 20;
    setfillstyle(SOLID_FILL, COLOR(255, 255, 0)); // Yellow for window light

    for (int i = 0; i < floors; ++i) {
        for (int j = 0; j < width / (2 * windowSize); ++j) {
            int winX = x + j * 2 * windowSize + windowSize / 2;
            int winY = buildingTop + i * 2 * windowSize + windowSize / 2;
            bar(winX, winY, winX + windowSize, winY + windowSize);
        }
    }
}
void drawHalfMoon(int x, int y, int radius) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    // Full circle for the moon background
    fillellipse(x, y, radius, radius);

     //Create the half-moon effect by overlaying a black circle
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + radius / 4, y, radius - radius / 4, radius);
}




void Close() {
    for (int i = 0; i < 30; i++) {
        setactivepage(0);
        setvisualpage(0);
        cleardevice(); // Clear before drawing to avoid flicker
        settextstyle(3, HORIZ_DIR, 20);
        setcolor(LIGHTMAGENTA);
        outtextxy(450, 280, "The End");
        delay(100); // Slower delay to make it more visible
    }
    setactivepage(0);
    setvisualpage(0); // Ensure the final page is displayed
    cleardevice();
    outtextxy(450, 280, "The End"); // Display "The End" without clearing again
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");
    initwindow(1366, 768);

    cycle c1;
    Letters();
    c1.body();
    Close();

    getch(); // Wait for a key press before closing
    closegraph();
    return 0;
}

