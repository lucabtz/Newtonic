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

  Newtonic::Texture tex;
  { // make a scope for image resource
    Newtonic::Image image = Newtonic::Image::LoadPNG("~/Downloads/wallpaper.png");
    tex.LoadFromImage(image);
  }

  Newtonic::Shader shader = Newtonic::Shader::CreateShader(R"(
    #version 330 core

    layout(location = 0) in vec3 vert;

    uniform mat4 u_view;
    uniform mat4 u_proj;

    void main()
    {
      gl_Position = u_proj * u_view * vec4(vert, 1.0);
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

  Newtonic::PerspectiveCamera camera;
  camera.SetAspectRatio(viewport);
  camera.SetFOV(glm::radians(45.0f));
  camera.SetZNear(0.1f);
  camera.SetZFar(100.0f);
  camera.SetPosition(Newtonic::Vector3(2.0, 0.0, 2.0));
  camera.LookAt(Newtonic::Vector3(0.0, 0.0, 0.0));

  do
  {
    Newtonic::Renderer::SetViewport(window.GetViewport());
    camera.SetAspectRatio(window.GetViewport());

    Newtonic::Renderer::Clear();

    shader.LoadVector3("u_color", Newtonic::Vector3(1, 1, 0));
    shader.LoadMatrix4("u_view", camera.GetViewMatrix());
    shader.LoadMatrix4("u_proj", camera.GetProjectionMatrix());
    Newtonic::Renderer::Render(va, ib, shader);

    window.Update();
  } while(!window.ShouldClose());

  return 0;
}
