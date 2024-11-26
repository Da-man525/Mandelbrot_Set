#include "ComplexPlane.cpp"

using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
  
  m_pixel_width = pixelWidth;
  m_pixel_height = pixelHeight;
  m_vArray = VertexArray(Points, m_pixel_width * m_pixel_height);

  m_plane_center = sf::Vector2f(0.0f, 0.0f);
  m_plane_size = sf::Vector2f(BASE_WIDTH, BASE_HEIGHT);

  m_aspectRatio = static_cast<float>(m_pixel_width) / m_pixel_height;

  m_mouseLocation = Vector2f(0.0f, 0.0f);

  m_state = State::DISPLAYING;
  m_zoomCount = 0;
}
