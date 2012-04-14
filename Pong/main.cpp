// Pong ...
// Attempt 1

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main()
{
    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Window");
    // Set FPS
    App.SetFramerateLimit(60);

    // Load Font
    sf::Font MyFont;
    if (!MyFont.LoadFromFile("CONSOLA.TTF"))
    {
        // Error
        return 1;
    }

    // Create Score Strings
    sf::String Score1("0", MyFont, 50);
    Score1.SetColor(sf::Color(255, 255, 255));
    Score1.Move(25, 25);
    sf::String Score2("0", MyFont, 50);
    Score2.SetColor(sf::Color(255, 255, 255));
    Score2.Move(750, 25);

    // Create scores
    int p1score = 0;
    int p2score = 0;

    // Load paddle image  25x125px
    sf::Image i_paddle;
    if (!i_paddle.LoadFromFile("paddle.png"))
    {
        // Error
        return 1;
    }

    // Create sprite for paddle1
    sf::Sprite paddle1;
    paddle1.SetImage(i_paddle);
    paddle1.SetPosition(25.f, 100.f);

    // Create sprite for paddle2
    sf::Sprite paddle2;
    paddle2.SetImage(i_paddle);
    paddle2.SetPosition(750.f, 300.f);

    // Load ball image 25x25px
    sf::Image i_ball;
    if (!i_ball.LoadFromFile("ball.png"))
    {
        // Error
        return 1;
    }

    // Create sprite for ball
    sf::Sprite ball;
    ball.SetImage(i_ball);
    ball.SetPosition(200, 100);

    // Create attributes for ball
    float ball_x = 1;
    float ball_y = 1;


    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close Window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Get elapsed time
        float ElapsedTime = App.GetFrameTime();

        // Move paddle1
        if (App.GetInput().IsKeyDown(sf::Key::Q))
            paddle1.Move(0, -250 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::A))
            paddle1.Move(0, 250 * ElapsedTime);
        // Reset paddle1 if it hits the edge of the screen
        if (paddle1.GetPosition().y < 0)
            paddle1.SetY(0);
        if (paddle1.GetPosition().y > 475)
            paddle1.SetY(475);

        // Move paddle2
        if (App.GetInput().IsKeyDown(sf::Key::Up))
            paddle2.Move(0, -250 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::Down))
            paddle2.Move(0, 250 * ElapsedTime);

        // Reset paddle1 if it hits the edge of the screen
        if (paddle2.GetPosition().y < 0)
            paddle2.SetY(0);
        if (paddle2.GetPosition().y > 475)
            paddle2.SetY(475);




        // Reverse ball direction when it hits celling or floor
        if (ball.GetPosition().y <= 0 || ball.GetPosition().y >= 575)
        {
            ball_y = ball_y * -1;
        }

        // Bounce off paddle1
        if ((ball.GetPosition().y >= paddle1.GetPosition().y) && (ball.GetPosition().y <= (paddle1.GetPosition().y + 125))
            && (ball.GetPosition().x <= (paddle1.GetPosition().x + 20)))
        {
            std::cout << "Paddle1 hit!" << std::endl;
            //ball_y = ball_y * -1;
            ball_x = ball_x * -1;
        }

        // Bounce off paddle2
        if ((ball.GetPosition().y >= paddle2.GetPosition().y) && (ball.GetPosition().y <= (paddle2.GetPosition().y + 125))
            && (ball.GetPosition().x >= (paddle2.GetPosition().x -20)))
        {
            std::cout << "Paddle2 hit!" << std::endl;
            //ball_y = ball_y * -1;
            ball_x = ball_x * -1;
        }

        // Score
        if (ball.GetPosition().x <= 0)
        {
            p2score = p2score + 1;
            std::cout << "p2: " << p2score << std::endl;
            ball.SetPosition(400, 300);
            ball_x = ball_x * -1;
            std::stringstream p2;
            p2 << p2score;
            Score2.SetText(p2.str().c_str());
        }
        if (ball.GetPosition().x >= 775)
        {
            p1score = p1score + 1;
            std::cout << "p1: " << p1score << std::endl;
            ball.SetPosition(400,300);
            ball_x = ball_x * -1;
            std::stringstream p1;
            p1 << p1score;
            Score1.SetText(p1.str().c_str());
        }

        // Move ball
        ball.Move(ball_x * 300 * ElapsedTime, ball_y * 300 * ElapsedTime);



        // Clear the screen (fill it with white)
        App.Clear(sf::Color(0, 0, 0));

        // Draw the sprite
        App.Draw(paddle1);
        App.Draw(paddle2);
        App.Draw(ball);
        App.Draw(Score1);
        App.Draw(Score2);

        // Display window contents on screen
        App.Display();

    }

    return EXIT_SUCCESS;
}
