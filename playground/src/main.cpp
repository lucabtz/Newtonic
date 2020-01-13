
#include "Newtonic.h"

const Newtonic::MeshVertex g_quadVertices[] = {
    {Newtonic::Vector3(0.5f,  0.5f, 0.0f) , Newtonic::Vector3(0.0f, 0.0f, 0.0f), Newtonic::Vector2(1.0f, 1.0f)},
    {Newtonic::Vector3(0.5f, -0.5f, 0.0f) , Newtonic::Vector3(0.0f, 0.0f, 0.0f), Newtonic::Vector2(1.0f, 0.0f)},
    {Newtonic::Vector3(-0.5f, -0.5f, 0.0f), Newtonic::Vector3(0.0f, 0.0f, 0.0f), Newtonic::Vector2(0.0f, 0.0f)},
    {Newtonic::Vector3(-0.5f, 0.5f, 0.0f) , Newtonic::Vector3(0.0f, 0.0f, 0.0f), Newtonic::Vector2(0.0f, 1.0f)}
};

const GLuint g_quadIndices[] = {
    0, 1, 3,
    1, 2, 3
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
      layout(location = 1) in vec3 normal;
      layout(location = 2) in vec2 texCoord;

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

    m_texId = Newtonic::AssetManager::PushResourceInfo(Newtonic::AssetResourceInfo(Newtonic::AssetResourceType::TexturePNG, "texture", "/home/ekardnam/Downloads/awesomeface.png"));
    m_texAsset = Newtonic::AssetManager::GetAsset<Newtonic::TextureAsset>(m_texId);

    m_mesh.SetVertices(g_quadVertices, 4);
    m_mesh.SetIndices(g_quadIndices, 6);
    m_mesh.FreeMemory();

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

    if (m_unloadTexCountdown > 0)
      m_unloadTexCountdown -= dt;
    else
    {
      m_texAsset.reset();
    }
  }

  void Render() override
  {
      Newtonic::Renderer::SetViewport(GetWindow().GetViewport());
      Newtonic::Renderer::Clear();

      if (m_texAsset)
        m_texAsset->GetTexture().Bind();
      m_shader.Bind();
      m_shader.LoadMatrix4("u_transform", m_quadTransform.GetMatrix());
      m_shader.LoadMatrix4("u_view", m_camera.GetViewMatrix());
      m_shader.LoadMatrix4("u_proj", m_camera.GetProjectionMatrix());
      m_shader.LoadUniform1i("u_texture", 0);
      Newtonic::Renderer::Render(m_mesh);
  }

private:
  Newtonic::Shader m_shader;
  Newtonic::Mesh m_mesh;
  unsigned int m_texId;
  std::shared_ptr<Newtonic::TextureAsset> m_texAsset;
  Newtonic::PerspectiveCamera m_camera;
  Newtonic::Vector3 m_cameraPosition;
  float m_cameraSpeed;
  Newtonic::Transform m_quadTransform;
  float m_quadRotationSpeed;
  float m_unloadTexCountdown = 10.0f;
};

int main()
{
  Newtonic::Core::Init();
  PlaygroundApplication app(std::string("Newtonic playground"), Newtonic::Viewport(1032, 558));
  app.Start();
  return 0;
}
