#include "EntityManager.h"

namespace csl {
    std::vector<std::unique_ptr<Entity>>& EntityManager::GetEntityVector() {
        return _entityList;
    }

    void EntityManager::update(float mFT)
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

    void EntityManager::propagateEvent(EngineEvent& e) {
        for (auto& entity : _entityList) {
            entity->propagateEvent(e);
        }
    }

    Entity* EntityManager::addEntity()
    {
        Entity* e(new Entity(this));
        std::unique_ptr<Entity> uPtr{ e };
        _entityList.emplace_back(std::move(uPtr));
        return e;
    }


    Entity* EntityManager::addEntity(Entity* e)
    {
        std::unique_ptr<Entity> uPtr{ e };
        _entityList.emplace_back(std::move(uPtr));
        return e;
    }
}