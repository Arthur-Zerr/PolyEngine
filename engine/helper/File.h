//
// Created by Arthur Zerr on 07.02.23.
//

#ifndef POLYRPG_FILE_H
#define POLYRPG_FILE_H

#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

namespace Engine::File
{
    class File
    {
    public:
        static std::string LoadFile(const char *filename);
    };
}


#endif //POLYRPG_FILE_H
