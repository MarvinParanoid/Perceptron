#include "Render.h"

Render::Render() {
    init();
}

bool Render::init() {
    setPosition(50.f, 50.f);
    mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Perceptron");
    //mWindow.setFramerateLimit(120);
    mFont.loadFromFile("../RobotoMono-Regular.ttf");
    return true;
}

void Render::render() {
    mWindow.clear({255, 255, 255});
    mWindow.draw(*this);
    mWindow.display();
}

void Render::drawImage(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rectangle({BORDER_WIDTH, BORDER_HEIGHT});
    rectangle.setPosition(PADDING, PADDING);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor({0, 0, 0});
    target.draw(rectangle, states);

    rectangle.setSize({PT_SIZE, PT_SIZE});
    rectangle.setOutlineThickness(0);
    rectangle.setFillColor({0, 0, 0});
    for (uint32_t i = 0; i < mData->image->size(); i++) {
        if ((*mData->image)[i] == 1) {
            rectangle.setPosition((i % IMG_WIDTH) * PT_SIZE, (i / IMG_HEIGHT) * PT_SIZE);
            target.draw(rectangle, states);
        }
    }
}

void Render::drawInfo(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text("", mFont, 30);
    text.setPosition(BORDER_WIDTH + PADDING * 2, PADDING);
    text.setFillColor({0, 0, 0});
    std::string str = "Expected: " + std::to_string(mData->expected) + "\nPredicted: " + std::to_string(mData->predicted);
    for (uint32_t i = 0; i < mData->res->size(); i++) {
        str += "\n" + std::to_string(i) + ": " + std::to_string((*mData->res)[i]);
    }
    text.setString(str);
    target.draw(text, states);
}

void Render::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    drawImage(target, states);
    drawInfo(target, states);
}

void Render::updateData(const Data *data) {
    mData = data;
}
