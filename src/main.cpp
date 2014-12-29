/*
#include "sdl/Game.h"
#include "World.h"
#include "Car.h"
#include "Wall.h"
#include "Point.h"

int main(int argc, char **argv)
{
    Game game;
    World world;
    Car player1;
    player1.Position({80, 80});
    world.Cars().push_back(std::move(player1));
    world.Walls().push_back(std::move(Wall({200,200}, {800,200})));
    world.Walls().push_back(std::move(Wall({200,200}, {200,600})));
    world.Walls().push_back(std::move(Wall({200,600}, {800,600})));
    world.Walls().push_back(std::move(Wall({400,400}, {1000,400})));
    world.Walls().push_back(std::move(Wall({0,0},     {0,800})));
    world.Walls().push_back(std::move(Wall({0,800},   {1000,800})));
    world.Walls().push_back(std::move(Wall({1000,800},{1000,0})));
    world.Walls().push_back(std::move(Wall({1000,0},  {0,0})));
    
    while (game.Running()) {
        game.UpdateFrame(world);
    }
    return 0;
}
*/

#include <memory>

#include "SDL2/SDL.h"
#include "sdl/Engine.h"
#include "sdl/Control.h"
#include "sdl/Render.h"
#include "Systems/Movement.h"
#include "Systems/Accelerate.h"
#include "Systems/Turning.h"
#include "Systems/Debug.h"
#include "Entity.h"
#include "Components/Keys.h"
#include "Components/Stats.h"
#include "Components/Acceleration.h"
#include "Components/Rotation.h"
#include "Components/Direction.h"
#include "Components/Velocity.h"
#include "Components/Position.h"
#include "Components/Size.h"
#include "Components/Sprite.h"

template<typename T>
std::unique_ptr<T> make(T* value) { return std::unique_ptr<T>(value); }

static Entity CreateCar()
{
    Entity car;
    auto keys = std::make_shared<Keys>();
    keys->TurnLeft = SDLK_LEFT;
    keys->TurnRight = SDLK_RIGHT;
    keys->Accelerate = SDLK_UP;
    
    auto stats = std::make_shared<Stats>();
    stats->AccelerationRate = 0.001;
    stats->DecelerationRate = -0.001;
    stats->TurningRate = 0.25;

    auto speed = std::make_shared<Velocity>();
    speed->Max = 0.5;
    
    auto size = std::make_shared<Size>();
    size->Width = 40;
    size->Height = 40;
    
    auto sprite = std::make_shared<Sprite>();
    sprite->Offset = {0, 0};
    sprite->Width = 40/320.;
    sprite->Height = 40/200.;
    
    car.Add(speed);
    car.Add(sprite);
    car.Add(size);
    car.Add(keys);
    car.Add(stats);
    car.Add(std::make_shared<Acceleration>());
    car.Add(std::make_shared<Rotation>());
    car.Add(std::make_shared<Direction>());
    car.Add(std::make_shared<Position>());
    return car;
}

int main(int argc, char **argv)
{
    Engine engine;

    auto controls = make(new Control(engine.GetInput()));
    auto turning = make(new Turning());
    auto accelerate = make(new Accelerate());
    auto movement = make(new Movement());
    auto render = make(new Render());
    auto debug = make(new Debug());
    
    auto car = CreateCar();
    auto car2 = CreateCar();
    auto keys = car2.Get<Keys>();
    keys->TurnLeft = SDLK_a;
    keys->TurnRight = SDLK_d;
    keys->Accelerate = SDLK_w;
    car2.Get<Position>()->Value = { 100, 100 };
    
    controls->Register(car);
    turning->Register(car);
    accelerate->Register(car);
    movement->Register(car);
    render->Register(car);
    debug->Register(car);
    controls->Register(car2);
    turning->Register(car2);
    accelerate->Register(car2);
    movement->Register(car2);
    render->Register(car2);
    debug->Register(car2);
    
    engine.Add(std::move(controls));
    engine.Add(std::move(turning));
    engine.Add(std::move(accelerate));
    engine.Add(std::move(debug));
    engine.Add(std::move(movement));
    engine.Add(std::move(render));
    
    engine.Run();
    
    return 0;
}
