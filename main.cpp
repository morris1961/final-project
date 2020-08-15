#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <windows.h>

int FASTFRAME = 300000;
int SLOWFRAME = 100000;
int Up = 8, Left = 9, Down = 10, Right = 11;
sf::Vector2f recSize(30, 45);

class Entity
{
public:
    sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::Vector2i source;
    sf::Texture texture;
    sf::Clock clock;
};

class Npc: public Entity
{
private:
public:
//    Npc(sf::String &filename);
    void setPosition(float x, float y);
    int maxDialog[6];
    int num;
    std::string dialog[6][6];
    bool next;
};

class Player: public Entity
{
private:
    float frameCounter, switchFrame, frameSpeed, walkSpeed, pace;
    bool canMoveUp, canMoveDown, canMoveLeft, canMoveRight, upDateFrame;
public:
    bool computer, cap, codeFromKong;
    bool codeFromLu, data1, data2, data3, data4, dataFromLiu;
    Player(sf::String &filename);
    bool getUpDateFrame();
    void moveMent(sf::Sprite *bimage);
    void frame();
    void setUpDateFrame(bool upDateFrame);
    bool isCollide(Npc *n);
    bool isCollide(sf::RectangleShape *rect);
    void cantMove();
    bool canTalk(Npc *n);
    void talking();
    void notTalking();
    void setTexture(sf::String &filename);
};

class Wei: public Npc
{
private:
public:
    Wei(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Music *endmusic, sf::Music *bmusic);
    bool first = true, fin = false;
};

class Kong: public Npc
{
private:
public:
    Kong(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting);
    bool first = false, guessRight = false, guessWrong = false, guessing = false;
};

class Longxi: public Npc
{
private:
public:
    Longxi(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting);
    bool first = false, guessRight = false, guessWrong = false, guessing = false;
};

class Zhang: public Npc
{
private:
public:
    Zhang(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk);
    bool guessing = false, guessRight = false, guessWrong = false;
};

class Hu: public Npc
{
private:
public:
    bool runningGround = false, runningCompelet = true;
    Hu(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Music *runmusic, sf::Music *bmusic);
};

class Liu: public Npc
{
private:
public:
    Liu(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting);
    bool first = false, guessRight = false, guessWrong = false, guessing = false;
};

class Lu: public Npc
{
private:
public:
    Lu(sf::String &filename);
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Sound *lutransport);
    int hwCnt = 0;
};

class Chest
{
private:
public:
    sf::RectangleShape rect[4];
    int maxDialog[6];
    int num = 0;
    std::string dialog[6][6];
    bool next = false;
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Sound *chestSound);
};

class Stone
{
private:
public:
    sf::RectangleShape rect;
    int maxDialog[6];
    int num = 0;
    std::string dialog[6][6];
    bool next = false;
    void talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk);
};

Player::Player(sf::String &filename)
{
    texture.loadFromFile(filename);
    rect.setSize(recSize);
    sprite.setPosition(145, 62);//(768, 765);
    sprite.setTexture(texture);
    frameCounter = 0;
    switchFrame = 100;
    frameSpeed = FASTFRAME;
    walkSpeed = 300;
    pace = 0;
    canMoveUp = true; canMoveDown = true; canMoveLeft = true; canMoveRight = true; upDateFrame = false;
    computer = false; cap = false;
    codeFromKong = false; codeFromLu = false;
    data1 = false; data2 = false; data3 = false; data4 = false; dataFromLiu = false;
    source = sf::Vector2i(1, Down);
    sprite.setTextureRect(sf::IntRect(source.x*64, source.y*64, 64, 64));
    rect.setPosition(sprite.getPosition());
}

