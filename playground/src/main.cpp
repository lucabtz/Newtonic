
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

class PlaygroundApplication : public Newtonic::Application
{
public:
  PlaygroundApplication(std::string name, const Newtonic::Viewport & viewport) : Newtonic::Application(name, viewport) {}
  void Setup() override
  {
    m_shader = Newtonic::Shader::CreateShader(R"(
      #version 430 core

      layout(location = 0) in vec3 vert;
      layout(location = 1) in vec2 texCoord;

      uniform mat4 u_transform;
      uniform mat4 u_view;
      uniform mat4 u_proj;

      out vec2 v_texCoord;

      void main()
      {
        gl_Position = u_proj * u_view * u_transform * vec4(vert, 1.0);
        v_texCoord = texCoord;
      }
    )", R"(
      #version 430 core

      in vec2 v_texCoord;

      uniform sampler2D u_texture;

      out vec4 color;

      void main()
      {
        color = texture(u_texture, v_texCoord);
      }
    )");

    { // make a scope for image resource
      Newtonic::Image image = Newtonic::Image::LoadPNG("/home/ekardnam/Downloads/awesomeface.png");
      ASSERT_TRUE(image.IsValid());
      m_texture.LoadFromImage(image);
    }

    m_vb1 = Newtonic::VertexBuffer(g_quadVertices, 12 * sizeof(GLfloat));
    Newtonic::VertexBufferLayout layout1;
    layout1.Add<GLfloat>(3);

    m_vb2 = Newtonic::VertexBuffer(g_quadTex, 8 * sizeof(GLfloat));
    Newtonic::VertexBufferLayout layout2;
    layout2.Add<GLfloat>(2);

    m_va.AddBuffer(m_vb1, layout1);
    m_va.AddBuffer(m_vb2, layout2);

    m_ib = Newtonic::IndexBuffer(g_quadIndices, 6);

    m_cameraPosition = Newtonic::Vector3(0.0f, 0.0f, 2.);
    m_cameraSpeed = 5.0f;

    m_camera.SetAspectRatio(GetWindow().GetViewport());
    m_camera.SetFOV(glm::radians(45.0f));
    m_camera.SetZNear(0.1f);
    m_camera.SetZFar(100.0f);
    m_camera.SetPosition(m_cameraPosition);
    m_camera.LookAt(Newtonic::Vector3(0.0, 0.0, 0.0));

    m_quadRotationSpeed = 1.0f;

    Newtonic::EventBus::Listen(Newtonic::EventType::WindowClose, [this](std::shared_ptr<Newtonic::Event> e)
    {
      this->Stop();
    });
  }

  void Update(float dt) override
  {
    m_quadTransform.Rotate(glm::angleAxis(m_quadRotationSpeed * dt, Newtonic::Vector3(0,1,0)));
    if (Newtonic::Input::IsKeyDown(NW_KEY_W)) m_cameraPosition += Newtonic::Vector3(0.0, 0.0, -1.0) * m_cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_S)) m_cameraPosition += Newtonic::Vector3(0.0, 0.0, 1.0) * m_cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_A)) m_cameraPosition += Newtonic::Vector3(1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_D)) m_cameraPosition += Newtonic::Vector3(-1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_Q)) m_cameraPosition += Newtonic::Vector3(0.0, 1.0, 0.0) * m_cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_E)) m_cameraPosition += Newtonic::Vector3(0.0, -1.0, 0.0) * m_cameraSpeed * dt;

    m_camera.SetPosition(m_cameraPosition);
    m_camera.SetAspectRatio(GetWindow().GetViewport());
  }

  void Render() override
  {
      Newtonic::Renderer::SetViewport(GetWindow().GetViewport());
      Newtonic::Renderer::Clear();

      m_shader.Bind();
      m_shader.LoadMatrix4("u_transform", m_quadTransform.GetMatrix());
      m_shader.LoadMatrix4("u_view", m_camera.GetViewMatrix());
      m_shader.LoadMatrix4("u_proj", m_camera.GetProjectionMatrix());
      m_texture.Bind();
      m_shader.LoadUniform1i("u_texture", 0);
      Newtonic::Renderer::Render(m_va, m_ib);
  }

private:
  Newtonic::Shader m_shader;
  Newtonic::Texture m_texture;
  Newtonic::VertexArray m_va;
  Newtonic::VertexBuffer m_vb1;
  Newtonic::VertexBuffer m_vb2;
  Newtonic::IndexBuffer m_ib;
  Newtonic::PerspectiveCamera m_camera;
  Newtonic::Vector3 m_cameraPosition;
  float m_cameraSpeed;
  Newtonic::Transform m_quadTransform;
  float m_quadRotationSpeed;
};

int main()
{
  Newtonic::Core::Init();
  PlaygroundApplication app(std::string("Newtonic playground"), Newtonic::Viewport(1032, 558));
  app.Start();
  return 0;
}
