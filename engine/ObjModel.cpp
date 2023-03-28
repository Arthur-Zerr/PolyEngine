//
// Created by Arthur Zerr on 06.02.23.
//

#include "ObjModel.h"

Engine::Models::ObjModel::ObjModel(const char *file)
{
    this->file = file;
}


void Engine::Models::ObjModel::Load()
{
    tinyobj::ObjReader objReader;
    tinyobj::ObjReaderConfig objReaderConfig;

    objReaderConfig.mtl_search_path = "./objects/";

    if (!objReader.ParseFromFile(this->file, objReaderConfig))
    {
        if (!objReader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << objReader.Error();
        }
        exit(1);
    }

    auto &attrib = objReader.GetAttrib();
    auto &shapes = objReader.GetShapes();
    auto &materials = objReader.GetMaterials();

    this->hasLoaded = true;

    for (size_t s = 0; s < shapes.size(); s++)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                this->vertices.push_back(glm::vec3(vx, vy, vz));

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0)
                {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

                    this->normals.push_back(glm::vec3(nx, ny, nz));
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0)
                {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

                    this->texturesUVs.push_back(glm::vec2(tx, ty));
                }

                // Optional: vertex colors
                tinyobj::real_t red = attrib.colors[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t green = attrib.colors[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t blue = attrib.colors[3 * size_t(idx.vertex_index) + 2];

                this->vColors.push_back(glm::vec3(red, green, blue));
            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];

            std::vector<float> buffer;
            if (buffer.size() > 0)
            {
                glGenBuffers(1, &vb_id);
                glBindBuffer(GL_ARRAY_BUFFER, vb_id);
                glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
                             &buffer.at(0), GL_STATIC_DRAW);
                numTriangles = buffer.size() / (3 + 3 + 3 + 2) /
                               3;  // 3:vtx, 3:normal, 3:col, 2:texcoord

                GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
                glEnableVertexAttribArray(0); // Enable the vertex Attribute

                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *) (3 * sizeof(float)));
                glEnableVertexAttribArray(1); // Enable the vertex Attribute

                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *) (6 * sizeof(float)));
                glEnableVertexAttribArray(2); // Enable the vertex Attribute

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        }
    }
}


void Engine::Models::ObjModel::Draw(Shader &shader, Camera &camera)
{
    if (!this->hasLoaded)
    {
        throw;
    }

    shader.Activate();
    glBindBuffer(GL_ARRAY_BUFFER, this->vb_id);

    glUniform3f(glGetUniformLocation(shader.Id, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "scale"), 1, GL_FALSE, glm::value_ptr(sca));

    glDrawArrays(GL_TRIANGLES, 0, 3 * this->numTriangles);
}