void Player::moveMent(sf::Sprite *bimage)
{
    pace = walkSpeed * clock.restart().asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {

        if(canMoveUp)
        {   upDateFrame = true;
            source.y = Up;
            if(sprite.getPosition().y > 0)
            {
                sprite.move(0,-pace);
                frameSpeed = SLOWFRAME;
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
//                {
//                    frameSpeed = FASTFRAME;
//                    sprite.move(0,-1.5*pace);
//                }
            }
            canMoveUp = true;
            canMoveDown = true;
            canMoveLeft = true;
            canMoveRight = true;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(canMoveDown)
        {
            upDateFrame = true;
            source.y = Down;
            if(sprite.getPosition().y+64 < bimage->getGlobalBounds().height)
            {
                sprite.move(0,pace);
                frameSpeed = SLOWFRAME;
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
//                {
//                    frameSpeed = FASTFRAME;
//                    sprite.move(0,1.5*pace);
//                }
            }
            canMoveUp = true;
            canMoveDown = true;
            canMoveLeft = true;
            canMoveRight = true;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {

        if(canMoveRight)
        {
            source.y = Right;
            upDateFrame = true;
            if(sprite.getPosition().x+64 < bimage->getGlobalBounds().width)
            {
                sprite.move(pace,0);
                frameSpeed = SLOWFRAME;
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
//                {
//                    frameSpeed = FASTFRAME;
//                    sprite.move(1.5*pace, 0);
//                }
            }
            canMoveUp = true;
            canMoveDown = true;
            canMoveLeft = true;
            canMoveRight = true;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {

        if(canMoveLeft)
        {
            source.y = Left;
            upDateFrame = true;
            if(sprite.getPosition().x > 0)
            {
                sprite.move(-pace,0);
                frameSpeed = SLOWFRAME;
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
//                {
//                    frameSpeed = FASTFRAME;
//                    sprite.move(-1.5*pace,0);
//                }
            }
            canMoveUp = true;
            canMoveDown = true;
            canMoveLeft = true;
            canMoveRight = true;
        }
    }
    rect.setPosition(sprite.getPosition());
}

void Player::frame()
{
    if(upDateFrame)
       frameCounter += frameSpeed * clock.getElapsedTime().asSeconds();
    if(frameCounter >= switchFrame)
    {
        frameCounter = 0;
        source.x++;
        if(source.x * 64 >= 64*9)
        source.x = 0;
    }
    sprite.setTextureRect(sf::IntRect(source.x*64, source.y*64, 64, 64));
}

bool Player::getUpDateFrame()
{
    return upDateFrame;
}

void Player::setUpDateFrame(bool upDateFrame)
{
    this->upDateFrame = upDateFrame;
}

bool Player::isCollide(Npc *n)
{
    if(this->rect.getGlobalBounds().intersects(n->rect.getGlobalBounds()))
        return true;
    return false;
}

bool Player::isCollide(sf::RectangleShape *rect)
{
    if(this->rect.getGlobalBounds().intersects(rect->getGlobalBounds()))
        return true;
    return false;
}

void Player::cantMove()
{
    if(source.y == Up)
    {
        canMoveUp = false;
        sprite.move(0, 1);
    }
    else if(source.y == Down)
    {
        canMoveDown = false;
        sprite.move(0, -1);
    }
    else if(source.y == Right)
    {
        canMoveRight = false;
        sprite.move(-1, 0);
    }
    else if(source.y == Left)
    {
        canMoveLeft = false;
        sprite.move(1, 0);
    }
}

bool Player::canTalk(Npc *n)
{
    rect.setPosition(sprite.getPosition().x-10, sprite.getPosition().y-10);
    rect.setSize(sf::Vector2f (recSize.x+20, recSize.y+20));
    if(this->rect.getGlobalBounds().intersects(n->rect.getGlobalBounds()))
    {
        rect.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        rect.setSize(recSize);
        return true;
    }
    rect.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    rect.setSize(recSize);
    return false;
}

void Player::talking()
{
    canMoveDown = false;
    canMoveUp = false;
    canMoveLeft = false;
    canMoveRight = false;
}

void Player::notTalking()
{
    canMoveDown = true;
    canMoveUp = true;
    canMoveLeft = true;
    canMoveRight = true;
}

void Npc::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
    rect.setPosition(x, y);
}

void Player::setTexture(sf::String &filename)
{
    if(!texture.loadFromFile(filename));
        std::cout << "HANSCAP fail" << std::endl;
}

Wei::Wei(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Wei::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Music *endmusic, sf::Music *bmusic)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            if(whatTalk == 0)
            {
                first = false;
            }
            else if(whatTalk == 2)
            {
                fin = true;
                bmusic->stop();
                endmusic->play();
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Kong::Kong(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Kong::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            if(whatTalk == 0)
            {
                first = true;
                isTexting = true;
                guessing = true;
            }
            else if(whatTalk == 1)
            {
                guessWrong = false;
                isTexting = true;
            }
            else if(whatTalk == 2)
            {
                guessing = false;
                p1->codeFromKong = true;
                p1->notTalking();
            }
            else if(whatTalk == 3)
            {
                p1->notTalking();
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Longxi::Longxi(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Longxi::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            if(whatTalk == 0)
            {
                first = true;
                isTexting = true;
                guessing = true;
            }
            else if(whatTalk == 1)
            {
                guessing = false;
                p1->notTalking();
            }
            else if(whatTalk == 2)
            {
                guessing = false;
                p1->computer = true;
                p1->notTalking();
            }
            else if(whatTalk == 3)
            {
                p1->notTalking();
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Zhang::Zhang(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Zhang::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            if(whatTalk == 0)
            {
                p1->talking();
                p1->sprite.setPosition(2223, 810);
                p1->source.y = Right;
                guessing = true;
            }
            else if(whatTalk == 1)
            {
                guessing = false;
            }
            else if(whatTalk == 2)
            {
                guessing = false;
                p1->cap = true;
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Hu::Hu(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Hu::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Music *runmusic, sf::Music *bmusic)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            if(whatTalk == 0)
            {
                runningGround = true;
                runningCompelet = false;
                p1->sprite.setPosition(1743, 305);
                bmusic->pause();
                runmusic->play();
            }
            if(whatTalk == 2)
            {
                runningGround = false;
                runmusic->stop();
                bmusic->play();
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Liu::Liu(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Liu::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, bool &isTexting)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            if(whatTalk == 0)
            {
                first = true;
                isTexting = true;
                guessing = true;
            }
            else if(whatTalk == 1)
            {
                guessWrong = false;
                isTexting = true;
            }
            else if(whatTalk == 2)
            {
                guessing = false;
                p1->dataFromLiu = true;
                p1->notTalking();
            }
            else if(whatTalk == 3)
            {
                p1->notTalking();
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

Lu::Lu(sf::String &filename)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    rect.setSize(recSize);
    sprite.setTextureRect(sf::IntRect(64, Down*64, 64, 64));
    rect.setPosition(sprite.getPosition());
    num = 0;
    next = false;
}

void Lu::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Sound *lutransport)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            if(whatTalk == 0)
            {
                p1->sprite.setPosition(3121, 1487);
                p1->source.y = Down;
                hwCnt++;
                if(hwCnt == 1)
                {
                    setPosition(1010,720);
                }
                else if(hwCnt == 2)
                {
                    setPosition(2387, 658);
                }
                lutransport->play();
            }
            else if (whatTalk == 1)
            {
                p1->codeFromLu = true;
            }
            else if (whatTalk == 2)
            {
                p1->computer = false;
                hwCnt++;
                if(hwCnt == 1)
                {
                    setPosition(1010,720);
                }
                else if(hwCnt == 2)
                {
                    setPosition(2387, 658);
                }
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}

void Chest::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk, sf::Sound *chestSound)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            if(whatTalk == 0)
            {
                p1->data1 = true;
            }
            else if(whatTalk == 1)
            {
                p1->data2 = true;
            }
            else if(whatTalk == 2)
            {
                p1->data3 = true;
            }
            else if(whatTalk == 3)
            {
                p1->data4 = true;
            }
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        chestSound->play();
        next = true;
    }
}

void Stone::talk(Player *p1, sf::Text *text, sf::RectangleShape *diaBox, int whatTalk)
{
    if(next)
    {
        num++;
        if(num > maxDialog[whatTalk] -1)
        {
            text->setFillColor(sf::Color::Transparent);
            diaBox->setFillColor(sf::Color::Transparent);
            diaBox->setOutlineColor(sf::Color::Transparent);
            next = false;
            num = 0;
            p1->notTalking();
            p1->codeFromLu = true;
            p1->codeFromKong = true;
            p1->data1 = true;
            p1->data2 = true;
            p1->data3 = true;
            p1->data4 = true;
            p1->dataFromLiu = true;
        }
        else
            text->setString(dialog[whatTalk][num]);
    }
    else
    {
        text->setString(dialog[whatTalk][num]);
        next = true;
    }
}
void makeWall(std::vector<sf::RectangleShape> *wallarray);
void makeField(std::vector<sf::RectangleShape> *fieldarray);
void makeSecret(std::vector<sf::RectangleShape> *secretarray);

int main()
{
    sf::Vector2i screen(1600, 800);
    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "06", sf::Style::Titlebar|sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    int count = 0; bool begin = true; bool isTexing = false; bool isTalking = false; bool isCap = false;

    //for text
    sf::RectangleShape diaBox(sf::Vector2f(screen.x - 500, 150));
    sf::Color color(255, 255 , 205);
    diaBox.setFillColor(sf::Color::Transparent);
    sf::Font font;
    if (!font.loadFromFile("Gabriola.ttf"))
        return EXIT_FAILURE;
    sf::Text text(" ", font, 30);
    text.setFillColor(sf::Color::Transparent);

    //for wei bound
    sf::RectangleShape weiBound1(sf::Vector2f(10, 50));
    weiBound1.setPosition(433, 50);
    sf::RectangleShape weiBound2(sf::Vector2f(60, 10));
    weiBound2.setPosition(385, 510);

    //for begin
    sf::Texture beginTexture;
    sf::Sprite beginImage;
    if(!beginTexture.loadFromFile("picture\\begin.png"))
        std::cout << "load beginImage fail !" << std::endl;
    beginImage.setTexture(beginTexture);

    sf::RectangleShape playGame(sf::Vector2f(340,100));
    playGame.setPosition(670, 600);
    sf::CircleShape help(50);
    help.setPosition(1240, 580);
    sf::RectangleShape quit(sf::Vector2f(95,95));
    quit.setPosition(320, 585);

    //for quit
    bool isQuit = false;
    sf::Texture quitTexture;
    sf::Sprite quitImage;
    if(!quitTexture.loadFromFile("picture\\suretoquit.png"))
        std::cout << "load suretoquit fail !" << std::endl;
    quitImage.setTexture(quitTexture);
    sf::RectangleShape no(sf::Vector2f(175,175));
    no.setPosition(740, 385);

    //for help
    bool ishelp = false;
    sf::Texture helpTexture;
    sf::Sprite helpImage;
    if(!helpTexture.loadFromFile("picture\\help.png"))
        std::cout << "load help fail !" << std::endl;
    helpImage.setTexture(helpTexture);
    sf::RectangleShape control(sf::Vector2f(180,175));
    control.setPosition(1300, 490);

    //for control
    bool iscontrol = false;
    sf::Texture controlTexture;
    sf::Sprite controlImage;
    if(!controlTexture.loadFromFile("picture\\control.png"))
        std::cout << "load control fail !" << std::endl;
    controlImage.setTexture(controlTexture);
    sf::RectangleShape home(sf::Vector2f(100,110));
    home.setPosition(1500, 620);

    //for end
    sf::Texture endTexture;
    sf::Sprite endImage;
    if(!endTexture.loadFromFile("picture\\end.png"))
        std::cout << "load endImage fail !" << std::endl;
    endImage.setTexture(endTexture);

    sf::RectangleShape exit(sf::Vector2f(95,95));
    exit.setPosition(780 ,585);
    sf::CircleShape more(50);
    more.setPosition(1215, 580);
    sf::RectangleShape discoverbug(sf::Vector2f(95,95));
    discoverbug.setPosition(325, 585);

    //for discoverbug
    bool isbug = false;
    sf::Texture bugTexture;
    sf::Sprite bugImage;
    if(!bugTexture.loadFromFile("picture\\discoverbug.png"))
        std::cout << "load bugImage fail !" << std::endl;
    bugImage.setTexture(bugTexture);
    sf::RectangleShape backbug(sf::Vector2f(160,100));
    backbug.setPosition(1200 ,600);
    sf::Text backbugtext("Back", font, 100);
    backbugtext.setPosition(sf::Vector2f(backbug.getPosition().x, backbug.getPosition().y-20));

    //for more
    bool ismore = false;
    sf::Texture moreTexture;
    sf::Sprite moreImage;
    if(!moreTexture.loadFromFile("picture\\more.png"))
        std::cout << "load moreImage fail !" << std::endl;
    moreImage.setTexture(moreTexture);
    sf::RectangleShape permonth(sf::Vector2f(250,230));
    permonth.setPosition(575 ,355);
    sf::RectangleShape peryear(sf::Vector2f(250,230));
    peryear.setPosition(890 ,355);
    sf::RectangleShape backmore(sf::Vector2f(160,100));
    backmore.setPosition(1200 ,600);
    sf::Text backmoretext("Back", font, 100);
    backmoretext.setPosition(sf::Vector2f(backmore.getPosition().x, backmore.getPosition().y-20));


    //for subscribe
    bool issubscibe = false;
    sf::Texture subscribeTexture;
    sf::Sprite subscribeImage;
    if(!subscribeTexture.loadFromFile("picture\\subscribe.png"))
        std::cout << "load subscribeImage fail !" << std::endl;
    subscribeImage.setTexture(subscribeTexture);
    sf::RectangleShape backsubscribe(sf::Vector2f(160,100));
    backsubscribe.setPosition(1200 ,600);
    sf::Text backsubscribetext("Back", font, 100);
    backsubscribetext.setPosition(sf::Vector2f(backsubscribe.getPosition().x, backsubscribe.getPosition().y-20));

    //for answer of the game
    bool isanswer = false;
    sf::Texture answerTexture;
    sf::Sprite answerImage;
    if(!answerTexture.loadFromFile("picture\\answer.png"))
        std::cout << "load answerImage fail !" << std::endl;
    answerImage.setTexture(answerTexture);
//    answerImage.setPosition(430,100);

    //for checking code and data
    sf::RectangleShape check(sf::Vector2f(300,400));
    check.setPosition(1000, 0);
    bool ischeck = false;
    std::string checkWord[7];
    checkWord[0] = "codeFromLu 0/1\n";//11
    checkWord[1] = "codeFromRrro 0/1\n";//28
    checkWord[2] = "data1 0/1\n";//38
    checkWord[3] = "data2 0/1\n";//48
    checkWord[4] = "data3 0/1\n";//58
    checkWord[5] = "data4 0/1\n";//68
    checkWord[6] = "dataFromLiu 0/1\n";//84
    std::string checkSentence;
    for(int i = 0; i < 7; i++)
        checkSentence += checkWord[i];

    sf::Text checkText(" ", font, 30);
    checkText.setString(checkSentence);
    checkText.setFillColor(sf::Color::Blue);
    check.setFillColor(sf::Color(255,255,205));
    check.setOutlineColor(sf::Color::Blue);
    check.setOutlineThickness(3.0f);

    //for chest
    Chest chest;
    for(int i = 0; i < 4; i++)
        chest.rect[i].setSize(sf::Vector2f(50, 50));
    chest.rect[0].setPosition(643, 33);
    chest.rect[1].setPosition(230, 33);
    chest.rect[2].setPosition(245, 1140);
    chest.rect[3].setPosition(1280, 113);
    chest.dialog[0][0] = "you get a data1";//data1
    chest.maxDialog[0] = 1;
    chest.dialog[1][0] = "you get a data2";//data2
    chest.maxDialog[1] = 1;
    chest.dialog[2][0] = "you get a data3";//data3
    chest.maxDialog[2] = 1;
    chest.dialog[3][0] = "you get a data4";//data4
    chest.maxDialog[3] = 1;
    chest.dialog[4][0] = "empty";
    chest.maxDialog[4] = 1;

    //for stone
    Stone stone;
    stone.rect.setSize(sf::Vector2f(50, 50));
    stone.rect.setPosition(1600, 1420);
    stone.dialog[0][0] = "[System]\nWhy you hit a stone? Data is not here.";
    stone.maxDialog[0] = 1;
    bool talkStone = false;

    //for wall
    std::vector<sf::RectangleShape>::const_iterator iterw;
    std::vector<sf::RectangleShape> wallarray;
    makeWall(&wallarray);

    //for secret
    std::vector<sf::RectangleShape>::const_iterator iters;
    std::vector<sf::RectangleShape> secretarray;
    makeSecret(&secretarray);

    //for field
    std::vector<sf::RectangleShape>::const_iterator iterf;
    std::vector<sf::RectangleShape> fieldarray;
    makeField(&fieldarray);

    int runCount = 0;
    sf::RectangleShape countRun1;
    countRun1.setPosition(1890,120);
    countRun1.setSize(sf::Vector2f(50, 50));
    sf::RectangleShape countRun2;
    countRun2.setPosition(2750,140);
    countRun2.setSize(sf::Vector2f(30, 30));
    sf::RectangleShape countRun3;
    countRun3.setPosition(2750,530);
    countRun3.setSize(sf::Vector2f(30, 30));
    sf::RectangleShape countRun4;
    countRun4.setPosition(1890,530);
    countRun4.setSize(sf::Vector2f(30, 30));
    bool cR1 = false, cR2 = false, cR3 = false;

    sf::Text runtext("1", font, 200);
    runtext.setFillColor(sf::Color::Blue);

    //for loading player and npc
    sf::String filename = "picture\\HANS.png";
    Player p1(filename);

    filename = "picture\\WEI.png";
    Wei wei(filename);
    wei.setPosition(95, 15);
    wei.dialog[0][0] = "[ZhiPing Wei]\nHello, who are you? Oh, seems like you had forgot your name! Poor you. \n";
    wei.dialog[0][1] = "[...]\nHmmmm...yes?\n";
    wei.dialog[0][2] = "[ZhiPing Wei]\nNow you are  Hanspartasebastianchristopher.\nAlrighty then, Hans. I need your help. Please help me finish the project of YouBike analytics.\nThe job's simple, all you need to do is to collect 5 pieces of data and 2 pieces of code\n";
    wei.dialog[0][3] = "[ZhiPing Wei]\nIt's time to go!\n";
    wei.maxDialog[0] = 4;
    wei.dialog[1][0] = "[Zhiping Wei]\nWell, Hans, and just to tell you, if you don't want to get an F, then get set and find data and code!\n";
    wei.maxDialog[1] = 1;
    wei.dialog[2][0] = "[Zhiping Wei]\nWell done kid, I now crown you the kang-ba-zi of NTU IM.\n Looking forward to cooperating with you for the next project.\n";
    wei.maxDialog[2] = 1;

    filename = "picture\\HU.png";
    Hu hu(filename);
    hu.setPosition(1790, 320);
    hu.dialog[0][0] = "[Linhuan Hu]\nHans, did you take physical fitness exam?\n";
    hu.dialog[0][1] = "[System]\nPlease use arrow keys to help Hans run 1600m.(clockwise)\nAfter finish running, talk to me again\n";
    hu.maxDialog[0] = 2;
    hu.dialog[1][0] = "[Linhuan Hu]\nyou haven't finish it yet!!\n";
    hu.maxDialog[1] = 1;
    hu.dialog[2][0] = "[Linhuan Hu]\nYou don't need to come next semester.\n";
    hu.maxDialog[2] = 1;

    filename = "picture\\KONG.png";
    Kong kong(filename);
    kong.setPosition(141, 1137);
    kong.dialog[0][0] = "[rrro]\nHi,Hanspartabaschristopher~\nI here have a question awaitng you, and I also notice that you are looking for a code, eh?\n";
    kong.dialog[0][1] = "[rrro]\nIf I type \"cout << 0;\" and I run it, what will you see on the screen?\nPlease remember to press space after entering your answer\n";
    kong.maxDialog[0] = 2;
    kong.dialog[1][0] = "[rrro]\nSorry, you are totally absolutely wrong.Please try again\n";
    kong.maxDialog[1] = 1;
    kong.dialog[2][0] = "[rrro]\nCongratulations!!! You are correct.\n I can now trust you and hand you the code, take care and be safe!!!\n";
    kong.dialog[2][1] = "[rrro]\nIt's time to head forward~ Good luck!\n";
    kong.maxDialog[2] = 2;
    kong.dialog[3][0] = "[rrro]\nProgramming isn't hard, is it?\n";
    kong.maxDialog[3] = 1;

    filename = "picture\\LONG XI.png";
    Longxi longxi(filename);
    longxi.setPosition(1217, 96);
    longxi.dialog[0][0] = "[Atsuko Takinishi]\nHi, you did a terribly awesome job in your final exam.\nHowever, there is one last thing till you can pass. Consider your asset is $10,000 and liability is $1,000 \nlet me ask, how much equity do you have?\nPlease remember to press space after entering your answer\n";
    longxi.maxDialog[0] = 1;
    longxi.dialog[2][0] = "[Atsuko Takinishi]\nTerrific job!\nBy the way Hans, did you forget your computer in my classroom?\n";
    longxi.dialog[2][1] = "[Atsuko Takinishi]\nYou get a computer!!!(You can now use it to finish Lu's homework!)\n";
    longxi.maxDialog[2] = 2;
    longxi.dialog[1][0] = "[Atsuko Takinishi]\nOh no, it's not correct. Sayonara Hans, you gotta come again next year.\n";
    longxi.maxDialog[1] = 1;
    longxi.dialog[3][0] = "[Atsuko Takinishi]\nI think you not only can understand my English but can also understand accounting, well done!\n";
    longxi.maxDialog[3] = 1;

    filename = "picture\\ZHANG.png";
    Zhang zhang(filename);
    zhang.setPosition(2254, 812);
    zhang.dialog[0][0] = "[Ruien Zhang]\nHi people,it's time for class ~\n";
    zhang.dialog[0][1] = "[system]\nWhich one is not Ruien Zhang?\nUse your mouse click on the one you choose, then press space\n";
    zhang.maxDialog[0] = 2;
    zhang.dialog[1][0] = "[Ruien Zhang]\nIf you choose to give up, your winter vocation will be right at the corner~\n";
    zhang.maxDialog[1] = 1;
    zhang.dialog[2][0] = "[Ruien Zhang]\nCongratulations! You are correct.\nYou earned yourself a hat!!\n";
    zhang.maxDialog[2] = 1;
    zhang.dialog[3][0] = "[Ruien Zhang]\nHow's everything going these days young lad?\n";
    zhang.maxDialog[3] = 1;

    filename = "picture\\ZHANG2.png";
    Zhang zhang2(filename);
    zhang2.setPosition(2321, 812);
    filename = "picture\\fake ZHANG.png";
    Zhang fzhang(filename);
    fzhang.setPosition(2374, 812);

    filename = "picture\\LIU.png";
    Liu liu(filename);
    liu.setPosition(2200, 910);
    liu.dialog[0][0] = "[Qiongru Liu]\n(Monday)Let's have a quiz.\n";
    liu.dialog[0][1] = "[Qiongru Liu]\nDifferentiate the following question: y = 2x\nPlease remember to press space after entering your answer\n";
    liu.maxDialog[0] = 2;
    liu.dialog[2][0] = "[Qiongru Liu]\nCongratulations!!! You are correct.\nGet a piece of data!!!\n";
    liu.maxDialog[2] = 1;
    liu.dialog[1][0] = "[Qiongru Liu]\n Where did I write incorrect? Oh no, you are wrong. \nPlease try it again~\n";
    liu.maxDialog[1] = 1;
    liu.dialog[3][0] = "[Qiongru Liu]\nSee? Calculus is just a piece of cake.";
    liu.maxDialog[3] = 1;

    filename = "picture\\LU.png";
    Lu lu(filename);
    lu.setPosition(460, 711);
    lu.dialog[0][0] = "[Lulu]\nGood afternoon!\n";
    lu.dialog[0][1] = "[Lulu]\nHans, have you made up your homework?\n";
    lu.dialog[0][2] = "[System]\n(Lulu's smile)\n";
    lu.dialog[0][3] = "[System]\nHans goes back to his room and does homework\nPause 10 seconds\n";
    lu.maxDialog[0] = 4;
    lu.dialog[1][0] = "[Lulu]\nGood afternoon!\n";
    lu.dialog[1][1] = "[Lulu]\nHans, you didn't hand in you homework, did you?\n";
    lu.dialog[1][2] = "[Lulu]\nI uploaded a piece of code on Ceiba.\n";
    lu.dialog[1][3] = "[Lulu]\nCongratulations!!! \nYou won yourself a peice of code, you deserve it!\n";
    lu.maxDialog[1] = 4;
    lu.dialog[2][0] = "[Lulu]\nGood afternoon!\n";
    lu.dialog[2][1] = "[Lulu]\nHans, you sure you're done with your homework?\n";
    lu.dialog[2][2] = "[System]\n(Lulu's smile)\n";
    lu.dialog[2][3] = "[System]\nHans uses his computer to finish homework.\n";
    lu.maxDialog[2] = 4;
    lu.dialog[3][0] = "[Lulu]\nSeems like you have worked hard on linear algebra, remember to do your homework next time.";
    lu.maxDialog[3] = 1;

    //for background
    sf::Texture btexture;
    sf::Sprite bimage;
    if(!btexture.loadFromFile("picture\\map.png"))
        std::cout << "load bimage fail !" << std::endl;
    bimage.setTexture(btexture);

    //for music
    sf::Music bmusic;
    if(!bmusic.openFromFile("sound and music\\bmusic.wav"))
        std::cout << "bmusic fail" << std::endl;
    bmusic.setLoop(true);
    bmusic.play();
    bmusic.setVolume(90);

    sf::Music endmusic;
    if(!endmusic.openFromFile("sound and music\\endmusic.wav"))
        std::cout << "endmusic fail" << std::endl;
    endmusic.setLoop(true);

    sf::Music runmusic;
    if(!runmusic.openFromFile("sound and music\\runmusic.wav"))
        std::cout << "runmusic fail" << std::endl;
    runmusic.setLoop(true);

    //for sound
    sf::SoundBuffer chestf;
    if(!chestf.loadFromFile("sound and music\\chestsound.wav"))
        std::cout << "chestsound fail !" << std::endl;
    sf::Sound chestSound;
    chestSound.setBuffer(chestf);

    sf::SoundBuffer lutransportf;
    if(!lutransportf.loadFromFile("sound and music\\Lutransport.wav"))
        std::cout << "Lutransport fail !" << std::endl;
    sf::Sound lutransport;
    lutransport.setBuffer(lutransportf);

    sf::SoundBuffer transportf;
    if(!transportf.loadFromFile("sound and music\\transport.wav"))
        std::cout << "transport fail !" << std::endl;
    sf::Sound transport;
    transport.setBuffer(transportf);

    sf::View view;
    view.setSize(screen.x, screen.y);

    //for cursor
    sf::Cursor cursorHand;
    if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
        std::cout << "cursorHand error!" << std::endl;
    sf::Cursor cursorArrow;
    if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
        std::cout << "cursorArrow error!" << std::endl;
    bool hand = false;

    //for enter text
    sf::String sentence;
    sf::Text enterText(sentence, font, 90);
    enterText.setColor(sf::Color::White);
    sf::RectangleShape enterBox(sf::Vector2f(screen.x - 500, 150));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::KeyReleased):
                if(event.key.code == sf::Keyboard::Up)
                {
                    p1.source.x=0;
                    p1.setUpDateFrame(false);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    p1.source.x=0;
                    p1.setUpDateFrame(false);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    p1.source.x=0;
                    p1.setUpDateFrame(false);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    p1.source.x=0;
                    p1.setUpDateFrame(false);
                }
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::P)
                {
                    if(bmusic.getStatus() == sf::Sound::Playing)
                        bmusic.pause();
                    else
                        bmusic.play();
                }
                else if (event.key.code == sf::Keyboard::H)
                {
                    if(iscontrol)
                    {
                        iscontrol = false;
                        p1.notTalking();
                    }
                    else
                    {
                        p1.talking();
                        iscontrol = true;
                    }
                }
                else if(event.key.code == sf::Keyboard::L)
                {
                    if(ischeck)
                    {
                        ischeck = false;
                    }
                    else
                    {
                        if(p1.codeFromLu)
                        {
                            checkSentence.replace(11,1,"1");
                        }
                        if(p1.codeFromKong)
                        {
                            checkSentence.replace(28,1,"1");
                        }
                        if(p1.data1)
                        {
                            checkSentence.replace(38,1,"1");
                        }
                        if(p1.data2)
                        {
                            checkSentence.replace(48,1,"1");
                        }
                        if(p1.data3)
                        {
                            checkSentence.replace(58,1,"1");
                        }
                        if(p1.data4)
                        {
                            checkSentence.replace(68,1,"1");
                        }
                        if(p1.dataFromLiu)
                        {
                            checkSentence.replace(84,1,"1");
                        }
                        checkText.setString(checkSentence);
                        ischeck = true;
                    }
                }
//                else if(event.key.code == sf::Keyboard::Y)
//                {
//                    p1.codeFromLu = true;
//                    p1.codeFromKong = true;
//                    p1.data1 = true;
//                    p1.data2 = true;
//                    p1.data3 = true;
//                    p1.data4 = true;
//                    p1.dataFromLiu = true;
//                }
                else if(event.key.code == sf::Keyboard::Space)
                {
                    diaBox.setPosition(p1.sprite.getPosition().x - screen.x / 3, p1.sprite.getPosition().y + screen.y / 2 - 150);
                    text.setPosition(diaBox.getPosition().x + 3, diaBox.getPosition().y );
                    text.setFillColor(sf::Color::Blue);
                    diaBox.setFillColor(color);
                    diaBox.setOutlineColor(sf::Color::Blue);
                    diaBox.setOutlineThickness(3.0f);
                    if(p1.canTalk(&wei))//ok
                    {
                        isTalking = true;
                        p1.talking();
                        if(wei.first)
                        {
                            wei.talk(&p1, &text, &diaBox, 0, &endmusic, &bmusic);
                        }
                        else if(!p1.codeFromKong || !p1.codeFromLu || !p1.data1 || !p1.data2 || !p1.data3
                                 || !p1.data4 || !p1.dataFromLiu)
                        {
                            wei.talk(&p1, &text, &diaBox, 1, &endmusic, &bmusic);
                        }
                        else if(p1.codeFromKong && p1.codeFromLu && p1.data1 && p1.data2 && p1.data3
                                 && p1.data4 && p1.dataFromLiu)
                        {
                            wei.talk(&p1, &text, &diaBox, 2, &endmusic, &bmusic);
                        }

                    }
                    else if(p1.canTalk(&hu))//OK
                    {
                        isTalking = true;
                        p1.talking();
                        if(hu.runningGround && !hu.runningCompelet)
                        {
                            hu.talk(&p1, &text, &diaBox, 1, &runmusic, &bmusic);
                        }
                        else if(hu.runningGround && hu.runningCompelet)
                        {
                            hu.talk(&p1, &text, &diaBox, 2, &runmusic, &bmusic);
                        }
                        else
                        {
                            hu.talk(&p1, &text, &diaBox, 0, &runmusic, &bmusic);
                        }
                    }
                    else if(p1.canTalk(&kong))//ok
                    {
                        isTalking = true;
                        p1.talking();
                        if(!kong.first)
                        {
                            kong.talk(&p1, &text, &diaBox, 0, isTexing);
                        }
                        else if(kong.guessing)
                        {
                            sentence.clear();
                            if(kong.guessRight)
                                {
                                    kong.talk(&p1, &text, &diaBox, 2, isTexing);
                                }
                            else if(kong.guessWrong)
                                {
                                    kong.talk(&p1, &text, &diaBox, 1, isTexing);
                                }
                        }
                        else
                        {
                            kong.talk(&p1, &text, &diaBox, 3, isTexing);
                        }
                    }
                    else if(p1.canTalk(&longxi))//ok
                    {
                        isTalking = true;
                        p1.talking();
                        if(!longxi.first)
                        {
                            longxi.talk(&p1, &text, &diaBox, 0, isTexing);
                        }
                        else if(longxi.guessing)
                        {
                            sentence.clear();
                            if(longxi.guessRight)
                                {
                                    longxi.talk(&p1, &text, &diaBox, 2, isTexing);
                                }
                            else if(longxi.guessWrong)
                                {
                                    longxi.talk(&p1, &text, &diaBox, 1, isTexing);
                                }
                        }
                        else
                        {
                            longxi.talk(&p1, &text, &diaBox, 3, isTexing);
                        }
                    }
                    else if(p1.canTalk(&zhang))//OK
                    {
                        isTalking = true;
                        p1.talking();
                        if(!zhang.guessRight && !zhang.guessWrong)
                        {
                            zhang.talk(&p1, &text, &diaBox, 0);
                        }
                        else if(zhang.guessing && zhang.guessRight)
                        {
                            zhang.talk(&p1, &text, &diaBox, 2);
                        }
                        else if(zhang.guessing && zhang.guessWrong)
                        {
                            zhang.talk(&p1, &text, &diaBox, 1);
                        }
                        else if(!zhang.guessing && (zhang.guessRight || zhang.guessWrong))
                        {
                            zhang.talk(&p1, &text, &diaBox, 3);
                        }
                    }
                    else if(p1.canTalk(&liu))//ok
                    {
                        isTalking = true;
                        p1.talking();
                        if(!liu.first)
                        {
                            liu.talk(&p1, &text, &diaBox, 0, isTexing);
                        }
                        else if(liu.guessing)
                        {
                            sentence.clear();
                            if(liu.guessRight)
                                {
                                    liu.talk(&p1, &text, &diaBox, 2, isTexing);
                                }
                            else if(liu.guessWrong)
                                {
                                    liu.talk(&p1, &text, &diaBox, 1, isTexing);
                                }
                        }
                        else
                        {
                            liu.talk(&p1, &text, &diaBox, 3, isTexing);
                        }
                    }
                    else if(p1.canTalk(&lu))//ok
                    {
                        isTalking = true;
                        p1.talking();
                        if(lu.hwCnt < 3)
                        {
                            if(p1.computer)
                            {
                                lu.talk(&p1, &text, &diaBox, 2, &lutransport);
                            }
                            else
                            {
                                lu.talk(&p1, &text, &diaBox, 0, &lutransport);
                            }
                        }
                        else if(p1.codeFromLu)
                        {
                            lu.talk(&p1, &text, &diaBox, 3, &lutransport);
                        }
                        else if(lu.hwCnt >= 3)
                        {
                            lu.talk(&p1, &text, &diaBox, 1, &lutransport);
                        }
                    }
                    else if(p1.isCollide(&chest.rect[0]))
                    {
                        isTalking = true;
                        if(!p1.data1)
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 0, &chestSound);
                        }
                        else
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 4, &chestSound);
                        }
                    }
                    else if(p1.isCollide(&chest.rect[1]))
                    {
                        isTalking = true;
                        if(!p1.data2)
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 1, &chestSound);
                        }
                        else
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 4, &chestSound);
                        }
                    }
                    else if(p1.isCollide(&chest.rect[2]))
                    {
                        isTalking = true;
                        if(!p1.data3)
                        {
                        p1.talking();
                        chest.talk(&p1, &text, &diaBox, 2, &chestSound);
                        }
                        else
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 4, &chestSound);
                        }
                    }
                    else if(p1.isCollide(&chest.rect[3]))
                    {
                        isTalking = true;
                        if(!p1.data4)
                        {
                        p1.talking();
                        chest.talk(&p1, &text, &diaBox, 3, &chestSound);
                        }
                        else
                        {
                            p1.talking();
                            chest.talk(&p1, &text, &diaBox, 4, &chestSound);
                        }
                    }
                    else if (p1.isCollide(&stone.rect))
                    {
//                        p1.talking();
//                        stone.talk(&p1, &text, &diaBox, 0);
//                        talkStone = true;
                        answerImage.setPosition(view.getCenter().x-390, view.getCenter().y-300);
                        isanswer = true;
                    }
                    else
                    {
                        isTalking = false;
                    }
                }
                else if(event.key.code == sf::Keyboard::Enter)
                {
                    if(isTexing)
                    {
                        if(kong.guessing)
                        {
                            if(sentence == "0")
                            {
                                kong.guessRight = true;
                                isTexing = false;
                            }
                            else
                            {
                                kong.guessWrong = true;
                                isTexing = false;
                            }
                        }
                        else if(longxi.guessing)
                        {
                            if(sentence == "9000")
                            {
                                longxi.guessRight = true;
                                isTexing = false;
                            }
                            else
                            {
                                longxi.guessWrong = true;
                                isTexing = false;
                            }
                        }
                        else if(liu.guessing)
                        {
                            if(sentence == "2")
                            {
                                liu.guessRight = true;
                                isTexing = false;
                            }
                            else
                            {
                                liu.guessWrong = true;
                                isTexing = false;
                            }
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(zhang.guessing && 910 < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < 951
                       && 410 < sf::Mouse::getPosition(window).y && sf::Mouse::getPosition(window).y < 470)
                    {
                        zhang.guessWrong = true;
                    }
                    else if(zhang.guessing && 965 < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < 1002
                       && 410 < sf::Mouse::getPosition(window).y && sf::Mouse::getPosition(window).y < 470)
                    {
                        zhang.guessRight = true;
                    }
                    if(begin)
                    {
                        if(isQuit)
                        {
                            if(sf::Mouse::getPosition(window).x > no.getPosition().x &&
                                sf::Mouse::getPosition(window).x < no.getPosition().x + no.getSize().x &&
                                sf::Mouse::getPosition(window).y > no.getPosition().y &&
                                sf::Mouse::getPosition(window).y < no.getPosition().y + no.getSize().y)
                            {
                                isQuit = false;
                            }
                        }
                        else if(ishelp)
                        {
                            if(sf::Mouse::getPosition(window).x > control.getPosition().x &&
                                sf::Mouse::getPosition(window).x < control.getPosition().x + control.getSize().x &&
                                sf::Mouse::getPosition(window).y > control.getPosition().y &&
                                sf::Mouse::getPosition(window).y < control.getPosition().y + control.getSize().y)
                            {
                                iscontrol = true;
                                ishelp = false;
                            }
                        }
                        else if(iscontrol)
                        {
                            if(sf::Mouse::getPosition(window).x > home.getPosition().x &&
                                sf::Mouse::getPosition(window).x < home.getPosition().x + home.getSize().x &&
                                sf::Mouse::getPosition(window).y > home.getPosition().y &&
                                sf::Mouse::getPosition(window).y < home.getPosition().y + home.getSize().y)
                            {
                                iscontrol = false;
                            }
                        }
                        else
                        {
                            if(sf::Mouse::getPosition(window).x > playGame.getPosition().x &&
                                sf::Mouse::getPosition(window).x < playGame.getPosition().x + playGame.getSize().x &&
                               sf::Mouse::getPosition(window).y > playGame.getPosition().y &&
                                sf::Mouse::getPosition(window).y < playGame.getPosition().y + playGame.getSize().y)
                            {
                                transport.play();
                                begin = false;
                            }
                            else if(sf::Mouse::getPosition(window).x > quit.getPosition().x &&
                                    sf::Mouse::getPosition(window).x < quit.getPosition().x + quit.getSize().x &&
                                    sf::Mouse::getPosition(window).y > quit.getPosition().y &&
                                    sf::Mouse::getPosition(window).y < quit.getPosition().y + quit.getSize().y)
                            {
                                isQuit = true;
                            }
                            else if(sf::Mouse::getPosition(window).x > help.getPosition().x &&
                                    sf::Mouse::getPosition(window).x < help.getPosition().x + help.getRadius()*2 &&
                                    sf::Mouse::getPosition(window).y > help.getPosition().y &&
                                    sf::Mouse::getPosition(window).y < help.getPosition().y + help.getRadius()*2)
                            {
                                ishelp = true;
                            }
                        }
                    }
                    else if(wei.fin)
                    {
                        if(isbug)
                        {
                            if(sf::Mouse::getPosition(window).x > backbug.getPosition().x &&
                                sf::Mouse::getPosition(window).x < backbug.getPosition().x + backbug.getSize().x &&
                                sf::Mouse::getPosition(window).y > backbug.getPosition().y &&
                                sf::Mouse::getPosition(window).y < backbug.getPosition().y + backbug.getSize().y)
                            {
                                isbug = false;
                            }
                        }
                        else if(issubscibe)
                        {
                            if(sf::Mouse::getPosition(window).x > backsubscribe.getPosition().x &&
                                sf::Mouse::getPosition(window).x < backsubscribe.getPosition().x + backsubscribe.getSize().x &&
                                sf::Mouse::getPosition(window).y > backsubscribe.getPosition().y &&
                                sf::Mouse::getPosition(window).y < backsubscribe.getPosition().y + backsubscribe.getSize().y)

                            {
                                issubscibe = false;
                            }
                        }
                        else if(ismore)
                        {
                            if((sf::Mouse::getPosition(window).x > permonth.getPosition().x &&
                                sf::Mouse::getPosition(window).x < permonth.getPosition().x + permonth.getSize().x &&
                                sf::Mouse::getPosition(window).y > permonth.getPosition().y &&
                                sf::Mouse::getPosition(window).y < permonth.getPosition().y + permonth.getSize().y) ||
                               (sf::Mouse::getPosition(window).x > peryear.getPosition().x &&
                                sf::Mouse::getPosition(window).x < peryear.getPosition().x + peryear.getSize().x &&
                                sf::Mouse::getPosition(window).y > peryear.getPosition().y &&
                                sf::Mouse::getPosition(window).y < peryear.getPosition().y + peryear.getSize().y))
                            {
                                issubscibe = true;
                            }
                            else if(sf::Mouse::getPosition(window).x > backmore.getPosition().x &&
                                sf::Mouse::getPosition(window).x < backmore.getPosition().x + backmore.getSize().x &&
                                sf::Mouse::getPosition(window).y > backmore.getPosition().y &&
                                sf::Mouse::getPosition(window).y < backmore.getPosition().y + backmore.getSize().y)

                            {
                                ismore = false;
                            }
                        }
                        else
                        {
                            if(sf::Mouse::getPosition(window).x > exit.getPosition().x &&
                            sf::Mouse::getPosition(window).x < exit.getPosition().x + exit.getSize().x &&
                            sf::Mouse::getPosition(window).y > exit.getPosition().y &&
                            sf::Mouse::getPosition(window).y < exit.getPosition().y + exit.getSize().y)
                            {
                                window.close();
                            }
                            else if (sf::Mouse::getPosition(window).x > discoverbug.getPosition().x &&
                                sf::Mouse::getPosition(window).x < discoverbug.getPosition().x + discoverbug.getSize().x &&
                                sf::Mouse::getPosition(window).y > discoverbug.getPosition().y &&
                                sf::Mouse::getPosition(window).y < discoverbug.getPosition().y + discoverbug.getSize().y)
                            {
                                isbug = true;
                            }
                            else if (sf::Mouse::getPosition(window).x > more.getPosition().x &&
                                sf::Mouse::getPosition(window).x < more.getPosition().x + more.getRadius()*2 &&
                                sf::Mouse::getPosition(window).y > more.getPosition().y &&
                                sf::Mouse::getPosition(window).y < more.getPosition().y + more.getRadius()*2)
                            {
                                ismore = true;
                            }
                        }
                    }
                }
                break;
            case sf::Event::TextEntered:
                {
                    if(isTexing)
                    {
                        if(event.text.unicode <= '9' && event.text.unicode >= '0')
                        {
                            sentence += static_cast<char>(event.text.unicode);
                        }
                        else if(event.text.unicode == 8 && sentence.getSize() > 0)
                        {
                            sentence.erase(sentence.getSize() - 1, sentence.getSize());
                        }
                        enterText.setString(sentence);
                        enterBox.setPosition(p1.sprite.getPosition().x - screen.x / 3, p1.sprite.getPosition().y - screen.y / 2 +100 );
                        enterText.setPosition(enterBox.getPosition().x + 3, enterBox.getPosition().y );
                        enterText.setFillColor(sf::Color::Blue);
                        enterBox.setFillColor(color);
                        enterBox.setOutlineColor(sf::Color::Blue);
                        enterBox.setOutlineThickness(3.0f);
                    }
                    break;
                }
            }
        }
        if(p1.cap && !isCap)
        {
            filename = "picture\\HANSCAP.png";
            p1.setTexture(filename);
            isCap = true;
        }
        if(begin)
        {
            if(isQuit)
            {
                if( sf::Mouse::getPosition(window).x > no.getPosition().x &&
                    sf::Mouse::getPosition(window).x < no.getPosition().x + no.getSize().x &&
                    sf::Mouse::getPosition(window).y > no.getPosition().y &&
                    sf::Mouse::getPosition(window).y < no.getPosition().y + no.getSize().y
                    )
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(quitImage);
            }
            else if (ishelp)
            {
                if(sf::Mouse::getPosition(window).x > control.getPosition().x &&
                    sf::Mouse::getPosition(window).x < control.getPosition().x + control.getSize().x &&
                    sf::Mouse::getPosition(window).y > control.getPosition().y &&
                    sf::Mouse::getPosition(window).y < control.getPosition().y + control.getSize().y)
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(helpImage);
            }
            else if(iscontrol)
            {
                if(sf::Mouse::getPosition(window).x > home.getPosition().x &&
                    sf::Mouse::getPosition(window).x < home.getPosition().x + home.getSize().x &&
                    sf::Mouse::getPosition(window).y > home.getPosition().y &&
                    sf::Mouse::getPosition(window).y < home.getPosition().y + home.getSize().y)
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(controlImage);
            }
            else
            {
                if((sf::Mouse::getPosition(window).x > playGame.getPosition().x &&
                    sf::Mouse::getPosition(window).x < playGame.getPosition().x + playGame.getSize().x &&
                    sf::Mouse::getPosition(window).y > playGame.getPosition().y &&
                    sf::Mouse::getPosition(window).y < playGame.getPosition().y + playGame.getSize().y) ||
                    (sf::Mouse::getPosition(window).x > help.getPosition().x &&
                    sf::Mouse::getPosition(window).x < help.getPosition().x + help.getRadius()*2 &&
                    sf::Mouse::getPosition(window).y > help.getPosition().y &&
                    sf::Mouse::getPosition(window).y < help.getPosition().y + help.getRadius()*2) ||
                    (sf::Mouse::getPosition(window).x > quit.getPosition().x &&
                    sf::Mouse::getPosition(window).x < quit.getPosition().x + quit.getSize().x &&
                    sf::Mouse::getPosition(window).y > quit.getPosition().y &&
                    sf::Mouse::getPosition(window).y < quit.getPosition().y + quit.getSize().y))
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(beginImage);
            }
        }
        else if(wei.fin)
        {
            view.reset(sf::FloatRect(0,0,screen.x,screen.y));
            window.setView(view);
            if(isbug)
            {
                if(sf::Mouse::getPosition(window).x > backbug.getPosition().x &&
                    sf::Mouse::getPosition(window).x < backbug.getPosition().x + backbug.getSize().x &&
                    sf::Mouse::getPosition(window).y > backbug.getPosition().y &&
                    sf::Mouse::getPosition(window).y < backbug.getPosition().y + backbug.getSize().y)
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(bugImage);
                window.draw(backbugtext);
            }
            else if(issubscibe)
            {
                if(sf::Mouse::getPosition(window).x > backsubscribe.getPosition().x &&
                    sf::Mouse::getPosition(window).x < backsubscribe.getPosition().x + backsubscribe.getSize().x &&
                    sf::Mouse::getPosition(window).y > backsubscribe.getPosition().y &&
                    sf::Mouse::getPosition(window).y < backsubscribe.getPosition().y + backsubscribe.getSize().y)
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(subscribeImage);
                window.draw(backsubscribetext);
            }
            else if(ismore)
            {
                if((sf::Mouse::getPosition(window).x > permonth.getPosition().x &&
                    sf::Mouse::getPosition(window).x < permonth.getPosition().x + permonth.getSize().x &&
                    sf::Mouse::getPosition(window).y > permonth.getPosition().y &&
                    sf::Mouse::getPosition(window).y < permonth.getPosition().y + permonth.getSize().y) ||
                   (sf::Mouse::getPosition(window).x > peryear.getPosition().x &&
                    sf::Mouse::getPosition(window).x < peryear.getPosition().x + peryear.getSize().x &&
                    sf::Mouse::getPosition(window).y > peryear.getPosition().y &&
                    sf::Mouse::getPosition(window).y < peryear.getPosition().y + peryear.getSize().y) ||
                   (sf::Mouse::getPosition(window).x > backsubscribe.getPosition().x &&
                    sf::Mouse::getPosition(window).x < backsubscribe.getPosition().x + backsubscribe.getSize().x &&
                    sf::Mouse::getPosition(window).y > backsubscribe.getPosition().y &&
                    sf::Mouse::getPosition(window).y < backsubscribe.getPosition().y + backsubscribe.getSize().y))
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(moreImage);
                window.draw(backmoretext);
            }
            else
            {
                if((sf::Mouse::getPosition(window).x > exit.getPosition().x &&
                    sf::Mouse::getPosition(window).x < exit.getPosition().x + exit.getSize().x &&
                    sf::Mouse::getPosition(window).y > exit.getPosition().y &&
                    sf::Mouse::getPosition(window).y < exit.getPosition().y + exit.getSize().y) ||
                   (sf::Mouse::getPosition(window).x > discoverbug.getPosition().x &&
                    sf::Mouse::getPosition(window).x < discoverbug.getPosition().x + discoverbug.getSize().x &&
                    sf::Mouse::getPosition(window).y > discoverbug.getPosition().y &&
                    sf::Mouse::getPosition(window).y < discoverbug.getPosition().y + discoverbug.getSize().y) ||
                   (sf::Mouse::getPosition(window).x > more.getPosition().x &&
                    sf::Mouse::getPosition(window).x < more.getPosition().x + more.getRadius()*2&&
                    sf::Mouse::getPosition(window).y > more.getPosition().y &&
                    sf::Mouse::getPosition(window).y < more.getPosition().y + more.getRadius()*2))
                {
                    if(!hand)
                    {
                        window.setMouseCursor(cursorHand);
                        hand = true;
                    }
                }
                else if(hand)
                {
                    window.setMouseCursor(cursorArrow);
                    hand = false;
                }
                window.draw(endImage);
            }
        }
        else if(isanswer)
        {
            window.draw(answerImage);
        }
        else
        {
            p1.moveMent(&bimage);
            p1.frame();
            view.setCenter(p1.sprite.getPosition());
            window.setView(view);
//            std::cout << p1.sprite.getPosition().x << " " << p1.sprite.getPosition().y << std::endl;
//            std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
            window.draw(bimage);
            if(zhang.guessing &&
               ( (910 < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < 951 &&
                410 < sf::Mouse::getPosition(window).y && sf::Mouse::getPosition(window).y < 470) ||
                (965 < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < 1002 &&
                410 < sf::Mouse::getPosition(window).y && sf::Mouse::getPosition(window).y < 470)))
            {
                if(!hand)
                {
                    window.setMouseCursor(cursorHand);
                    hand = true;
                }
            }
            else if(hand)
            {
                window.setMouseCursor(cursorArrow);
                hand = false;
            }
            if(p1.isCollide(&wei) || p1.isCollide(&kong) || p1.isCollide(&longxi)
                || p1.isCollide(&hu) || p1.isCollide(&zhang) || p1.isCollide(&liu) || p1.isCollide(&lu))
            {
                p1.cantMove();
            }
            if(zhang.guessing)
            {
                window.draw(zhang2.sprite);
                window.draw(fzhang.sprite);
            }
            if(hu.runningGround)
            {
                count = 0;
                for(iterf = fieldarray.begin(); iterf != fieldarray.end(); iterf++)
                {
                    if(p1.isCollide(&fieldarray[count]))
                        p1.cantMove();
                    count++;
                }
                if(p1.isCollide(&countRun1) && !cR1)
                {
                    cR1 = true;
                }
                else if (p1.isCollide(&countRun2) && cR1 && !cR2)
                {
                    cR2 = true;
                }
                else if (p1.isCollide(&countRun3) && cR1 && cR2 &&!cR3)
                {
                    cR3 = true;
                }
                else if (p1.isCollide(&countRun4) && cR1 && cR2 && cR3)
                {
                    runCount++;
                    cR1 = false;
                    cR2 = false;
                    cR3 = false;
                }
                if(runCount >= 4)
                    hu.runningCompelet = true;
                runtext.setPosition(view.getCenter().x-750, view.getCenter().y-400);
                runtext.setString(std::to_string(runCount));
                window.draw(runtext);
            }
            count = 0;
            for(iterw = wallarray.begin(); iterw != wallarray.end(); iterw++)
            {
                if(p1.isCollide(&wallarray[count]))
                    p1.cantMove();
                count++;
            }
            count = 0;
            for(iters = secretarray.begin(); iters != secretarray.end(); iters++)
            {
                if(p1.isCollide(&secretarray[count]))
                    p1.cantMove();
                count++;
            }
            if(wei.first)
            {
                if(p1.isCollide(&weiBound1) || p1.isCollide(&weiBound2))
                {
                    p1.cantMove();
                }
            }
            window.draw(hu.sprite);
            window.draw(kong.sprite);
            window.draw(liu.sprite);
            window.draw(longxi.sprite);
            window.draw(lu.sprite);
            window.draw(zhang.sprite);
            window.draw(wei.sprite);
            window.draw(p1.sprite);
            if(ischeck)
            {
                check.setPosition(view.getCenter().x+300, view.getCenter().y-200);
                window.draw(check);
                checkText.setPosition(check.getPosition().x+3, check.getPosition().y+10);
                window.draw(checkText);
            }
            if(iscontrol)
            {
                controlImage.setPosition(view.getCenter().x-820, view.getCenter().y-380);
                window.draw(controlImage);
            }
            if(isTexing)
            {
                window.draw(enterBox);
                window.draw(enterText);
            }
            else if(isTalking)
            {
                window.draw(diaBox);
                window.draw(text);
            }
//            count = 0;
//            for(iters = secretarray.begin(); iters != secretarray.end(); iters++)
//            {
//                window.draw(secretarray[count]);
//                count++;
//            }
        }
