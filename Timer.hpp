class Timer {
private:
    std::chrono::high_resolution_clock::time_point timerNow = std::chrono::high_resolution_clock::now();
    int seconds = 0;
    float miliseconds = 0.f;

    long long int delay = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->timerNow)).count();

    float posX, posY;
    float sizeX, sizeY;

    sf::RectangleShape *body;

    sf::Color backgroundColor;
    sf::Color borderColor;

    sf::Font font;
    sf::Text text;

public:
    int running = 0;

    Timer(float x, float y, float width, float height){
        delay = 0;

        this->posX = x-5;
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

        
        std::ostringstream milisecondsStream;
        milisecondsStream << std::fixed << std::setprecision(1) << this->miliseconds;

        this->text.setString((milisecondsStream).str());
        this->text.setCharacterSize(25);
        this->text.setFillColor(sf::Color::Red);

        this->text.setStyle(sf::Text::Bold);

        this->text.setPosition(sf::Vector2f(this->posX + 8, this->posY + 3));


        
    }

    ~Timer(){
        delete this->body;
    }

    void start(){
        running = 1;
        this->timerNow = std::chrono::high_resolution_clock::now();
    }

    void stop(){
        running = 0;
        delay = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->timerNow).count());
    }

    void reset(int mode=0){
        miliseconds = 0;
        this->timerNow = std::chrono::high_resolution_clock::now();
        delay = 0;
        if (!mode){
            stop();
        }
    }

    int update(){
        if (this->running){
            if (((std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->timerNow).count())+delay)/50'000 > 1){
                this->timerNow = std::chrono::high_resolution_clock::now();
                this->miliseconds += 0.1;
                delay=0;
                
                std::ostringstream milisecondsStream;
                milisecondsStream << std::fixed << std::setprecision(1) << this->miliseconds;

                this->text.setString((milisecondsStream).str());
            }
        }

        return miliseconds;
    }

    void draw(sf::RenderWindow *window){
        update();

        //printf("%d\n", this->seconds);

        window->draw(*this->body);
        window->draw(this->text);
    }

};