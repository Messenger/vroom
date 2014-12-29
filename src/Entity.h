#ifndef ENTITY_H_
#define ENTITY_H_

#include <typeindex>
#include <memory>
#include <map>

class Component;

class Entity
{
    std::map<std::type_index, std::shared_ptr<Component>> components;
    
public:
    template <typename T>
    void Add(std::shared_ptr<T> component)
    {
        components[std::type_index(typeid(*component))] = component;
    }
    
    template <typename T>
    std::shared_ptr<T> Get()
    {
        std::type_index index(typeid(T));
        if(components.count(index) != 0)
        {
            return std::static_pointer_cast<T>(components[index]);
        }
        else
        {
            return std::shared_ptr<T>();
        }
    }
};

#endif