//
// Created by Arthur Zerr on 06.02.23.
//

#ifndef POLYRPG_MODEL_H
#define POLYRPG_MODEL_H

#include <json/json.h>
#include "Mesh.h"

using json = nlohmann::json;

namespace Engine
{
    class Model
    {
    public:
        Model(const char *file);

        void Draw(Shader &shader, Camera &camera);

    private:
        const char *file;
        std::vector<unsigned char> data;
        json JSON;

        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translationMeshes;
        std::vector<glm::quat> rotationMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;

        std::vector<std::string> loadedTexName;
        std::vector<Texture> loadedTex;

        void loadMesh(unsigned int indMesh);

        void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

        std::vector<unsigned char> getData();

        std::vector<float> getFloats(json accessor);

        std::vector<GLuint> getIndices(json accessor);

        std::vector<Vertex> assembleVertices(
                std::vector<glm::vec3> positions,
                std::vector<glm::vec3> normals,
                std::vector<glm::vec2> textUVs
        );

        std::vector<Texture> getTextures();

        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);

        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);

        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);


    };
}


#endif //POLYRPG_MODEL_H
