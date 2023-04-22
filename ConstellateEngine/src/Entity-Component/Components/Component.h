#pragma once


namespace csl {

    enum class ComponentType {
        PositionComponentType,
        PhysicsComponentType,
        ColliderComponentType,
        GraphicsComponentType,
    };

    class Entity;

    class Component
    {
    private:
        Entity* _entity;

        bool alive = true;

    public:
        virtual void update(float mFT) {}
        virtual void draw() {}

        void SetEntity(Entity* entity) {
            _entity = entity;
        }

        Entity* getEntity() {
            return _entity;
        }

        virtual ComponentType GetComponentType() = 0;

    };

}
