#include "Render.h"

Render::Render() {
    init();
}

bool Render::init() {
    setPosition(50.f, 50.f);
    _window.create(sf::VideoMode(420, 420), "Perceptron");
    _window.setFramerateLimit(60);
    return true;
}

void Render::render() {
    _window.clear();
    _window.draw(*this);
    _window.display();
}

void Render::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rectangle(sf::Vector2f(15.f, 15.f));
    rectangle.setFillColor(sf::Color(100, 250, 50));
    for (uint32_t i = 0; i < _image->size(); i++) {
        if ((*_image)[i] == 1) {
            sf::Vector2f position((i % 28) * 15, (i / 28) * 15);
            rectangle.setPosition(position);
            target.draw(rectangle, states);
        }
    }
}

void Render::setImage(const std::vector<double> *image) {
    _image = image;
}
