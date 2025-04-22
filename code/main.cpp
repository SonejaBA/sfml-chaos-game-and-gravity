#include "Particle.h"
#include <cstdlib>
#include <ctime>

Vector2f calculateDistance(Vector2f p1, Vector2f p2) {
	Vector2f coords;
	coords.x = (p1.x + p2.x) / 2;
	coords.y = (p1.y + p2.y) / 2;
	return coords;
}

int main() {
	srand(time(0));

	const int AMOUNT_OF_PARTICLES = 10000;

	RenderWindow window(VideoMode(1280, 720), "Chaos Game");
	window.setFramerateLimit(60);

	vector<Particle> particles;
	vector<Source> gravitySource;
	bool blackHoleReady = false;

	SoundBuffer soundbuffer;
	if (!soundbuffer.loadFromFile("assets/sounds/tone.wav")) {
		cout << "error. sound file not found.";
		return -1;
	}

	Sound sound;
	sound.setBuffer(soundbuffer);
	sound.setVolume(10);

	Font font;
	if (!font.loadFromFile("assets/fonts/uni-sans.heavy-italic-caps.otf")) {
		cout << "error. font file not found.";
		return -1;
	}

	Text text;
	text.setFont(font);
	text.setString("Press left mouse button to plot three points that form a triangle.");
	text.setCharacterSize(28);
	text.setFillColor(Color::Yellow);
	text.setPosition(30, 30);

	Clock timer;
	bool timerRestarted = false;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {

			// handling window exit
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}

			//handles fourth click to start the fractal generation
			if (event.type == Event::MouseButtonPressed &&
				event.key.code == Mouse::Left &&
				particles.size() == 3) {
				particles.push_back(Particle(Mouse::getPosition(window).x, Mouse::getPosition(window).y, 0, 0));
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && particles.size() <= 3) {
				particles.push_back(Particle(Mouse::getPosition(window).x, Mouse::getPosition(window).y, 0, 0));
			}


			//triggers black hole to be deployable
			//plus 4 because of the initial 4 particles
			if (particles.size() >= AMOUNT_OF_PARTICLES + 4) {
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
					gravitySource.push_back(Source(Mouse::getPosition(window).x, Mouse::getPosition(window).y, 10));
					blackHoleReady = true;
					

					if (!soundbuffer.loadFromFile("assets/sounds/explosion.wav")) {
						cout << "error. sound file not found.";
						return -1;
					}

					sound.setBuffer(soundbuffer);
					sound.setPitch(.5f);
					sound.setVolume(30);
					sound.play();
				}
			}
			
		}

		// dark blue background
		window.clear(Color(3, 5, 16));

		// when the three main points have been plotted
		if (particles.size() == 3) {
			text.setString("Place a fourth point inside the triangle to initiate the fractal generation.");
		}
		// after fourth has been set and dissapears when amount of particles is near the limit
		else if (particles.size() > 3 && particles.size() < AMOUNT_OF_PARTICLES + 4){
			text.setString("Generating.");
		}
		else if (particles.size() >= AMOUNT_OF_PARTICLES + 4){
			text.setString("Sierpinski's triangle complete.");

			if (!timerRestarted) {
				timer.restart();
				timerRestarted = true;
			}

			if (timer.getElapsedTime().asSeconds() > 3) {
				text.setString("Press right mouse button anywhere on the screen for something fun.");
			}

			if (timer.getElapsedTime().asSeconds() > 3 && blackHoleReady) {
				text.setString(":)");
			}
		}
		
		
		if (particles.size() >= 4 && particles.size() <= AMOUNT_OF_PARTICLES) {
			int sizeOfParticlesVec = particles.size();
			int raisingAmount = pow(2, particles.size() / 500) < 100 ? pow(2, particles.size() / 500) : 100;
			for (int i = 0; i < raisingAmount; i++) {

				//gradual rise in pitch
				sound.setPitch(0.0009 * particles.size());
				sound.play();

				//chaos game
				int randNum = rand() % 3;
				Vector2f previousParticle;
				previousParticle.x = particles.at(particles.size() - 1).getPos().x;
				previousParticle.y = particles.at(particles.size() - 1).getPos().y;
				
				Vector2f targetParticle;
				targetParticle.x = particles.at(randNum).getPos().x;
				targetParticle.y = particles.at(randNum).getPos().y;

				Vector2f newParticleCoords = calculateDistance(previousParticle, targetParticle);
				particles.push_back(Particle(newParticleCoords.x, newParticleCoords.y, 0, 0));
			}
		}

		for (int i = 0; i < particles.size(); i++) {
			particles.at(i).render(window);
		}
		if (blackHoleReady) {
			// 0 as there is only one gravity source
			gravitySource.at(0).render(window);
			for (int i = 0; i < particles.size(); i++) {

				particles.at(i).updatePhysics(gravitySource.at(0));
			}
		}

		//after text gets updated in the loop, it gets printed here
		window.draw(text);
		
		window.display();
	}

	


	return 0;
}
