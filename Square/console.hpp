// It's just to display text and be like console to debug.

sf::Font font;
sf::Text indication;

void LoadFont();
void SetText(sf::Text& txt, sf::String str);


void LoadFont() {
    if (!font.loadFromFile("font/Roboto-Medium.ttf")) {
        std::cout << "Erreur font" << std::endl;
    }
}

void SetText(sf::Text& txt, sf::String str) {
    txt.setFont(font);
    txt.setString(str);
    txt.setCharacterSize(20);
    txt.setFillColor(sf::Color::White);
    txt.setStyle(sf::Text::Bold);
}
