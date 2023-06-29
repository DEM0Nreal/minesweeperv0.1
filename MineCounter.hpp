class MineCounter{
private:
    int value=0;

    float posX, posY;
    float sizeX, sizeY;

    sf::RectangleShape *body;

    sf::Color backgroundColor;
    sf::Color borderColor;

    sf::Font font;
    sf::Text text;
public:

    MineCounter(float x, float y, float width, float height){
        this->posX = x+5;
        this->posY = y;
        this->sizeX = width;
        this->sizeY = height;

        backgroundColor = sf::Color(50, 50, 50);
        borderColor = sf::Color(240, 240, 240);

        this->body = new sf::RectangleShape(sf::Vector2f(this->sizeX, this->sizeY));
        this->body->setPosition(sf::Vector2f(this->posX, this->posY));

        this->body->setOutlineThickness(5.f);
        this->body->setOutlineColor(borderColor);
        
        this->body->setFillColor(backgroundColor);

        if (!this->font.loadFromFile(ASSETSPATH+"JosefinSans-Regular.ttf"))
        {
            exit(1);
        }
        this->text.setFont(this->font); 
        this->text.setString((std::to_string(this->value)));
        this->text.setCharacterSize(25);
        this->text.setFillColor(sf::Color::Red);

        this->text.setStyle(sf::Text::Bold);

        this->text.setPosition(sf::Vector2f(this->posX + 8, this->posY + 1));
    }

    ~MineCounter(){
        delete this->body;
    }

    void setMines(int amount){
        this->value = amount;
    }

    void change(int x){
        if (x){
            this->value++;
        }else{
            this->value--;
        }
    }

    void update(){
        this->text.setString(std::to_string(this->value));
    }

    void draw(sf::RenderWindow *window){
        this->update();

        window->draw(*this->body);
        window->draw(this->text);
    }

};