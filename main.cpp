#include "conf.h" 
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{ 
    srand(time(0)); //Генерация случайного числа
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space");

    Texture fon;
    fon.loadFromFile(BACKGROUND_PATH);
    Sprite background(fon);
    
    //Игрок
    Texture p;
    p.loadFromFile(PLAYER_PATH);
    Sprite player(p);
    player.setTextureRect(IntRect(0, 0, 120, 90));
    player.setPosition(500, 600);
    
    //Снаряд
    Texture bul;
    bul.loadFromFile(BULLET_PATH);
    Sprite bullet(bul);
    bullet.setPosition(-100, -100);
    bool s_bul = false; //коэффициент, который отвечает за отрисовку снаряда
    bullet.setScale(0.8f, 0.8f);

    //Чтобы начать игру, нужно прожать "пробел"
    Texture sp;
    sp.loadFromFile(PROBEL_PATH);
    Sprite probel(sp);
    probel.setPosition(200, 300);

    Texture en;
    en.loadFromFile(ENEMY_PATH);
    Sprite enemy[5];
    int en_y[5] = {0};
    for (int i = 0; i < 5; i++) {
        enemy[i].setScale(0.9f, 0.9f);
        enemy[i].setTexture(en);
        en_y[i] = rand() % 5;
        enemy[i].setPosition(230 * i, -150 - 100 * en_y[i]);
    }

    Texture lf;
    lf.loadFromFile(LIFE_PATH);
    Sprite life(lf);
    life.setPosition(950, 5);
    life.setScale(0.4f, 0.4f);

    bool play = false;

    //Главный цикл приложения. Выполняется, пока открыто окно.
    while (window.isOpen())
    {
        Vector2f pl = player.getPosition();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space) {
                    if (!play && !s_bul)
                        play = true;
                    else if (play && !s_bul) {
                        bullet.setPosition(pl.x + 52, pl.y - 50);
                        s_bul = true;
                    }
                }
        }
        
        if (play) {
            if (Keyboard::isKeyPressed(Keyboard::Right))
                if (pl.x < 1080)
                    player.move(0.10, 0);
            if (Keyboard::isKeyPressed(Keyboard::Left))
                if (pl.x > 0)
                    player.move(-0.10, 0);
            if (Keyboard::isKeyPressed(Keyboard::Up))
                if (pl.y > 5)
                    player.move(0, -0.10);
            if (Keyboard::isKeyPressed(Keyboard::Down))
                if (pl.y < 695)
                    player.move(0, 0.10);
            
            Vector2f pa = bullet.getPosition();
                if (s_bul) {
                    bullet.move(0, -0.5);
                    if(pa.y < -100)
                        s_bul = false;
                }
            
            Vector2f em[5];
            for (int i = 0; i < 5; i++) {
                enemy[i].move(0, 0.05);
                em[i] = enemy[i].getPosition();

                if (em[i].y > 850) {
                    en_y[i] = rand() % 5;
                    enemy[i].setPosition(175 * i, -150 - 100 * en_y[i]);
                }

                if (bullet.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
                    en_y[i] = rand() % 5;
                    enemy[i].setPosition(175 * i, -150 - 100 * en_y[i]);

                    bullet.setPosition(-100, -100);
                }
            }
        }

        window.clear(Color::White);

        window.draw(background);
        window.draw(player);

        window.draw(bullet);

        for (int i = 0; i < 5; i++)
            window.draw(enemy[i]);

        if (play) {
            window.draw(life);
        } else if (!play)
            window.draw(probel);

        window.display();
    }

    return 0;
}