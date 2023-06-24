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

        void update(float mFT)
        {
            std::vector<std::vector<std::unique_ptr<Entity>>::iterator> iteratorsToDelete;

            //Update or delete children.
            for (auto it = _entityList.begin(); it != _entityList.end();) {
                if ((*it)->IsAlive()) {
                    (*it)->update(mFT);
                }
                else {
                    iteratorsToDelete.push_back(it);
                }
                it++;
            }

            for (auto it : iteratorsToDelete)
            {
                _entityList.erase(it);
            }
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