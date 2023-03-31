#pragma once

#include "Components/Component.h"

#include "glm.hpp"
#include "cslpch.h"
struct aiMesh;

namespace csl {

    class Entity {
    private:
        std::vector<std::unique_ptr<Entity>> _childrenEntities;

        Entity* _parent = nullptr;

        //Spacial data
        glm::vec3 _position;
        glm::vec3 _rotation;
        float _scale;
    public:
        std::vector<std::unique_ptr<Component>> _components;

        Entity() {

        }
        Entity(Entity* parent) : _parent(parent) {

        }

        Entity* addEntity() {

            _childrenEntities.emplace_back(std::make_unique<Entity>(this));

            return _childrenEntities.back().get();
        }

        std::vector<std::unique_ptr<Entity>>& GetChildren() {
            return _childrenEntities;
        }


        std::vector<std::unique_ptr<Component>>& GetComponents() {
            return _components;
        }


        template <typename T, typename... TArgs>
        T* addComponent(TArgs&&... mArgs)
        {
            T* comp(new T(std::forward<TArgs>(mArgs)...));
            comp->SetEntity(this);

            std::unique_ptr<Component> uPtr{ comp };
            _components.emplace_back(std::move(uPtr));
            return (T*)_components.back().get();
        }


        //Component* addGraphicsComponent(aiMesh* mesh) {
        //    GraphicsComponent* comp = new GraphicsComponent(mesh);
        //    comp->SetEntity(this);

        //    std::unique_ptr<Component> uPtr{ comp };


        //    _components.emplace_back(std::move(uPtr));
        //    return _components.back().get();

        //}

    };
}