//        std::cout << p1.sprite.getPosition().x << " " << p1.sprite.getPosition().y << std::endl;
        //window.draw(answerImage);
        window.display();
        window.clear();
    }

    return 0;
}

void makeWall(std::vector<sf::RectangleShape> *wallarray)
{
    int count = 0;
    sf::RectangleShape wallInBig;
    wallInBig.setFillColor(sf::Color::White);
    wallInBig.setSize(sf::Vector2f(48, 32));
    //12
    for(count = 0; count < 30; count++)
    {
        wallInBig.setPosition(count*48, 0);
        wallarray->push_back(wallInBig);
    }
    wallInBig.setSize(sf::Vector2f(32, 48));
    for(count = 0; count < 33; count++)
    {
        wallInBig.setPosition(0, count*48);
        wallarray->push_back(wallInBig);
    }
    wallInBig.setSize(sf::Vector2f(48, 48));
    for(count = 0; count < 30; count++)
    {
        wallInBig.setPosition(count*48, 32*48);
        wallarray->push_back(wallInBig);
    }
    wallInBig.setSize(sf::Vector2f(130, 32));
    for(count = 0; count < 50; count++)
    {
        if(count == 27 || count == 26 || count == 25)
            continue;
        wallInBig.setPosition(29*47, count*32);
        wallarray->push_back(wallInBig);
    }
    //13
    wallInBig.setSize(sf::Vector2f(32, 32));
    for(count = 0; count < 23; count++)
    {
        wallInBig.setPosition(2464, 1600-32-count*32);
        wallarray->push_back(wallInBig);
    }
    wallInBig.setSize(sf::Vector2f(48, 32));
    for(count = 3; count < 15; count++)
    {
        wallInBig.setPosition(2464+count*48, 1600-23*32);
        wallarray->push_back(wallInBig);
    }
    //1
    wallInBig.setSize(sf::Vector2f(420, 2));
    wallInBig.setPosition(35, 575);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(2,130));
    wallInBig.setPosition(455, 575);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(2,220));
    wallInBig.setPosition(455, 765);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(420, 2));
    wallInBig.setPosition(35, 985);
    wallarray->push_back(wallInBig);
    //2
    wallInBig.setSize(sf::Vector2f(330, 10));
    wallInBig.setPosition(35, 510);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(10,412));
    wallInBig.setPosition(433, 100);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(220,65));
    wallInBig.setPosition(33, 166);
    wallarray->push_back(wallInBig);
    //3
    wallInBig.setSize(sf::Vector2f(10,320));
    wallInBig.setPosition(560, 33);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(380,10));
    wallInBig.setPosition(570, 420);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(10,333));
    wallInBig.setPosition(960, 97);
    wallarray->push_back(wallInBig);

    wallInBig.setSize(sf::Vector2f(170,60));
    wallInBig.setPosition(570, 250);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(160,60));
    wallInBig.setPosition(800, 250);
    wallarray->push_back(wallInBig);
    //4
    wallInBig.setSize(sf::Vector2f(10,355));
    wallInBig.setPosition(1060, 95);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(155,10));
    wallInBig.setPosition(1070, 440);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(30, 10));
    wallInBig.setPosition(1315, 440);
    wallarray->push_back(wallInBig);
    //5
    wallInBig.setSize(sf::Vector2f(400,10));
    wallInBig.setPosition(885, 1175);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(10,300));
    wallInBig.setPosition(885, 1186);
    wallarray->push_back(wallInBig);
    //6
    wallInBig.setSize(sf::Vector2f(10,450));
    wallInBig.setPosition(450,1080);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(240,10));
    wallInBig.setPosition(530, 1061);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(10, 450));
    wallInBig.setPosition(840, 1080);
    wallarray->push_back(wallInBig);
    //7
    wallInBig.setSize(sf::Vector2f(310,10));
    wallInBig.setPosition(32,1061);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(10,470));
    wallInBig.setPosition(420, 1061);
    wallarray->push_back(wallInBig);
    //14
    wallInBig.setSize(sf::Vector2f(780,100));
    wallInBig.setPosition(1495,612);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(650,100));
    wallInBig.setPosition(2465, 631);
    wallarray->push_back(wallInBig);

    wallInBig.setSize(sf::Vector2f(150,550));
    wallInBig.setPosition(1530,7);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(1140,80));
    wallInBig.setPosition(1731, 0);
    wallarray->push_back(wallInBig);
    wallInBig.setSize(sf::Vector2f(170,550));
    wallInBig.setPosition(2940, 7);
    wallarray->push_back(wallInBig);
}

