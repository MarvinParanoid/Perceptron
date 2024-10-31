#ifndef PERCEPTRON_RENDER_H
#define PERCEPTRON_RENDER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Render : public sf::Drawable, public sf::Transformable {
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _text;
    const std::vector<double> *_image;

public:
    Render();
    void setImage(const std::vector<double>* image);
    bool init();
    void render();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::RenderWindow &window() { return _window; };
};


#endif//PERCEPTRON_RENDER_H
