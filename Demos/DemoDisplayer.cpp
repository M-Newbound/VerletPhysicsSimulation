#include "DemoDisplayer.h"

sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Window");

void DemoDisplayer::loop()
{

    sf::Clock clock;
    double deltaTime = 0.0f;




    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed) {   
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) onClick(mousePosition);

            }
        }


        window.clear();

        deltaTime = clock.restart().asSeconds();
        duringUpdate(deltaTime);


        window.display();
    }
}

void DemoDisplayer::drawParticle(const VerletPhysics::Particle* p)
{
    double r = p->getRadius();
    sf::CircleShape circle(r);

    circle.setPosition(p->getPosition().x() - r, p->getPosition().y() - r);

    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.0f);

    window.draw(circle);
}

void DemoDisplayer::drawPairedParticleConstraint(const VerletPhysics::PairedParticleConstraint* c)
{
    if (!((VerletPhysics::Constraint*)c)->isEnabled()) return;
    
    sf::Vector2f point1(c->getParticleA()->getPosition().x(), c->getParticleA()->getPosition().y());
    sf::Vector2f point2(c->getParticleB()->getPosition().x(), c->getParticleB()->getPosition().y());
    
    // Create a vertex array for the line
    sf::VertexArray line(sf::Lines, 2);

    // Set the position and color of each vertex
    line[0].position = point1;
    line[0].color = sf::Color::White;
    line[1].position = point2;
    line[1].color = sf::Color::White;

    window.draw(line);
}
