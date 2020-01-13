
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
    m_shaderId = Newtonic::AssetManager::PushResourceInfo(Newtonic::AssetResourceInfo(Newtonic::AssetResourceType::ShaderFilePair, "shader", "/home/ekardnam/Downloads/vert.glsl;/home/ekardnam/Downloads/frag.glsl"));
    m_shaderAsset = Newtonic::AssetManager::GetAsset<Newtonic::ShaderAsset>(m_shaderId);

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
  }

  void Render() override
  {
      Newtonic::Renderer::SetViewport(GetWindow().GetViewport());
      Newtonic::Renderer::Clear();

      m_texAsset->GetTexture().Bind();
      m_shaderAsset->GetShader().Bind();
      m_shaderAsset->GetShader().LoadMatrix4("u_transform", m_quadTransform.GetMatrix());
      m_shaderAsset->GetShader().LoadMatrix4("u_view", m_camera.GetViewMatrix());
      m_shaderAsset->GetShader().LoadMatrix4("u_proj", m_camera.GetProjectionMatrix());
      m_shaderAsset->GetShader().LoadUniform1i("u_texture", 0);
      Newtonic::Renderer::Render(m_mesh);
  }

private:
  Newtonic::Mesh m_mesh;
  unsigned int m_texId;
  std::shared_ptr<Newtonic::TextureAsset> m_texAsset;
  unsigned int m_shaderId;
  std::shared_ptr<Newtonic::ShaderAsset> m_shaderAsset;
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
