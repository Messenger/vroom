#include "System.h"

#include <vector>
#include "../Entity.h"

struct System::Impl
{
    std::vector<Entity> Entities;
};

System::System()
    : pImpl(new Impl())
{
}

System::~System()
{
}

std::vector< Entity >& System::Entities()
{
    return pImpl->Entities;
}

void System::Start()
{

}

void System::Stop()
{

}

void System::Register(const Entity& entity)
{
    pImpl->Entities.push_back(entity);
}
