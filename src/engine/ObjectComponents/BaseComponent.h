//
// Created by Arthur Zerr on 16.02.23.
//

#ifndef POLYRPG_BASECOMPONENT_H
#define POLYRPG_BASECOMPONENT_H

namespace Engine::ObjectComponents
{
    struct BaseComponent
    {
        virtual void Init() = 0;
        virtual void Dispose() = 0;
    };
}


#endif //POLYRPG_BASECOMPONENT_H
