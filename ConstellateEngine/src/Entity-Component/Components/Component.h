#pragma once


namespace csl {

    enum class ComponentType {
        PositionComponentType,
        PhysicsComponentType,
        GraphicsComponentType
    };

    class Entity;

    class Component
    {
    private:
        Entity* _entity;

        bool alive = true;

    public:
        virtual void init() {}
        virtual void update(float mFT) {}
        virtual void draw() {}

        void SetEntity(Entity* entity) {
            _entity = entity;
        }

        virtual ComponentType GetComponentType() = 0;

    };

}
