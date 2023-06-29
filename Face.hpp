class Face{
private:
    int mood; // 0 = normal ; 1 = triggered ; 2 = dead ; 3 = win ;

    float posX, posY, sizeX, sizeY;

    sf::RectangleShape *body;
    sf::CircleShape *face;
    
    sf::Color bodyBackgroundColor;
    sf::Color bodyOffsetColor;

    sf::Color faceColor;

    int *dead;
    std::string mouseButton;
    int mouseDown;

public:
    Face(float x, float y, float width, float height, int *dead){
        this->mood = 0;

        this->posX = x;
        this->posY = y;
        
        this->sizeX = width;
        this->sizeY = height;

        this->body = new sf::RectangleShape(sf::Vector2f(this->sizeX, this->sizeY));
        this->body->setPosition(sf::Vector2f(this->posX, this->posY));

        this->face = new sf::CircleShape(this->sizeX/2-2);
        this->face->setPosition(sf::Vector2f(this->posX+2, this->posY+2));

        this->dead = dead;

        this->mouseButton = "";
        this->mouseDown = 0;
    }

    ~Face(){
        delete body;
        delete face;
    }

    void update(){
        switch (mood)
        {
        case 0:
            faceColor = sf::Color::Yellow;
            break;
        case 1:
            faceColor = sf::Color(200, 200, 255);
            break;
        case 2:
            faceColor = sf::Color(150, 80, 80);
            break;
        case 3:
            faceColor = sf::Color(100, 255, 120);
            break;
        default:
            faceColor = sf::Color::Yellow;
            break;
        }
    }

    void setMood(int mood){
        this->mood = mood;
        this->face->setFillColor(this->faceColor);
    }

    int getMood(){
        return this->mood;
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
                *this->dead = 6;
                //printf("DEAD == 6:::!!!\n");
                mouseDown = 0;
            }else if (this->mouseButton == "RIGHT" && !mouseDown){
                *this->dead = 3;

                mouseDown = 0;
            }
        }




        update();
        this->face->setFillColor(this->faceColor);


        window->draw(*this->body);
        window->draw(*this->face);
    }

};