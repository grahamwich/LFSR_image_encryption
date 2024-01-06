#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "LFSR.hpp"

// transforms image using LFSR
void transform(sf::Image&, LFSR*);

// main should take arguments in the format:
// inputfile, outputfile, lfsr seed
// which will go to argv[0], ...[1], ...[2], ...[3]
int main(int argc, char* argv[]) {

    // check argc is the correct size:
    if (argc < 3) {
        std::cout << "Invalid cl args to main";
    }


	LFSR lfsr(argv[3]);

	//load original cat image
	sf::Image image;
	if (!image.loadFromFile(argv[1]))
		return -1;

	//temp image used for transform function
	sf::Image tempIm = image;
	transform(tempIm, &lfsr);
	//   write the file
	if (!tempIm.saveToFile(argv[2]))
		return -1;

	//create the window based on the image size
	sf::Vector2u size1 = image.getSize();
	sf::RenderWindow window1(sf::VideoMode(size1.x, size1.y), "Original");
	sf::Vector2u size2 = tempIm.getSize();
	sf::RenderWindow window2(sf::VideoMode(size2.x, size2.y), "Encrypted");

	//load textures
	sf::Texture texture1;
	texture1.loadFromImage(image);
	sf::Texture texture2;
	texture2.loadFromImage(tempIm);

	//load sprites
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);

	//loop
	while (window1.isOpen() && window2.isOpen()) {
		//check if windows are closed manually
		sf::Event event;
		while (window1.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window1.close();
		}
		while (window2.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			window2.close();
		}

	//draw
	window1.clear();
	window1.draw(sprite1);
	window1.display();

	window2.clear();
	window2.draw(sprite2);
	window2.display();
	}

	return 0;
}



void transform(sf::Image& image, LFSR* lfsr) {
	//p is a pixelimage.getPixel(x, y);
	sf::Color p;

	//get image width and height based in pixels and loop over them
	//pixels.cpp showed how to manipulate the RGB values of a single pixel
	for (unsigned int x = 0; x < image.getSize().x; x++) {
		for (unsigned int y = 0; y < image.getSize().y; y++) {

			p = image.getPixel(x, y);
			p.r = p.r ^ lfsr->generate(8); //XORing twice will return the original value (concept used for unencrypt)
			p.g = p.g ^ lfsr->generate(8); 
			p.b = p.b ^ lfsr->generate(8);
			image.setPixel(x, y, p); //fully change the pixel at location x, y, to pixel p
		}
	}
}