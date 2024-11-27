#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
  
  m_pixel_size.x = pixelWidth;
  m_pixel_size.y = pixelHeight;
  m_vArray = VertexArray(Points, m_pixel_size.x * m_pixel_size.y);

  m_plane_center = sf::Vector2f(0.0f, 0.0f);


  m_aspectRatio = static_cast<float>(m_pixel_size.x) / m_pixel_size.y;
  m_plane_size = sf::Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);

  m_mouseLocation = Vector2f(0.0f, 0.0f);

  m_state = State::CALCULATING;
  m_zoomCount = 0;
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const{
  target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	++m_zoomCount;
	Vector2f newsize;
	newsize.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	newsize.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = newsize;
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	--m_zoomCount;
	Vector2f newsize;
	newsize.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	newsize.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = newsize;
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	Vector2f currcoord = mapPixelToCoords(mousePixel);
	m_plane_center = currcoord;
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
	Vector2f currcoord = mapPixelToCoords(mousPixel);
	m_mouseLocation = currcoord;
}

int ComplexPlane::countIterations(Vector2f coord){
	Vector2f z(0.0f, 0.0f);

	const unsigned int maxIterations = MAX_ITER;

	for(int i = 0; i < maxIterations; i++){
		float realPart = pow(z.x, 2) - pow(z.y, 2) + coord.x;
		float imaginaryPart = 2.0f * z.x * z.y + coord.y;

		z.x = realPart;
		z.y = imaginaryPart;

		if(pow(z.x, 2) * pow(z.y, 2) > 4.0f){
			return i;
		}
	}
	return maxIterations;
}

void ComplexPlane::loadText(Text& text)
{
    stringstream outputtext;
	outputtext << "Mandelbrot Set" << endl << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	outputtext << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	outputtext << "Left-click to zoom in" << endl << "Right-click to zoom out";
	string outtext = outputtext.str();
	Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::Red);
	text.setString(outtext);

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

	if (count >= 0 && count <= 12) {
		r = 191;
		g = 0;
		b = 255;
	}
	else if (count >= 13 && count <= 25) {
		r = 0;
		g = 251;
		b = 255;
	}
	else if (count >= 26 && count <= 38) {
		r = 0;
		g = 255;
		b = 72;
	}
	else if (count >= 39 && count <= 51) {
		r = 238;
		g = 255;
		b = 0;
	}
	else {
		r = 255;
		g = 60;
		b = 0;
	}
}
