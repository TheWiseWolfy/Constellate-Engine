#pragma once

#include "cslpch.h"
#include "Entity.h"

namespace csl {
    class EngineEvent;

	class EntityManager{
	private:
		std::vector<std::unique_ptr<Entity>> _entityList;

	public:

        std::vector<std::unique_ptr<Entity>>& GetEntityVector();
        void update(float mFT);
        void propagateEvent(EngineEvent& e);

        Entity* addEntity();
        Entity* addEntity(Entity* e);
    };
}