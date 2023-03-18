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

  // for (string sha : shaders)
   renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
   renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
    renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
    // etc
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
      
      if (checker) { 
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
      checker = true;
   }

   void mouseUp(int button, int mods) {
      checker = false;
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
      }
      if (key == GLFW_KEY_P || key == GLFW_KEY_LEFT_BRACKET) {
         // show previous model
         _currModel = (_currModel - 1 + _numModel) % _numModel;
         mesh = modelList[_currModel];
      }
      if(key == GLFW_KEY_S){
         _currShader = (_currShader +1)% shaders.size();
          
      }


      
   }
   

   void draw() {
   
   renderer.beginShader(shaders[_currShader]);

      renderer.setUniform("Light.pos", eyePos);
      renderer.setUniform("Light.La", vec3(0.90f));
      renderer.setUniform("Light.Ld", vec3(0.90f));
      renderer.setUniform("Light.Ls", vec3(0.90f));

      
      renderer.setUniform("Material.Ka", vec3(0.1f, 0.1f, 0.1f));
      renderer.setUniform("Material.Kd", vec3(0.6f, 0.6f, 0.9f));
      renderer.setUniform("Material.Ks", vec3(0.9f, 0.9f, 0.9f));
      renderer.setUniform("Material.shine", 50.0f);
 
      

   float aspect = ((float)width()) / height();
   std::cout<<model[_currModel]<<std::endl;
   renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
   renderer.lookAt(eyePos, lookPos, up);

   // Compute mesh bounds
   vec3 maxBounds = mesh.maxBounds();
   vec3 minBounds = mesh.minBounds();
   vec3 center = (maxBounds + minBounds) * 0.5f;
   vec3 size = maxBounds - minBounds;
   float maxDim = std::max(std::max(size.x, size.y), size.z);
   float scale = 6.0f / maxDim;

   // Apply transformations
   renderer.translate(-center);
   renderer.scale(vec3(scale));
   renderer.rotate(vec3(0, 0, 0));
   renderer.translate(vec3(x, y, z));







   // Render the mesh
   renderer.mesh(mesh);
   // renderer.cube();
   renderer.endShader();
   }

   

protected:
float _scale = 1.0f;
   float x=0.0f;
   float y=0.0f;
   float z=0.0f;

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

   bool checker = false;

   int _currShader = 0;
   std::vector<string> shaders = {"normals", "phong-vertex", "phong-pixel"};

};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

