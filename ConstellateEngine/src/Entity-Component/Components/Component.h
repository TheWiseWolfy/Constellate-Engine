/*
File:Component.h

Class describing the component from the Entity-Component pattern.

TODO:Replace enum with registration system, because for now, the engine user cannot properly declare his own component types.

*/



#pragma once


namespace csl {

    enum class ComponentType {
        PositionComponentType,
        PhysicsComponentType,
        ColliderComponentType,
        GraphicsComponentType,
        CustomComponentType1,
        CustomComponentType2
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
        virtual void init() {}

        void SetEntity(Entity* entity) {
            _entity = entity;
        }

        Entity* getEntity() {
            return _entity;
        }

        virtual ComponentType GetComponentType() = 0;

    };

}
