#pragma once

#include "Components/Component.h"

#include "glm.hpp"
#include "cslpch.h"
#include "Transform.h"

struct aiMesh;

namespace csl {

    class EntityManager;

    class Entity {
    private:
        std::vector<std::unique_ptr<Entity>> _childrenEntities;
        std::map< ComponentType, std::unique_ptr<Component> > _componentReference;

        const std::variant<Entity*, EntityManager*> _parent;

        Transform _transform;
    public:

        Entity(EntityManager* manager) : _parent(manager) {}
        Entity(Entity* entityParent) : _parent(entityParent) {}

        void update(float mFT)
        {
            for (auto const& component : _componentReference)
            {
                component.second->update(mFT);
            }
        }

        //Transform 
        Transform& getTransform() {
            return _transform;
        }

        void setTransform(Transform transform) {
            _transform = transform;
        }

        //Component Entity Dynammic


        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->SetEntity(this);
            std::unique_ptr<Component> uPtr{ c };

            ComponentType type = c->GetComponentType();
            _componentReference.insert(std::make_pair(type, std::move(uPtr)));
            return *c;
        }

        bool HasComponent(ComponentType type) {
            auto it = _componentReference.find(type);

            if (it != _componentReference.end())
            {
                return true;
            }
            return false;
        }

        Component* GetComponent(ComponentType type) {
            return _componentReference[type].get();
        }




        //__________________________________________________________________________
       
        //Fuctions used in the parent-child dynamic
        glm::vec3 getAbsolutePosition() {
            glm::vec3 absolutePosition = _transform._position;
            for (Entity* currentEntity = getParentEntity(); currentEntity != nullptr; currentEntity = currentEntity->getParentEntity()) {
                absolutePosition += currentEntity->_transform._position;
            }
            return absolutePosition;
        }

        glm::vec3 getAbsoluteScale() {
        glm::vec3 absoluteScale = _transform._scale;
        for (Entity* currentEntity = getParentEntity(); currentEntity != nullptr; currentEntity = currentEntity->getParentEntity()) {
            absoluteScale *= currentEntity->_transform._scale;
        }
        return absoluteScale;
    }

        //Parent pattern
        bool isParentedByEntity() const { return std::holds_alternative<Entity*>(_parent); }
        bool isParentedByManager() const { return std::holds_alternative<EntityManager*>(_parent); }

        Entity* getParentEntity() const { 
            if (isParentedByEntity()) {
                return std::get<Entity*>(_parent);
            }
            return nullptr;
        }
        EntityManager* getParentManager() const { 
            if (isParentedByManager()) {
                return std::get<EntityManager*>(_parent);
            }
            return nullptr;
        }

       //Parent Child Dynamic
        std::variant<Entity*, EntityManager*> getParent() const { return _parent; }

        Entity* createChildEntity() {

            _childrenEntities.emplace_back(std::make_unique<Entity>(this));

            return _childrenEntities.back().get();
        }

        std::vector<std::unique_ptr<Entity>>& GetChildren() {
            return _childrenEntities;
        }


    };
}