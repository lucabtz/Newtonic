
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

struct MaterialPoint
{
  float mass;
  Transform transform;
  Vector3 velocity;
};

#define G 1

class PlaygroundApplication : public Application
{
public:
  PlaygroundApplication(std::string name, const Viewport & viewport) : Application(name, viewport) {}
  void Setup() override
  {
    AssetManager::RegisterAsset("facetexture", std::make_unique<FileSystemLoadingInformation>(AssetType::Texture, "/home/ekardnam/Newtonic/res/awesomeface.png"));
    m_colorSun = Vector4(1, 0, 0, 1);
    m_colorEarth = m_colorSun;

    MaterialDefinition flatcolorMaterialInfo(Shader::CreateShader(ReadFile("/home/ekardnam/Newtonic/res/flatcolorvert.glsl").c_str(), ReadFile("/home/ekardnam/Newtonic/res/flatcolorfrag.glsl").c_str()));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_view", "View Matrix"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_transform", "Transform"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Mat4Uniform>(Matrix4(), "u_proj", "Projection Matrix"));
    flatcolorMaterialInfo.PushUniform(std::make_unique<Float4Uniform>(m_colorSun, "u_color", "Color"));

    m_sunMaterial.Instantiate(flatcolorMaterialInfo);
    m_earthMaterial.Instantiate(flatcolorMaterialInfo);

    float r = 10;
    float mass = 10;
    float force = G * (mass * mass)/(r * r);
    float velocity = std::sqrt((force * r)/(2 * mass));

    m_sun.mass = mass;
    m_sun.transform.SetPosition(Vector3(0, 0, 0));
    m_sun.velocity = Vector3(0, 0, velocity);

    m_earth.mass = mass;
    m_earth.transform.SetPosition(Vector3(r, 0, 0));
    m_earth.velocity = Vector3(0, 0, -velocity);


    float radius = 1.0;
    int stackCount = 10;
    int sectorCount = 10;

    std::vector<MeshVertex> vertices;
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;

            vertices.push_back({Vector3(x, y, z), Vector3(nx, ny, nz), Vector2(s, t)});
        }
    }

    std::vector<unsigned int> indices;
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    m_mesh.SetVertices(&vertices[0], vertices.size());
    m_mesh.SetIndices(&indices[0], indices.size());
    m_mesh.FreeMemory();

    m_cameraPosition = Vector3(0.0f, 0.0f, 10.);
    m_cameraSpeed = 5.0f;

    m_camera.SetAspectRatio(GetWindow().GetViewport());
    m_camera.SetFOV(glm::radians(45.0f));
    m_camera.SetZNear(0.1f);
    m_camera.SetZFar(100.0f);
    m_camera.SetPosition(m_cameraPosition);
    m_camera.LookAt(Vector3(0.0, 0.0, 0.0));

    EventBus::Listen(EventType::WindowClose, [this](std::shared_ptr<Event> e)
    {
      this->Stop();
    });
  }

  void Update(float dt) override
  {
    if (Input::IsKeyDown(NW_KEY_W)) m_cameraPosition += Vector3(0.0, 0.0, -1.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_S)) m_cameraPosition += Vector3(0.0, 0.0, 1.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_A)) m_cameraPosition += Vector3(1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_D)) m_cameraPosition += Vector3(-1.0, 0.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_Q)) m_cameraPosition += Vector3(0.0, 1.0, 0.0) * m_cameraSpeed * dt;
    else if (Input::IsKeyDown(NW_KEY_E)) m_cameraPosition += Vector3(0.0, -1.0, 0.0) * m_cameraSpeed * dt;

    m_camera.SetPosition(m_cameraPosition);
    m_camera.SetAspectRatio(GetWindow().GetViewport());


    Vector3 axis = glm::normalize(m_sun.transform.GetPosition() - m_earth.transform.GetPosition());
    float force = G * (m_sun.mass * m_earth.mass)/glm::length2(m_sun.transform.GetPosition() - m_earth.transform.GetPosition());
    float earthAcceleration = force / m_earth.mass;
    float sunAcceleration = force / m_sun.mass;

    Vector3 earthdv = earthAcceleration * dt * axis;
    Vector3 sundv = - sunAcceleration * dt * axis;
    Vector3 earthds = m_earth.velocity * dt;
    Vector3 sunds = m_sun.velocity * dt;

    m_earth.velocity += earthdv;
    m_sun.velocity += sundv;
    m_earth.transform.SetPosition(m_earth.transform.GetPosition() + earthds);
    m_sun.transform.SetPosition(m_sun.transform.GetPosition() + sunds);
  }

  void Render() override
  {
      m_sunMaterial.SetMatrix4("View Matrix", m_camera.GetViewMatrix());
      m_sunMaterial.SetMatrix4("Projection Matrix", m_camera.GetProjectionMatrix());
      m_earthMaterial.SetMatrix4("View Matrix", m_camera.GetViewMatrix());
      m_earthMaterial.SetMatrix4("Projection Matrix", m_camera.GetProjectionMatrix());
      m_sunMaterial.SetVector4("Color", m_colorSun);
      m_earthMaterial.SetVector4("Color", m_colorEarth);
      m_earthMaterial.SetMatrix4("Transform", m_earth.transform.GetMatrix());
      m_sunMaterial.SetMatrix4("Transform", m_sun.transform.GetMatrix());


      Renderer::SetViewport(GetWindow().GetViewport());
      Renderer::Clear();

      Renderer::Render(m_mesh, m_earthMaterial);
      Renderer::Render(m_mesh, m_sunMaterial);
  }

  void ImGuiRender() override
  {
    ImGui::Begin("Color");
    ImGui::ColorEdit3("Sun color", (float*)&m_colorSun);
    ImGui::ColorEdit3("Earth color", (float*)&m_colorEarth);
    ImGui::End();
  }

private:
  Mesh m_mesh;

  PerspectiveCamera m_camera;
  Vector3 m_cameraPosition;
  float m_cameraSpeed;

  Material m_sunMaterial;
  MaterialPoint m_sun;
  Material m_earthMaterial;
  MaterialPoint m_earth;

  Vector4 m_colorSun;
  Vector4 m_colorEarth;
};

int main()
{
  Core::Init();
  PlaygroundApplication app(std::string("Newtonic playground"), Viewport(1032, 558));
  app.Start();
  return 0;
}
