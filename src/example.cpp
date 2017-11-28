#include "oxygine-framework.h"
#include <functional>
#include <iostream>
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;


class MainActor: public Actor
{
public:
    spSprite    _button;
    bool _moving;
    Vector2 _position, _clickPosition;

    MainActor() : _moving{false}, _position(0, 0), _clickPosition(0, 0)
    {
        spSprite button = new Sprite();
        button->setResAnim(gameResources.getResAnim("button"));
        button->setPosition(this->_position);

        button->addEventListener(TouchEvent::CLICK, [this](Event * e) {
            this->buttonClicked(e);
        });
        button->addEventListener(TouchEvent::TOUCH_DOWN, [this](Event * e) {
            TouchEvent* foo = (TouchEvent*) e;
            this->_moving = true;
            this->_clickPosition = foo->position;
        });
        button->addEventListener(TouchEvent::TOUCH_UP, [this](Event * e) {
            this->_moving = false;
        });
        button->addEventListener(TouchEvent::MOVE, [this](Event * e) {
            TouchEvent* foo = (TouchEvent*) e;
            if (!this->_moving) {
                return;
            }

            this->_position += (foo->position - this->_clickPosition);
            this->_button->setPosition(this->_position);
        });

        //attach button as child to current actor
        addChild(button);
        _button = button;
    }

    void buttonClicked(Event* event)
    {
        std::cout<<"clicked"<<std::endl;
    }
};
typedef oxygine::intrusive_ptr<MainActor> spMainActor;

void example_preinit() {}

void example_init()
{
    gameResources.loadXML("res.xml");

    spMainActor actor = new MainActor;
    getStage()->addChild(actor);
}

void example_update()
{
}

void example_destroy()
{
    gameResources.free();
}