void makeField(std::vector<sf::RectangleShape> *fieldarray)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(850, 355));
    rect.setPosition(1900, 165);
    fieldarray->push_back(rect);
    rect.setSize(sf::Vector2f(20, 20));
    for(int i = 0; i < 5; i++)
    {
        rect.setPosition(1896-i*20, 202+i*20);
        fieldarray->push_back(rect);
        rect.setPosition(1796+i*20, 403+i*20);
        fieldarray->push_back(rect);
    }
    for(int i = 0; i < 5; i++)
    {
        rect.setPosition(2750+i*20, 172+i*20);
        fieldarray->push_back(rect);
        rect.setPosition(2750+i*20, 480-i*20);
        fieldarray->push_back(rect);
    }
    for(int i = 0; i < 7; i++)
    {
        rect.setPosition(2840, 272+i*20);
        fieldarray->push_back(rect);
    }
    rect.setSize(sf::Vector2f(350, 100));
    rect.setPosition(2200, 612);
    fieldarray->push_back(rect);
}

void makeSecret(std::vector<sf::RectangleShape> *secretarray)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(810, 110));
    rect.setPosition(1520, 1170);
    secretarray->push_back(rect);
    rect.setSize(sf::Vector2f(90, 110));
    rect.setPosition(2380, 1170);
    secretarray->push_back(rect);

    rect.setSize(sf::Vector2f(720, 80));
    rect.setPosition(1520, 1280);
    secretarray->push_back(rect);
    rect.setSize(sf::Vector2f(100, 80));
    rect.setPosition(2380, 1280);
    secretarray->push_back(rect);

    rect.setSize(sf::Vector2f(720, 70));
    rect.setPosition(1520, 1350);
    secretarray->push_back(rect);
    rect.setSize(sf::Vector2f(180, 70));
    rect.setPosition(2280, 1350);
    secretarray->push_back(rect);

    rect.setSize(sf::Vector2f(100, 70));
    rect.setPosition(1650, 1420);
    secretarray->push_back(rect);

    rect.setSize(sf::Vector2f(700, 45));
    rect.setPosition(1540, 1490);
    secretarray->push_back(rect);
    rect.setSize(sf::Vector2f(180, 45));
    rect.setPosition(2280, 1490);
    secretarray->push_back(rect);

}
//1490
