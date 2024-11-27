#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size.x = pixelWidth;
    m_pixel_size.y = pixelHeight;
    m_plane_size.x = BASE_WIDTH;
    m_plane_size.y = BASE_HEIGHT;
    m_plane_center.x = 0.0f;
    m_plane_center.y = 0.0f;
    m_zoomCount = 0;
    m_aspectRatio = static_cast<float>(pixelWidth) / static_cast<float>(pixelHeight);
    m_vArray = VertexArray(Points, m_pixel_size.x * m_pixel_size.y);
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

	if (count == MAX_ITER) {
	r = 0;
	g = 0;
	b = 0;
        }
       else if (count >= 0 && count <= 12) {
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

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel){
	float mappedX = ((mousePixel.x - 0) / static_cast<float>(m_pixel_size.x - 0)) * m_plane_size.x
	+ (m_plane_center.x - m_plane_size.x / 2.0f);

	float mappedY = ((mousePixel.y - m_pixel_size.y) / static_cast<float>(0 - m_pixel_size.y)) * m_plane_size.y
	+ (m_plane_center.y - m_plane_size.y / 2.0f);

	return Vector2f(mappedX, mappedY);
}

void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		for (int i = 0; i < m_pixel_size.y; i++) {
			for (int j = 0; j < m_pixel_size.x; j++) {
				m_vArray[j + i * m_pixel_size.x].position = { (float)j, (float)i };
				Vector2f coord = mapPixelToCoords(Vector2i(j, i));
				int iterationCount = countIterations(coord);
				Uint8 r, g, b;
				iterationsToRGB(iterationCount, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r, g, b };

			}
		}
		m_state = State::DISPLAYING;
	}
}
