#pragma once

#include "Components/Component.h"

#include "glm.hpp"
#include "cslpch.h"
struct aiMesh;

namespace csl {

    class EntityManager;

    class Entity {
    private:
        std::vector<std::unique_ptr<Entity>> _childrenEntities;
        std::map< ComponentType, std::unique_ptr<Component> > componentReference;

        Entity* _parent = nullptr;
        EntityManager* _manager = nullptr;

        //Spacial data
        glm::vec3 _position;
        glm::vec3 _rotation;
        float _scale;
    public:

        Entity(EntityManager* manager) : _manager(manager) {
        }
        Entity(Entity* parent) : _parent(parent) {

        }

        Entity() {

        }

        Entity* addEntity() {

            _childrenEntities.emplace_back(std::make_unique<Entity>(this));

            return _childrenEntities.back().get();
        }

        std::vector<std::unique_ptr<Entity>>& GetChildren() {
            return _childrenEntities;
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->SetEntity(this);
            std::unique_ptr<Component> uPtr{ c };

            ComponentType type = c->GetComponentType();
            componentReference.insert(std::make_pair(type, std::move(uPtr)));
            c->init();
            return *c;
        }

        bool HasComponent(ComponentType type) {
            auto it = componentReference.find(type);

            if (it != componentReference.end())
            {
                return true;
            }
            return false;
        }

        Component* GetComponent(ComponentType type) {
            return componentReference[type].get();
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