#pragma once

#include <entt/entt.hpp>
#include <iostream>

namespace Sage {

class Entity
{
public:
    Entity() : _handle(entt::null), _sceneRegistry(NULL) {}
    Entity(entt::entity handle, entt::registry *registry)
        : _handle(handle), _sceneRegistry(registry)
    {}

    ~Entity();

    void destroy();

    template <typename T>
    bool hasComponent()
    {
        return _sceneRegistry->try_get<T>(_handle) != nullptr;
    }

    template <typename T, typename... Args>
    T &addComponent(Args &&...args)
    {
        return _sceneRegistry->emplace<T>(_handle, std::forward<Args>(args)...);
    }

    template <typename T>
    T &getComponent()
    {
        if (! hasComponent<T>())
        {
            std::cerr << "Entity does not have this component\n";
        }
        return _sceneRegistry->get<T>(_handle);
    }

    template <typename T>
    void removeComponent()
    {
        if (! hasComponent<T>())
            return;
        _sceneRegistry->remove<T>(_handle);
    }

    template <typename T>
    T &replaceComponent(T new_component)
    {
        _sceneRegistry->replace<T>(_handle, new_component);
        return _sceneRegistry->get<T>(_handle);
    }

    operator bool() const
    {
        return _handle != entt::null;
    }

    bool operator==(const Entity &other) const
    {
        return _handle == other._handle && _sceneRegistry == other._sceneRegistry;
    }

    bool operator!=(const Entity &other) const
    {
        return ! (*this == other);
    }

    entt::entity getHandle()
    {
        return _handle;
    }

    uint32_t getUuid()
    {
        return (uint32_t)_handle;
    }

private:
    entt::entity _handle = entt::null;
    entt::registry *_sceneRegistry;
};

}  // namespace Sage