//--------------------------------------------------
// Author: Jenifer Fabian Dubon
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
   }

   void setup() {
      model =  GetFilenamesInDir("../models", "ply");
      mesh.load("../models/" + model[_currModel]);
      _numModel = model.size();

   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
        // Convert pixel movement to rotation angles
        float sensitivity = 0.2f;
        float azimuthDelta = dx * sensitivity;
        float elevationDelta = dy * sensitivity;

        // Update camera position
        azimuth += azimuthDelta;
        elevation += elevationDelta;

        // Keep elevation within [-90, 90] degrees
        elevation = glm::clamp(elevation, -90, 90);

        // Convert spherical coordinates to cartesian coordinates
        float theta = glm::radians(static_cast<float>(azimuth));
        float phi = glm::radians(static_cast<float>(elevation));
        float x = radius * glm::cos(phi) * glm::cos(theta);
        float y = radius * glm::sin(phi);
        float z = radius * glm::cos(phi) * glm::sin(theta);
        eyePos = lookPos + glm::vec3(x, y, z);

        // Update view matrix
        //renderer.lookAt(eyePos, lookPos, up);
    }
}


   void mouseDown(int button, int mods) {


   }

   void mouseUp(int button, int mods) {
   }

   void scroll(float dx, float dy) {
        radius += dy * 0.05f;

      eyePos = vec3(
         radius * sin(azimuth) * cos(elevation), 
         radius * sin(elevation), 
         radius * cos(azimuth) * cos(elevation)
      );
   }

   void keyUp(int key, int mods) {
   }

   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      renderer.rotate(vec3(0,0,0));
      renderer.scale(vec3(1,1,1));
      renderer.translate(vec3(0,0,0));
      //renderer.mesh(mesh);
      renderer.lookAt(eyePos, lookPos, up);
      renderer.cube(); // for debugging!
   }

protected:
   PLYMesh mesh;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);


   std::vector<std::string> model;
   int _currModel;
   int _numModel;

   float azimuth = 0;
   int elevation = 0;
   float radius = 10;



};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

