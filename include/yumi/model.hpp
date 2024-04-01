#pragma once

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include "mesh.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "file.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include "transform.hpp"

#include <vector>
#include <string>

using json = nlohmann::json;

namespace yumi {
    class Model {
    private:
        const char* filePath;
        std::vector <unsigned char> data;
        json JSON;

        std::vector<glm::vec3> translations;
        std::vector<glm::quat> rotations;
        std::vector<glm::vec3> scales;
        std::vector<glm::mat4> matrices;

        std::vector<Mesh*> loadedMeshes;
        std::vector<Texture*> loadedTextures;
        std::vector<std::string> loadedTextureNames;

        void loadMesh(unsigned int index);
        void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(json accessor);
        std::vector<unsigned int> getIndices(json accessor);

        std::vector<Texture*> getTextures();
        std::vector<Vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords);

        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floats);
        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floats);
        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floats);

    public:
        Model(const char* filePath);
        ~Model();

        Transform transform;

        void render(Shader* shader, Camera* camera);
        void destroy();
    };
}