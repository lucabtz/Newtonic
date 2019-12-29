#include "Newtonic.h"

const GLfloat g_quadVertices[] = {
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f
};

const GLuint g_quadIndices[] = {
  0, 1, 3,
  0, 2, 3
};

int main(int argc, char ** argv)
{
  Newtonic::Core::Init();
  Newtonic::Viewport viewport(1032, 558);
  Newtonic::Window window = Newtonic::Window::CreateWindow("Newtonic playground", viewport);
  Newtonic::Core::PostWindowInit();
  window.SetStickyKeys(true);

  Newtonic::Core::GetApplicationLogger().Info("Application started");
  Newtonic::Shader shader = Newtonic::Shader::CreateShader(R"(
    #version 330 core

    layout(location = 0) in vec3 vert;

    void main()
    {
      gl_Position = vec4(vert, 1.0);
    }
  )", R"(
    #version 330 core

    uniform vec3 u_color;
    out vec4 color;

    void main()
    {
      color = vec4(u_color, 1.0);
    }
  )");

  Newtonic::VertexBuffer vb(g_quadVertices, 12 * sizeof(GLfloat));
  Newtonic::VertexBufferLayout layout;
  layout.Add<GLfloat>(3);

  Newtonic::IndexBuffer ib(g_quadIndices, 6);

  Newtonic::VertexArray va;
  va.AddBuffer(vb, layout);

  do
  {
    Newtonic::Renderer::SetViewport(window.GetViewport());
    Newtonic::Renderer::Clear();

    shader.LoadVector3("u_color", Newtonic::Vector3(1, 1, 0));
    Newtonic::Renderer::Render(va, ib, shader);

    window.Update();
  } while(!window.ShouldClose());

  return 0;
}
