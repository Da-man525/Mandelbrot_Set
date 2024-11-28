#include "ComplexPlane.h"
using namespace sf;

int main()
{
	int scrteenwidth = VideoMode::getDesktopMode().width;
	int scrteenhight = VideoMode::getDesktopMode().height;
	VideoMode vm(scrteenwidth, scrteenhight);

	RenderWindow window(vm, "MandelBrot Set", Style::Default);

	ComplexPlane game = ComplexPlane(scrteenwidth, scrteenhight);
	Font font;
	Text text;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Right) 
				{
					game.zoomOut();
					game.setCenter(Mouse::getPosition());
				}
				else if (event.mouseButton.button == Mouse::Left)
				{
					game.zoomIn();
					game.setCenter(Mouse::getPosition());
				}
			}
		}
		if (event.type == Event::MouseMoved)
		{
			game.setMouseLocation(Mouse::getPosition());
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		game.updateRender();
		game.loadText(text);
		window.clear();
		game.draw(window, RenderStates::Default);
		window.draw(text);
		window.display();
	}
}
