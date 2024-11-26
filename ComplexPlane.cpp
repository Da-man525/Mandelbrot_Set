#include "ComplexPlane.h"

using namespace sf;

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
