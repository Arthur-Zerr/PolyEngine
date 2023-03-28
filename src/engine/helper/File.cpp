//
// Created by Arthur Zerr on 07.02.23.
//

#include "File.h"

std::string Engine::File::File::LoadFile(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    std::cout << "Error loading file: " << filename << std::endl;
    throw (errno);
}
