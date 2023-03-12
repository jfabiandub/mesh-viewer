//--------------------------------------------------
// Author: Jenifer Fabian Dubon
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"
#include "fstream"

using namespace std;
using namespace glm;

namespace agl {

   PLYMesh::PLYMesh(const std::string& filename) {
      load(filename);
   }

   PLYMesh::PLYMesh() {
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
   }

   bool PLYMesh::load(const std::string& filename) {
      if ( _positions.size() != 0 ) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      // todo: your code here
         ifstream _file;
         _file.open(filename);
         if (!_file.is_open()) {
            return false;
        }
        string _myData;
        _file >> _myData;
        if (_myData.compare("ply") != 0) {
            return false;
        }
        while (_myData.compare("vertex") != 0) {
            _file >> _myData;
        }
        _file >> _myData;
        int numVertex = stoi(_myData);
        while (_myData.compare("face") != 0) {
            _file >> _myData;
        }
        _file >> _myData;
         int numFace = stoi(_myData);
        printf("numface: %d\n", numFace);
        while (_myData.compare("end_header") != 0) {
            _file >> _myData;
        }

         // todo: your code here
        for (int i = 0; i < numVertex; i++) {
            GLfloat v1, v2, v3, v4, v5, v6;
            _file >> v1>> v2>> v3>> v4>> v5>>v6;
            vec3 vtx = vec3{ v1, v2, v3 };
            _positions.push_back(v1);
            _positions.push_back(v2);
            _positions.push_back(v3);
            _normals.push_back(v4);
            _normals.push_back(v5);
            _normals.push_back(v6);
            _file >> _myData;
            _file >> _myData;
        }
        for (int i = 0; i < numFace; i++) {
            _file >> _myData;
            GLuint f1, f2, f3;
            _file >> f1 >> f2>> f3;
            _faces.push_back(f1);
            _faces.push_back(f2);
            _faces.push_back(f3);
        }  
        return true;
   }
   glm::vec3 PLYMesh::minBounds() const {
   glm::vec3 minBound(_positions[0], _positions[1], _positions[2]);
     
     for (int i = 3; i < _positions.size(); i += 3) {
         glm::vec3 vertex(_positions[i], _positions[i+1], _positions[i+2]);
         if (vertex.x < minBound.x) {
            minBound.x = vertex.x;
         }
         if (vertex.y < minBound.y) {
         minBound.y = vertex.y;
         }
         if (vertex.z < minBound.z) {
         minBound.z = vertex.z;
      }
   }

   return minBound;
   }

   glm::vec3 PLYMesh::maxBounds() const {
     
     glm::vec3 maxBound(_positions[0], _positions[1], _positions[2]);

      for (int i = 3; i < _positions.size(); i += 3) {
         glm::vec3 vertex(_positions[i], _positions[i+1], _positions[i+2]);
         if (vertex.x > maxBound.x) {
            maxBound.x = vertex.x;
         }
         if (vertex.y > maxBound.y) {
         maxBound.y = vertex.y;
         }
         if (vertex.z > maxBound.z) {
         maxBound.z = vertex.z;
      }
   }

   return maxBound;
   }

   int PLYMesh::numVertices() const {
      return _positions.size()/3;
   }

   int PLYMesh::numTriangles() const {
      return _faces.size()/3;
   }

   const std::vector<GLfloat>& PLYMesh::positions() const {
      return _positions;
   }

   const std::vector<GLfloat>& PLYMesh::normals() const {
      return _normals;
   }

   const std::vector<GLuint>& PLYMesh::indices() const {
      return _faces;
   }

   void PLYMesh::clear(){
      _positions.clear();
      _normals.clear();
      _faces.clear();
   }
}
