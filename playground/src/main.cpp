#include "Newtonic.h"

const GLfloat g_quadVertices[] = {
    0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
const GLfloat g_quadTex[] = {
1.0f, 1.0f,   // top right
 1.0f, 0.0f,   // bottom right
  0.0f, 0.0f,   // bottom left
   0.0f, 1.0f    // top left
};

const GLuint g_quadIndices[] = {
  0, 1, 3, // first triangle
  1, 2, 3  // second triangle
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
    Newtonic::Image image = Newtonic::Image::LoadPNG("/home/ekardnam/Downloads/awesomeface.png");
    ASSERT_TRUE(image.IsValid());
    tex.LoadFromImage(image);
  }

  Newtonic::Shader shader = Newtonic::Shader::CreateShader(R"(
    #version 330 core

    layout(location = 0) in vec3 vert;
    layout(location = 1) in vec2 texCoord;

    uniform mat4 u_view;
    uniform mat4 u_proj;

    out vec2 v_texCoord;

    void main()
    {
      gl_Position = u_proj * u_view * vec4(vert, 1.0);
      v_texCoord = texCoord;
    }
  )", R"(
    #version 330 core

    in vec2 v_texCoord;

    uniform sampler2D u_texture;

    out vec4 color;

    void main()
    {
      color = texture(u_texture, v_texCoord);
    }
  )");

  Newtonic::VertexBuffer vb1(g_quadVertices, 12 * sizeof(GLfloat));
  Newtonic::VertexBufferLayout layout1;
  layout1.Add<GLfloat>(3);

  Newtonic::VertexBuffer vb2(g_quadTex, 8 * sizeof(GLfloat));
  Newtonic::VertexBufferLayout layout2;
  layout2.Add<GLfloat>(2);

  Newtonic::IndexBuffer ib(g_quadIndices, 6);

  Newtonic::VertexArray va;
  va.AddBuffer(vb1, layout1);
  va.AddBuffer(vb2, layout2);

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

    shader.Bind();
    shader.LoadMatrix4("u_view", camera.GetViewMatrix());
    shader.LoadMatrix4("u_proj", camera.GetProjectionMatrix());
    tex.Bind();
    shader.LoadUniform1i("u_texture", 0);
    Newtonic::Renderer::Render(va, ib, shader);

    window.Update();
  } while(!window.ShouldClose());

  return 0;
}
