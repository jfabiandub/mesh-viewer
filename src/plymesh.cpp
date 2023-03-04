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
      _positions.clear();
      _normals.clear();
      _faces.clear();
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
   }

   bool PLYMesh::load(const std::string& filename) {
      if (_positions.size() != 0|| _normals.size() != 0 || _faces.size() != 0) {
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
        
        for (int i = 0; i < numVertex; i++) {
            GLfloat a, b, c, d, e, f;
            _file >> a;
            _file >> b;
            _file >> c;
            _file >> d;
            _file >> e;
            _file >> f;
            vec3 vtx = vec3{ a, b, c };
            _positions.push_back(a);
            _positions.push_back(b);
            _positions.push_back(c);
            _normals.push_back(d);
            _normals.push_back(e);
            _normals.push_back(f);
            _file >> _myData;
            _file >> _myData;
        }
        for (int i = 0; i < numFace; i++) {
            _file >> _myData;
            GLuint a, b, c;
            _file >> a;
            _file >> b;
            _file >> c;
            _faces.push_back(a);
            printf("a: : %d\n", a);
            _faces.push_back(b);
            _faces.push_back(c);
        }
        return false;
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
}
