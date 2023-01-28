#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;

/*struct color to acces the colors  */
struct colors{
  float red;
  float green;
  float blue;
  float trans;
};

/* struct cir with circle information */
struct cir{
  float x;
  float y; 
  float size;
  //float trans;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // todo: store a circle with the current color, size, x, y

      //creates new structs for the new cricle with the stored info
      struct cir newCircle;
      newCircle.x = x;
      newCircle.y = y;
      newCircle.size = circleSize;
      currColor.trans = currAlpha;
      drawColors.push_back(currColor); //add the elemenst from currColor into the list drawColors
      drawCir.push_back(newCircle);  //add the elements from newCircle into the vector Drawcircle 
    }
  }

  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      // todo: check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y


     // define an array of colors
    struct colors colrs[] = {
        { 1, 0.6, 0.2 }, // orange
        { 1, 0.6, 0.6 }, // pink
        { 0.8, 0.6, 1 }, // light purple
        { 0.7, 0.9, 1 }, // light blue
        { 1, 0.9, 0.5 }  // yellow
    };

    // define the position of each color in the array
    float colorPosition[] = { 40, 110, 180, 250, 320 }; //holds the x coordinates of the center of each 

    for (int i = 0; i < 5; i++) {
        float distance = sqrt(pow(2, double(mx - colorPosition[i])) + pow(2, double(my - 35)));  //uses the pythagorean theorem to find the distance between mouse position and the center of cirlce
        if (distance < 30) {
            currColor = colrs[i]; 
            break;
        }
    }
}
 
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      circleSize = circleSize + 1;
    } 
    else if (key == GLFW_KEY_DOWN) {
      // decrease size of circle
      if(circleSize < 2){
        circleSize = circleSize;
      }
      else{
        circleSize = circleSize - 1;
        std::cout << "Window size: " << key << ", " << circleSize << std::endl;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha
      if(currAlpha <= 0.1){
        currAlpha = currAlpha;
      }
      else{
        currAlpha = currAlpha - 0.1;
      }
      
      std::cout << "Window size: " << key << ", " << currAlpha<< std::endl;
    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
      currAlpha = currAlpha + 0.1;
      std::cout << "Window size: " << key << ", " << currAlpha<< std::endl;

    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
    drawColors.clear();
    drawCir.clear();

      
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    color(1.0f, 0.5f, 0.5f, currAlpha);
    circle(width() * 0.5f, height() * 0.5, circleSize);

    // todo : drawCiraw palletlet
      color(0.1f, 0.1f, 0.1f);
      square(width()/2.0f, 35, width(), 70);


      struct cir c = {40, 35, 60}; //the current cirlcle  {x, y, size}
      struct colors col = {1, 0.6, 0.2};  //the current color  {RGB} colors

      /* add the color and the circles to the pallet list and the colorPallet list */
      c = {40, 35, 60};  
      col = {1, 0.6, 0.2};
      pallet.push_back(c);
      colorPallet.push_back(col);

      c = {110, 35, 60};
      col = {1, 0.6, 0.6};
      pallet.push_back(c);
      colorPallet.push_back(col);

      c = {180, 35, 60};
      col = { 0.8, 0.6, 1};
      pallet.push_back(c);
      colorPallet.push_back(col);
      
      c = {250, 35, 60};
      col = {0.7, 0.9, 1};
      pallet.push_back(c);
      colorPallet.push_back(col);

      c = {320, 35, 60};
      col = {1, 0.9, 0.5};
      pallet.push_back(c);
      colorPallet.push_back(col);


      /* draw the circles in the pallet using the colors from the colorPallet vector  */
      for(int i = 0; i < pallet.size(); i++){
        color(colorPallet[i].red, colorPallet[i].green, colorPallet[i].blue);
        circle(pallet[i].x, pallet[i].y, pallet[i].size);
      }   
      /*  draw the circles in the drawCir vector using the color in the drawColors vector */
      for(int i = 0; i < drawCir.size(); i++){
        color(drawColors[i].red, drawColors[i].green, drawColors[i].blue, drawColors[i].trans);
        circle(drawCir[i].x, drawCir[i].y, drawCir[i].size);
      }  
  }
 private:

  // todo: create member variables for 
  // current circle size
  float circleSize = 40.0;
  // current transparency
  float currAlpha = 1.0f;
  // current color
  struct colors currColor = {1, 0.6, 0.2}; 
  // list of circles to drawCiraw each frame
  
  // color palletlet
  std::vector<colors> colorPallet;
  std::vector<cir> pallet;

  //for drawCirawing color and pallet so i can clear it later
  std::vector<cir> drawCir;
  std::vector<colors> drawColors;
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
