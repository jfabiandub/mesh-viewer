//--------------------------------------------------
// Author: Jenifer Fabian Dubon
// Date:03/24/2023
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

   renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
   renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
   renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
   //renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
   renderer.loadShader("glitch", "../shaders/glitch.vs", "../shaders/glitch.fs");
   renderer.loadShader("fog", "../shaders/fog.vs", "../shaders/fog.fs");
   renderer.loadShader("flat-shading", "../shaders/flat-shading.vs", "../shaders/flat-shading.fs");

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

      renderer.setUniform("Light.intensity", vec3( 0.8f));
      renderer.setUniform("Light.pos", eyePos);

      renderer.setUniform("Light.La", vec3(0.90f));
      renderer.setUniform("Light.Ld", vec3(0.90f));
      renderer.setUniform("Light.Ls", vec3(0.90f));

      renderer.setUniform("Material.Ka", vec3(0.3f, 0.5f, 0.4f));
      renderer.setUniform("Material.Kd", vec3(0.6f, 0.6f, 0.9f));
      renderer.setUniform("Material.Ks", vec3(0.9f, 0.9f, 0.9f));
      renderer.setUniform("Material.shine", 50.0f);
 
      renderer.setUniform("Fog.maxDist", 60.0f * 0.9f);
      renderer.setUniform("Fog.minDist", 60.0f/2);
      renderer.setUniform("Fog.color", vec3(0.1f));
      renderer.setUniform("scale", 15.0f);

      renderer.setUniform("time", (float)glfwGetTime());
      
      
      float aspect_ratio = static_cast<float>(width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);

      // Calculate the maximum and minimum bounds of the mesh
      glm::vec3 max_bounds = mesh.maxBounds();
      glm::vec3 min_bounds = mesh.minBounds();

      // Calculate the dimensions of the mesh and its maximum extent
      glm::vec3 dimensions = max_bounds - min_bounds;
      float max_extent = glm::compMax(dimensions);

      // Calculate the scale of the mesh and apply it
      float mesh_scale = 6.0f / max_extent;
      renderer.scale(glm::vec3(_scale * mesh_scale));

      // Calculate the center of the mesh and apply the translation
      glm::vec3 center = (max_bounds + min_bounds) / 2.0f;
      center *= -1.0f; 
      renderer.translate(center + glm::vec3(x, y, z));
      renderer.mesh(mesh);
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
   std::vector<string> shaders = {"normals", "phong-vertex", "phong-pixel", "fog", "flat-shading", "glitch"};

};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}
