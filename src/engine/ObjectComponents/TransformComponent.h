//
// Created by Arthur Zerr on 16.02.23.
//

#ifndef POLYRPG_TRANSFORMCOMPONENT_H
#define POLYRPG_TRANSFORMCOMPONENT_H

#include "BaseComponent.h"

namespace Engine::ObjectComponents
{
    class TransformComponent : public BaseComponent
    {

    public:
        TransformComponent();
        void Init() override;
        void Dispose() override;

    };
}


#endif //POLYRPG_TRANSFORMCOMPONENT_H
