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
#include <cmath>

#include "SDL2/SDL.h"
#include "sdl/Engine.h"
#include "sdl/Control.h"
#include "sdl/Render.h"
#include "sdl/Music.h"
#include "Systems/Collision.h"
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
#include "Components/State.h"
#include "Distance.h"
#include "Point.h"

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
    sprite->Direction = 90;
    
    auto position = std::make_shared<Position>();
    position->Value = { 50, 50};
    
    car.Add(speed);
    car.Add(sprite);
    car.Add(size);
    car.Add(keys);
    car.Add(stats);
    car.Add(std::make_shared<Acceleration>());
    car.Add(std::make_shared<Rotation>());
    car.Add(std::make_shared<Direction>());
    car.Add(position);
    car.Add(std::make_shared<State>());
    return car;
}

static Entity CreateWall(const Point& start, const Point& end)
{
    Entity wall;
    
    auto size = std::make_shared<Size>();
    size->Width = Distance(start, end) + 10;
    size->Height = 10;
    
    auto sprite = std::make_shared<Sprite>();
    sprite->Offset = {0, 40/200.};
    sprite->Width = 40/320.;
    sprite->Height = 10/200.;

    auto direction = std::make_shared<Direction>();
    auto difference = end - start;
    direction->Value = Angle::Radians(std::atan2(difference.Y().Value(), difference.X().Value()));
    
    auto position = std::make_shared<Position>();
    position->Value = start + Point(difference.X().Value() / 2., difference.Y().Value() / 2.);
    
    wall.Add(size);
    wall.Add(sprite);
    wall.Add(direction);
    wall.Add(position);
    return wall;
}

int main(int argc, char **argv)
{
    Engine engine;

    auto controls = make(new Control(engine.GetInput()));
    auto turning = make(new Turning());
    auto accelerate = make(new Accelerate());
    auto collision = make(new Collision());
    auto render = make(new Render());
    auto debug = make(new Debug());
    auto music = make(new Music());
    
    auto cars = std::vector<Entity>{
        CreateCar(),
        CreateCar()
    };
    auto keys = cars[0].Get<Keys>();
    keys->TurnLeft = SDLK_a;
    keys->TurnRight = SDLK_d;
    keys->Accelerate = SDLK_w;
    cars[0].Get<Position>()->Value = { 100, 100 };

    for(auto& car : cars)
    {
        controls->Register(car);
        turning->Register(car);
        accelerate->Register(car);
        collision->Register(car);
        render->Register(car);
        debug->Register(car);
    }
    
    auto walls = {
        CreateWall({200,200}, {800,200}),
        CreateWall({200,200}, {200,600}),
        CreateWall({200,600}, {800,600}),
        CreateWall({400,400}, {1000,400}),
        CreateWall({0,0},     {0,800}),
        CreateWall({0,800},   {1000,800}),
        CreateWall({1000,800},{1000,0}),
        CreateWall({1000,0},  {0,0})
    };
    
    for(auto& wall : walls)
    {
        collision->Register(wall);
        render->Register(wall);
    }

    engine.Add(std::move(controls));
    engine.Add(std::move(accelerate));
    engine.Add(std::move(turning));
    engine.Add(std::move(collision));
    engine.Add(std::move(debug));
    engine.Add(std::move(render));
    engine.Add(std::move(music));
    
    engine.Run();
    
    return 0;
}
