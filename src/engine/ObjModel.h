//
// Created by Arthur Zerr on 07.02.23.
//

#ifndef POLYRPG_OBJMODEL_H
#define POLYRPG_OBJMODEL_H

#include <tinyobj/tiny_obj_loader.h>
#include <unordered_map>
#include <vector>

#include "Mesh.h"
#include "Shader.h"


namespace Engine::Models
{
    class ObjModel
    {
    public:
        ObjModel(const char *file);

        void Load();

        void Draw(Shader &shader, Camera &camera);

    private:
        bool hasLoaded;
        const char *file;

        GLuint vb_id;

        int numTriangles = 0;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texturesUVs;
        std::vector<glm::vec3> vColors;

    };
};


#endif //POLYRPG_OBJMODEL_H
