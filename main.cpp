#include "conf.h" 
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{ 
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
    Texture sn;
    sn.loadFromFile(BULLET_PATH);
    Sprite bullet(sn);
    bullet.setPosition(-100, -100);
    bool s_bul = false; //коэффициент, который отвечает за отрисовку снаряда

    //Чтобы начать игру, нужно прожать "пробел"
    Texture st;
    st.loadFromFile(PROBEL_PATH);
    Sprite probel(st);
    probel.setPosition(200, 300);

    bool play = false;

    //основной цикл
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
                    bullet.move(0, -0.1);
                    if(pa.y < -100)
                        s_bul = false;
                }
        }

        window.clear(Color::White);

        window.draw(background);
        window.draw(player);

        window.draw(bullet);

        if (!play)
            window.draw(probel);

        window.display();
    }

    return 0;
}