#pragma once

#include "cslpch.h"
#include "Entity.h"

namespace csl {

	class EntityManager{
	private:
		std::vector<std::unique_ptr<Entity>> _entityList;

	public:

        std::vector<std::unique_ptr<Entity>>& GetEntityVector() {
            return _entityList;
        }

        Entity* addEntity()
        {
            Entity* e(new Entity(this));
            std::unique_ptr<Entity> uPtr{ e };
            _entityList.emplace_back(std::move(uPtr));
            return e;
        }


        Entity* addEntity(Entity* e)
        {
            std::unique_ptr<Entity> uPtr{ e };
            _entityList.emplace_back(std::move(uPtr));
            return e;
        }


    };
}