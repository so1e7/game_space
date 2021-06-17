#include "conf.h"
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

//Основная функция приложения, в которой описана сама игра и взаимодействие между игроком и камнями
int main()
{
    srand(time(0)); 
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space");

    //Объявляем текстуру и спрайт для игрового фона
    Texture fon;
    fon.loadFromFile(BACKGROUND_PATH); //Загружаем фон игры в текстуру
    Sprite background(fon);

    //Объявляем текстуру и спрайт для фона меню
    Texture t1;	
	t1.loadFromFile(MENU_PATH); //Загружаем фон игрового меню в текстуру
	Sprite menu_background(t1);

    //Объявляем текстуру и спрайт для игрока
    Texture p;
    p.loadFromFile(PLAYER_PATH); //Загружаем картинку игрока(космического кораблся) в текстуру
    Sprite player(p);
    player.setTextureRect(IntRect(0, 0, 120, 90));
    player.setPosition(500, 600); //Устанавливаем начальную позицию корабля

    //Объявляем текстуру и спрайт для снаряда
    Texture bul;
    bul.loadFromFile(BULLET_PATH);//Загружаем картинку снаряда в текстуру
    Sprite bullet(bul);
    bullet.setPosition(-100, -100); //Устанавливаем начальную позицию снаряда
    bool s_bul = false; //коэффициент, который отвечает, когда будет появляться снаряд
    bullet.setScale(0.8f, 0.8f);

    //Объявляем текстуру и спрайт для кнопки, при помощи которой мы сможем начать игру
    Texture sp;
    sp.loadFromFile(PROBEL_PATH); 
    Sprite probel(sp);
    probel.setPosition(200, 300); //Устанавливаем расположение надписи "Нажмите на пробел"

    //Объявляем текстуру и спрайт для камней
    Texture en;
    en.loadFromFile(ENEMY_PATH);//Загружаем картинку камня в текстуру
    Sprite enemy[6];
    int en_y[6] = {0}, e_x, e_y;
    for (int i = 0; i < 6; i++)
    {
        enemy[i].setScale(0.9f, 0.9f);
        enemy[i].setTexture(en);
        en_y[i] = rand() % 5;

        e_x = 220 * i;
        e_y = -150 - 100 * en_y[i];
        enemy[i].setPosition(e_x, e_y);
    }

    //Объявляем текстуру и спрайт для надписи "Очки"
    Texture scr;
    scr.loadFromFile(SCORE_PATH);
    Sprite score(scr);
    score.setPosition(10, 5); //Устанавливаем расположение надписи "Очки"
    score.setScale(0.4f, 0.4f);

    //Объявляем текстуру и спрайт для цирф, которые используются для выведения счета
    Texture numb;
    numb.loadFromFile(NUMBER_PATH);
    Sprite number[3];
    int n_k[3] = {0};
    for (int i = 0; i < 3; i++)
    {
        number[i].setScale(0.45f, 0.45f);

        number[i].setTexture(numb);
        number[i].setPosition(130 + 25 * i, 5);
        number[i].setTextureRect(IntRect(0, 0, 50, 79));
    }

    bool play = false;

    //Главный цикл приложения. Выполняется, пока открыто окно.
    while (window.isOpen())
    {
        Vector2f pl = player.getPosition();

        //Обработка очереди событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space)
                {
                    if (!play && !s_bul)
                        play = true;
                    else if (play && !s_bul)
                    {
                        bullet.setPosition(pl.x + 52, pl.y - 50);
                        s_bul = true;
                    }
                }
        }

        //Условие, отвечающее за работу игры
        if (play)
        {
            //Обрабатка нажатия клавиш движения
            if (Keyboard::isKeyPressed(Keyboard::Right))
                if (pl.x < 1080)
                    player.move(0.15f, 0);
            if (Keyboard::isKeyPressed(Keyboard::Left))
                if (pl.x > 0)
                    player.move(-0.15f, 0);
            if (Keyboard::isKeyPressed(Keyboard::Up))
                if (pl.y > 5)
                    player.move(0, -0.15f);
            if (Keyboard::isKeyPressed(Keyboard::Down))
                if (pl.y < 695)
                    player.move(0, 0.15f);

            Vector2f pa = bullet.getPosition();
            if (s_bul)
            {
                bullet.move(0, -0.7f);
                if (pa.y < -100)
                    s_bul = false;
            }

            Vector2f em[6];
            for (int i = 0; i < 6; i++)
            {
                enemy[i].move(0, 0.05);
                em[i] = enemy[i].getPosition();

                //Условие генерации нового камня, если он выходит за границу
                if (em[i].y > 850)
                {
                    en_y[i] = rand() % 5;

                    e_x = 220 * i;
                    e_y = -150 - 100 * en_y[i];
                    enemy[i].setPosition(e_x, e_y);
                }

                //Обрабатка столкновения космического кораблся с камнем
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
                {
                    e_x = 220 * i;
                    e_y = -150 - 100 * en_y[i];
                    enemy[i].setPosition(e_x, e_y);

                    n_k[2]--;
                }
                
                //Обрабатка столкновения снаряда с камнем
                if (bullet.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
                {
                    en_y[i] = rand() % 5;
                    e_x = 220 * i;
                    e_y = -150 - 100 * en_y[i];
                    enemy[i].setPosition(e_x, e_y);

                    bullet.setPosition(-100, -100);

                    n_k[2] += 2;
                }
            }
        }

        // Обрабатка счетчика очков
        if (n_k[2] > 9)
        {
            n_k[2] -= 10;

            n_k[1]++;
            if (n_k[1] > 9)
            {
                n_k[1] -= 10;

                n_k[0]++;
                if (n_k[0] > 9)
                    n_k[0] -= 10;
                number[0].setTextureRect(IntRect(n_k[0] * 50, 0, 50, 79));
            }
            number[1].setTextureRect(IntRect(n_k[1] * 50, 0, 50, 79));
        }
        number[2].setTextureRect(IntRect(n_k[2] * 50, 0, 50, 79));

        window.clear(Color::White);

        window.draw(background); //Отрисовывка игрового фона
        window.draw(player); //Отрисовывка космического корабля

        window.draw(bullet); //Отрисовывка снаряда

        //Цикл, который отвечает за отрисовку камней
        for (int i = 0; i < 6; i++)
            window.draw(enemy[i]);

        if (play) {
            window.draw(score);

            for (int i = 0; i < 3; i++)
                window.draw(number[i]);
        }
        else if (!play){
            window.draw(menu_background);
            window.draw(probel);
        }

        window.display(); //Отрисовка окна
    }

    return 0;
}