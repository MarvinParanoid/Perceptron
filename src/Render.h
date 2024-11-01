#ifndef PERCEPTRON_RENDER_H
#define PERCEPTRON_RENDER_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Data {
    std::vector<double> *image;
    std::vector<double> *res;
    uint32_t expected;
    uint32_t predicted;
};

class Render : public sf::Drawable, public sf::Transformable {
    sf::RenderWindow mWindow;
    sf::Font mFont;
    const Data *mData;

    static constexpr uint32_t PT_SIZE = 30;
    static constexpr uint32_t IMG_WIDTH = 28;
    static constexpr uint32_t IMG_HEIGHT = 28;
    static constexpr uint32_t PADDING = 20;
    static constexpr uint32_t BORDER_WIDTH = IMG_WIDTH * PT_SIZE;
    static constexpr uint32_t BORDER_HEIGHT = IMG_HEIGHT * PT_SIZE;
    static constexpr uint32_t WIDTH = BORDER_WIDTH + 2 * PADDING + 250;
    static constexpr uint32_t HEIGHT = BORDER_HEIGHT + 2 * PADDING;

    void drawImage(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawInfo(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    explicit Render(const Data *data);
    bool init();
    void render();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::RenderWindow &window() { return mWindow; };
};


#endif//PERCEPTRON_RENDER_H
