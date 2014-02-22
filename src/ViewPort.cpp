#include "ViewPort.h"
#include "Distance.h"
#include "Point.h"
#include "Car.h"

struct ViewPort::Impl
{
    Distance Height {480};
    Distance Width {640};
    Point Offset {0,0};
    Distance MinimumScreenDistance {80};
};

ViewPort::ViewPort()
    : pImpl(new Impl{})
{

}

ViewPort::~ViewPort()
{

}

Distance ViewPort::Height() const
{
    return pImpl->Height;
}

Distance ViewPort::Width() const
{
    return pImpl->Width;
}

Point ViewPort::Offset() const
{
    return pImpl->Offset;
}

void ViewPort::Update(const Car& car)
{
    auto carX = car.Position().X();
    auto carY = car.Position().Y();
    auto offsetX = pImpl->Offset.X();
    auto offsetY = pImpl->Offset.Y();
    
    auto topLimit = offsetY + pImpl->Height - pImpl->MinimumScreenDistance;
    if(carY > topLimit)
    {
        pImpl->Offset += Point{0, carY - topLimit};
    }
    
    auto bottomLimit = offsetY + pImpl->MinimumScreenDistance;
    if(carY < bottomLimit)
    {
        pImpl->Offset += Point{0, carY - bottomLimit};
    }
    
    auto rightLimit = offsetX + pImpl->Width - pImpl->MinimumScreenDistance;
    if(carX > rightLimit)
    {
        pImpl->Offset += Point{carX - rightLimit, 0};
    }

    auto leftLimit = offsetX + pImpl->MinimumScreenDistance;
    if(carX < leftLimit)
    {
        pImpl->Offset += Point{carX - leftLimit, 0};
    }
}
