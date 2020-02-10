
#include "Newtonic.h"
#include "NewtonicImGui.h"

using namespace Newtonic;

const MeshVertex g_quadVertices[] = {
    {Vector3(0.5f,  0.5f, 0.0f) , Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)},
    {Vector3(0.5f, -0.5f, 0.0f) , Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)},
    {Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)},
    {Vector3(-0.5f, 0.5f, 0.0f) , Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)}
};

const GLuint g_quadIndices[] = {
    0, 1, 3,
    1, 2, 3
};

class PlaygroundApplication : public Application
{
public:
  PlaygroundApplication(std::string name, const Viewport & viewport) : Application(name, viewport) {}
  void Setup() override
  {
    AssetManager::RegisterAsset("flatcolor", std::make_unique<ShaderLoadingInformation>(AssetType::Shader, "/home/ekardnam/Newtonic/res/flatcolorvert.glsl", "/home/ekardnam/Newtonic/res/flatcolorfrag.glsl"));
    AssetManager::RegisterAsset("textured", std::make_unique<ShaderLoadingInformation>(AssetType::Shader, "/home/ekardnam/Newtonic/res/texturedvert.glsl","/home/ekardnam/Newtonic/res/texturedfrag.glsl"));
    AssetManager::RegisterAsset("facetexture", std::make_unique<FileSystemLoadingInformation>(AssetType::Texture, "/home/ekardnam/Newtonic/res/awesomeface.png"));
    m_color = Vector4(1, 0, 0, 1);

    MaterialDefinition flatcolorMaterialInfo("flatcolor");
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_view", "View Matrix"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_transform", "Transform"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_proj", "Projection Matrix"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Float4Uniform>(m_color, "u_color", "Color"));

    MaterialDefinition texturedMaterialInfo("textured");
    texturedMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_view", "View Matrix"));
    texturedMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_transform", "Transform"));
    texturedMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_proj", "Projection Matrix"));
    texturedMaterialInfo.PushUniform(std::make_unique<TextureUniform>("facetexture", "u_texture", "Texture"));

    m_material.Instantiate(flatcolorMaterialInfo);

    m_mesh.SetVertices(g_quadVertices, 4);
    m_mesh.SetIndices(g_quadIndices, 6);
    m_mesh.FreeMemory();

    m_cameraPosition = Vector3(0.0f, 0.0f, 2.);
    m_cameraSpeed = 5.0f;

    m_camera.SetAspectRatio(GetWindow().GetViewport());
    m_camera.SetFOV(glm::radians(45.0f));
    m_camera.SetZNear(0.1f);
    m_camera.SetZFar(100.0f);
    m_camera.SetPosition(m_cameraPosition);
    m_camera.LookAt(Vector3(0.0, 0.0, 0.0));

    m_quadRotationSpeed = 1.0f;

    EventBus::Listen(EventType::WindowClose, [this](std::shared_ptr<Event> e)
    {
      this->Stop();
    });
  }

  void Update(float dt) override
  {
    m_quadTransform.Rotate(glm::angleAxis(m_quadRotationSpeed * dt, Vector3(0,1,0)));
    if (Input::IsKeyDown(NW_KEY_W)) m_cameraPosition += Vector3(0.0, 0.0, -1.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_S)) m_cameraPosition += Vector3(0.0, 0.0, 1.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_A)) m_cameraPosition += Vector3(1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_D)) m_cameraPosition += Vector3(-1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_Q)) m_cameraPosition += Vector3(0.0, 1.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_E)) m_cameraPosition += Vector3(0.0, -1.0, 0.0) * m_cameraSpeed * dt;

    m_camera.SetPosition(m_cameraPosition);
    m_camera.SetAspectRatio(GetWindow().GetViewport());

    m_material.SetMatrix4("View Matrix", m_camera.GetViewMatrix());
    m_material.SetMatrix4("Projection Matrix", m_camera.GetProjectionMatrix());
    m_material.SetMatrix4("Transform", m_quadTransform.GetMatrix());
    m_material.SetVector4("Color", m_color);
  }

  void Render() override
  {
      Renderer::SetViewport(GetWindow().GetViewport());
      Renderer::Clear();
      Renderer::Render(m_mesh, m_material);
  }

  void ImGuiRender() override
  {
    ImGui::Begin("Color");
    ImGui::ColorEdit3("Quad color", (float*)&m_color);
    ImGui::End();
  }

private:
  Mesh m_mesh;
  Material m_material;

  PerspectiveCamera m_camera;
  Vector3 m_cameraPosition;
  float m_cameraSpeed;

  Transform m_quadTransform;
  float m_quadRotationSpeed;

  Vector4 m_color;
};

int main()
{
  Core::Init();
  PlaygroundApplication app(std::string("Newtonic playground"), Viewport(1032, 558));
  app.Start();
  return 0;
}
