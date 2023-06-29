class Button{
private:
    float posX, posY, sizeX, sizeY, borderSize;
    sf::Color color, borderColor, hoverColor, hoverBorderColor;
    std::string text;
    sf::RectangleShape *body;
    sf::Font font;
    sf::Text Ttext;

    int pressed; // 0 no, 1 hover, 2 yes, 3 up
    int value;
    int *mode;

public:
    Button(float x, float y, float width, float height, std::string text, int *modeModifier, int value){
        this->posX = x;
        this->posY = y;

        this->sizeX = width;
        this->sizeY = height;
        
        this->text = text;
        
        this->body = new sf::RectangleShape(sf::Vector2f(this->sizeX, this->sizeY));
        this->body->setPosition(sf::Vector2f(this->posX , this->posY));

        
        
        if (!this->font.loadFromFile(ASSETSPATH+"JosefinSans-Regular.ttf"))
        {
            exit(1);
        }
        this->Ttext.setFont(this->font); 
        this->Ttext.setString(this->text);
        this->Ttext.setCharacterSize(50);
        this->Ttext.setFillColor(sf::Color::Black);

        this->Ttext.setStyle(sf::Text::Bold | sf::Text::Underlined);

        this->Ttext.setPosition(sf::Vector2f(this->posX + 25, this->posY + 15));

        this->pressed = 0;
        this->value = value;
        this->mode = modeModifier;
    }

    void setBorderSize(float size){
        this->borderSize = size;
        this->body->setOutlineThickness(borderSize);
    }

    void setBodyColor(sf::Color color){
        this->color = color;
        this->body->setFillColor(this->color);
    }

    void setBorderColor(sf::Color color){
        this->borderColor = color;
        this->body->setOutlineColor(this->borderColor);
    }

    void setHoverBodyColor(sf::Color color){
        this->hoverColor = color;
        this->body->setFillColor(this->hoverColor);
    }

    void setHoverBorderColor(sf::Color color){
        this->hoverBorderColor = color;
        this->body->setOutlineColor(this->hoverBorderColor);
    }

    void setColors(sf::Color color, sf::Color borderColor, sf::Color hoverColor, sf::Color hoverBorderColor){
        setBodyColor(color);
        setBorderColor(borderColor);
        setHoverBodyColor(hoverColor);
        setHoverBorderColor(hoverBorderColor);
    }

    void setText(std::string text){
        this->text = text;
        
        this->Ttext.setString(this->text);
    }

    void draw(sf::RenderWindow *window){
        //update
        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        if ((int)this->posX < mouse.x && mouse.x < (int)this->posX+(int)this->sizeX && (int)this->posY < mouse.y && mouse.y < (int)this->posY + (int)this->sizeY){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                this->pressed = 2;
            }else{
                if (this->pressed == 2){
                    this->pressed = 3;
                    *this->mode = value;
                }else{
                    this->pressed = 1;
                }
            }
        }else{
            this->pressed = 0;
        }

        if (pressed!=0){
        this->body->setFillColor(this->hoverColor);
        this->body->setOutlineColor(this->hoverBorderColor);
        }else{
        this->body->setFillColor(this->color);
        this->body->setOutlineColor(this->borderColor);
        }

        //this->body->setPosition


        //draw
        window->draw(*(this->body));
        window->draw(this->Ttext);
    }

};