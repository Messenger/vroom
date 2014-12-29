#ifndef SYSTEMS_SYSTEM_H_
#define SYSTEMS_SYSTEM_H_

#include <memory>
#include <vector>

class Time;
class Entity;

class System
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;

protected:
    std::vector<Entity>& Entities();
    
public:
    System();
    virtual ~System();
    
    virtual void Start();
    virtual void Update(const Time& time) = 0;
    virtual void Stop();
    void Register(const Entity& entity);
};

#endif