#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

constexpr int STONES_NUMBER = 6;

using namespace sf;

/**
 * Обновляет счётчик очков
 * @param n_k позиции цифр
 * @param number спрайты цифр
 */
void update_counter(int *n_k, Sprite *number) {
    if (n_k[2] > 9) {
        n_k[2] -= 10;

        n_k[1]++;
        if (n_k[1] > 9) {
            n_k[1] -= 10;

            n_k[0]++;
            if (n_k[0] > 9)
                n_k[0] -= 10;
            number[0].setTextureRect(IntRect(n_k[0] * 50, 0, 50, 79));
        }
        number[1].setTextureRect(IntRect(n_k[1] * 50, 0, 50, 79));
    }
    number[2].setTextureRect(IntRect(n_k[2] * 50, 0, 50, 79));
}

/**
 * Обрабатывает нажатия клавиатуры
 * @param player спрайт игрока
 * @param pl координаты игрока
 */
void handle_keyboard(Sprite &player, Vector2f &pl) {
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
}

/**
 * Выводит камни на экран и проверяет взаимодействие с игроком и снарядом
 * @param enemy спрайт камня
 * @param player спрайт игрока
 * @param bullet спрайт снаряда
 * @param en_y координата Y камня
 * @param n_k позиции цифр
 */
void draw_stones(std::vector<Sprite> &enemy, Sprite &player, Sprite &bullet, int *en_y, int *n_k) {
    int e_x, e_y;

    Vector2f em[STONES_NUMBER];
    for (int i = 0; i < STONES_NUMBER; i++) {
        enemy[i].move(0, 0.05f);
        em[i] = enemy[i].getPosition();

        if (em[i].y > 850) {
            en_y[i] = rand() % 10;

            e_x = 220 * i;
            e_y = -150 - 100 * en_y[i];
            enemy[i].setPosition(e_x, e_y);
        }

        if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
            e_x = 220 * i;
            e_y = -150 - 100 * en_y[i];
            enemy[i].setPosition(e_x, e_y);

            n_k[2]--;
        }

        if (bullet.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
            en_y[i] = rand() % 5;

            e_x = 220 * i;
            e_y = -150 - 100 * en_y[i];
            enemy[i].setPosition(e_x, e_y);

            bullet.setPosition(-100, -100);

            n_k[2] += 2;
        }
    }
}

//Основная функция приложения, в которой описана сама игра и взаимодействие между игроком и камнями
int main() {
    srand(time(0));
    RenderWindow window(VideoMode(1200, 790), "Space");

    //Объявляем текстуру и спрайт для игрового фона
    Texture fon;
    fon.loadFromFile("res/background.png"); //Переменная, в которой содерижтся изображение фона игры
    Sprite background(fon);

    //Объявляем текстуру и спрайт для фона меню
    Texture t1;
    t1.loadFromFile("res/menu.jpg"); //Переменная, в которой содерижтся изображение фона "игрового меню"
    Sprite menu_background(t1);

    //Объявляем текстуру и спрайт для игрока
    Texture p;
    p.loadFromFile("res/player.png"); //Переменная, в которой содерижтся изображение игрока(космического корабля)
    Sprite player(p);
    player.setTextureRect(IntRect(0, 0, 120, 90));
    player.setPosition(500, 600); //Устанавливаем начальную позицию корабля

    //Объявляем текстуру и спрайт для снаряда
    Texture bul;
    bul.loadFromFile("res/bullet.png"); //Переменная, в которой содерижтся изображение снаряда
    Sprite bullet(bul);
    bullet.setPosition(-100, -100); //Устанавливаем начальную позицию снаряда
    bool s_bul = false; //коэффициент, который отвечает, когда будет появляться снаряд
    bullet.setScale(0.8f, 0.8f);

    //Объявляем текстуру и спрайт для кнопки, при помощи которой мы сможем начать игру
    Texture sp;
    sp.loadFromFile("res/probel.png");
    Sprite probel(sp);
    probel.setPosition(200, 300); //Устанавливаем расположение надписи "Нажмите на пробел"

    //Объявляем текстуру и спрайт для камней
    Texture en;
    en.loadFromFile("res/enemy.png"); //Переменная, в которой содерижтся изображение камня
    std::vector<Sprite> enemy(STONES_NUMBER);
    int en_y[STONES_NUMBER] = {0}, e_x, e_y;
    for (int i = 0; i < STONES_NUMBER; i++) {
        enemy[i].setScale(0.9f, 0.9f);
        enemy[i].setTexture(en);
        en_y[i] = rand() % 5;

        e_x = 220 * i;
        e_y = -150 - 100 * en_y[i];
        enemy[i].setPosition(e_x, e_y);
    }

    //Объявляем текстуру и спрайт для надписи "Очки"
    Texture scr;
    scr.loadFromFile("res/score.png");
    Sprite score(scr);
    score.setPosition(10, 5); //Устанавливаем расположение надписи "Очки"
    score.setScale(0.4f, 0.4f);

    //Объявляем текстуру и спрайт для цирф, которые используются для выведения счета
    Texture numb;
    numb.loadFromFile("res/number.png");
    Sprite number[3];
    int n_k[3] = {0};
    for (int i = 0; i < 3; i++) {
        number[i].setScale(0.45f, 0.45f);

        number[i].setTexture(numb);
        number[i].setPosition(130 + 25 * i, 5);
        number[i].setTextureRect(IntRect(0, 0, 50, 79));
    }

    bool play = false; //Переменная, отвечающая за начало игры

    //Главный цикл приложения. Выполняется, пока открыто окно.
    while (window.isOpen()) {
        Vector2f pl = player.getPosition();

        //Обработка очереди событий в цикле
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                //////Принцип работы стрельбы был взят на сайте kychka-pc.ru
                if (event.key.code == Keyboard::Space) {
                    if (!play && !s_bul)
                        play = true;
                    else if (play && !s_bul) {
                        bullet.setPosition(pl.x + 52, pl.y - 50);
                        s_bul = true;
                    }
                }
                ///Конец взаимствования
        }

        //Условие, отвечающее за работу игры
        if (play) {
            handle_keyboard(player, pl);

            Vector2f pa = bullet.getPosition();
            if (s_bul) {
                bullet.move(0, -0.7f);
                if (pa.y < -100)
                    s_bul = false;
            }

            draw_stones(enemy, player, bullet, en_y, n_k);
        }

        update_counter(n_k, number);

        window.clear(Color::White);

        window.draw(background); //Отрисовывка игрового фона
        window.draw(player); //Отрисовывка космического корабля

        window.draw(bullet); //Отрисовывка снаряда

        //Цикл, который отвечает за отрисовку камней
        for (int i = 0; i < STONES_NUMBER; i++)
            window.draw(enemy[i]);

        if (play) {
            window.draw(score);

            for (int i = 0; i < 3; i++)
                window.draw(number[i]);
        } else if (!play) {
            window.draw(menu_background);
            window.draw(probel);
        }

        window.display(); //Отрисовка окна
    }

    return 0;
}