#pragma once

#include "Components/Component.h"

#include "glm.hpp"
#include "cslpch.h"
struct aiMesh;

namespace csl {

    class EntityManager;

    struct Transform {
        //Transform data
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::vec3 _rotation;

        Transform() {
            _position = { 0.0, 0.0, 0.0 };
            _scale = { 1.0,1.0,1.0 };
            _rotation = { 1.0,1.0,1.0 };
        }

        Transform(glm::vec3 pozition) {
            _position = pozition;
            _scale = { 1.0,1.0,1.0 };
            _rotation = { 1.0,1.0,1.0 };

        }

        Transform(glm::vec3 pozition, glm::vec3 scale) {
            _position = pozition;
            _scale = scale;
            _rotation = { 1.0,1.0,1.0 };

        }

        Transform(glm::vec3 pozition, glm::vec3 scale, glm::vec3 rotation) {
            _position = pozition;
            _scale = scale;
            _rotation = rotation;

        }

        //Getters
        glm::vec3 getPosition() const { return _position; }
        glm::vec3 getScale() const { return _scale; }
        glm::vec3 getRotation() const { return _rotation; }

        //Setters
        void setPosition(const glm::vec3& position) { _position = position; }
        void setScale(const glm::vec3& scale) { _scale = scale; }
        void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
    };

    class Entity {
    private:
        std::vector<std::unique_ptr<Entity>> _childrenEntities;
        std::map< ComponentType, std::unique_ptr<Component> > componentReference;

        const std::variant<Entity*, EntityManager*> _parent;

        Transform _transform;
    public:

        Entity(EntityManager* manager) : _parent(manager) {
        }
        Entity(Entity* entityParent) : _parent(entityParent) {
        }

        //Transform 
        Transform& getTransform() {
            return _transform;
        }

        void setTransform(Transform transform) {
            _transform = transform;
        }

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

        //Component Entity Dynammic
        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->SetEntity(this);
            std::unique_ptr<Component> uPtr{ c };

            ComponentType type = c->GetComponentType();
            componentReference.insert(std::make_pair(type, std::move(uPtr)));
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
    };
}