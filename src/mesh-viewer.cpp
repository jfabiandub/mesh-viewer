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
      for (string each : model) {
            PLYMesh eachFile;
            eachFile.load("../models/" + each);
            modelList.push_back(eachFile);
        }
         mesh = modelList[0];
        _numModel = modelList.size();
         _currModel = 0;

   }

   void mouseMotion(int x, int y, int dx, int dy) {
      
      if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {  //THIS ONE CAUSES SEGMENTATION SOME TIMES
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
      float x = radius * glm::sin(glm::radians(static_cast<float>(azimuth))) * glm::cos(glm::radians(static_cast<float>(elevation)));
      float y = radius * glm::sin(glm::radians(static_cast<float>(elevation)));
      float z = radius * glm::cos(glm::radians(static_cast<float>(azimuth))) * glm::cos(glm::radians(static_cast<float>(elevation)));
      eyePos = vec3(x, y, z);

    }
}


   void mouseDown(int button, int mods) {
   }

   void mouseUp(int button, int mods) {
   }

   void scroll(float dx, float dy) {
      
      radius += dy * 0.05f;

      float x = radius * glm::sin(glm::radians(static_cast<float>(azimuth))) * glm::cos(glm::radians(static_cast<float>(elevation)));
      float y = radius * glm::sin(glm::radians(static_cast<float>(elevation)));
      float z = radius * glm::cos(glm::radians(static_cast<float>(azimuth))) * glm::cos(glm::radians(static_cast<float>(elevation)));
      eyePos = vec3(x, y, z);
      
   }

   void keyUp(int key, int mods) {
      
       if (key == GLFW_KEY_N || key == GLFW_KEY_RIGHT_BRACKET) {
         // show next model
         _currModel = (_currModel + 1) % _numModel;
         mesh = modelList[_currModel];
      } else if (key == GLFW_KEY_P || key == GLFW_KEY_LEFT_BRACKET) {
         // show previous model
         _currModel = (_currModel - 1 + _numModel) % _numModel;
         mesh = modelList[_currModel];
      }
      
   }

   void draw() {
      /*
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      renderer.rotate(vec3(0,0,0));
      renderer.scale(vec3(1,1,1));
      renderer.translate(vec3(0,0,0));
      renderer.mesh(mesh);
      renderer.lookAt(eyePos, lookPos, up);
      renderer.cube(); // for debugging!
   }
   */

   float aspect = ((float)width()) / height();
   mesh=modelList[_currModel];
   std::cout<<model[_currModel]<<std::endl;
   renderer.perspective(glm::radians(60.0f), aspect, 0.01f, 100.0f);
   renderer.lookAt(eyePos,lookPos,up);
   
   // Center the loaded model at (0,0,0)
   vec3 modelCenter = (mesh.minBounds() + mesh.maxBounds()) / 2.0f;
   renderer.translate(-modelCenter);   
   // Resize the model so it fits within a 10x10x10 view volume
   vec3 scale = vec3(10.0f) / (mesh.maxBounds() - mesh.minBounds());
   float scaleFactor = glm::min(glm::min(scale.x, scale.y), scale.z);
   renderer.scale(vec3(scaleFactor));

   renderer.rotate(vec3(0, 0, 0));
   renderer.mesh(mesh);

   renderer.cube(); // for debugging!
   }
   

protected:
   PLYMesh mesh;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);


   std::vector<std::string> model;
   std::vector<PLYMesh> modelList;
   int _currModel=0;
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

