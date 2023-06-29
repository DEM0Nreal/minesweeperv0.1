class Tile{
private:
    float posX, posY;
    float sizeX, sizeY;

    std::string mouseButton = "";
    int mouseDown = 0;

    sf::RectangleShape *body;

    sf::Font font;
    sf::Text text;

    sf::Color colorFlag;
    sf::Color colorHid;
    sf::Color colorShow;

    Face **Emote;

public:
    int hidden;
    int flagged;
    char value;

    Tile(float x, float y, Face **Emote){
        this->hidden = 1;
        this->flagged = 0;
        this->value = 0;

        sizeX = sizeY = 30;

        this->posX = x;
        this->posY = y;

        this->body = new sf::RectangleShape(sf::Vector2f(this->sizeX, this->sizeY));
        this->body->setPosition(sf::Vector2f(this->posX , this->posY));

        if (!this->font.loadFromFile(ASSETSPATH+"JosefinSans-Regular.ttf"))
        {
            exit(1);
        }
        this->text.setFont(this->font);
        this->text.setCharacterSize(20);

        this->colorFlag = sf::Color(255, 0, 0);
        this->colorHid = sf::Color(255, 255, 255);
        this->colorShow = sf::Color(200, 200, 200);

        this->Emote = Emote;
    }

    void setColor(sf::Color colors){
        colorShow = colors;
    }

    sf::Color getColor(){
        return this->body->getFillColor();
    }

    void show(){
        if (!this->flagged)
            this->hidden = 0;
    }

    void update(char val){
        this->value = val;
        this->text.setString(this->value);

        this->text.setPosition(sf::Vector2f(this->posX+10, this->posY+5));

        switch (val)
        {
        case '1':
            this->text.setFillColor(sf::Color::Red);
            break;
        case '2':
            this->text.setFillColor(sf::Color(255,140,0));
            break;
        case '3':
            this->text.setFillColor(sf::Color::Yellow);
            break;
        case '4':
            this->text.setFillColor(sf::Color(154, 205, 50));
            break;
        case '5':
            this->text.setFillColor(sf::Color::Green);
            break;
        case '6':
            this->text.setFillColor(sf::Color(58, 237, 204));
            break;
        case '7':
            this->text.setFillColor(sf::Color::Cyan);
            break;
        case '8':
            this->text.setFillColor(sf::Color::Blue);
            break;
        case '#':
            this->text.setFillColor(sf::Color::Black);
            break;
        
        default:
            this->text.setFillColor(sf::Color(200, 200, 200));
            break;
        }
    }

    void draw(sf::RenderWindow *window){

        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->mouseButton = "LEFT";
            this->mouseDown = 1;
        }else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            this->mouseButton = "RIGHT";
            this->mouseDown = 1;
        }else if(this->mouseDown){
            this->mouseDown = 0;
        }else{
            this->mouseButton = "";
        }


        if ((int)this->posX < mouse.x && mouse.x < (int)this->posX+(int)this->sizeX && (int)this->posY < mouse.y && mouse.y < (int)this->posY + (int)this->sizeY){
            if (this->mouseButton == "LEFT" && !mouseDown){
                if (!flagged){
                    this->hidden = 0;
                    countRevealed();
                }
                clicked = 1;
                //printf("this->CLICKED\n");

                mouseDown = 0;
            }else if (this->mouseButton == "RIGHT" && !mouseDown){
                if (hidden){
                    this->flagged = !this->flagged;
                    mineCounter->change(!this->flagged);
                }
                mouseDown = 0;
            }

            if (mouseButton!="" && this->hidden && (*this->Emote)->getMood() == 0){
                (*this->Emote)->setMood(1);
            }
            
        }


        if (this->flagged){
            this->body->setFillColor(colorFlag);
        }else if (!this->hidden){
            this->body->setFillColor(colorShow);
        }else{
            this->body->setFillColor(colorHid);
        }

        window->draw(*this->body);

        if (!this->hidden)
            window->draw(this->text);

    }

    ~Tile(){
        delete body;
    }

};