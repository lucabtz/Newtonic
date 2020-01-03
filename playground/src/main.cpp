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

  Newtonic::Input::Init();

  Newtonic::Core::GetApplicationLogger().Info("Application started");

  Newtonic::Texture tex;
  { // make a scope for image resource
    Newtonic::Image image = Newtonic::Image::LoadPNG("/home/ekardnam/Downloads/awesomeface.png");
    ASSERT_TRUE(image.IsValid());
    tex.LoadFromImage(image);
  }

  Newtonic::Shader shader = Newtonic::Shader::CreateShader(R"(
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

  Newtonic::Vector3 cameraPosition(0.0, 0.0, 2.0);
  float cameraSpeed = 5.0;

  Newtonic::PerspectiveCamera camera;
  camera.SetAspectRatio(viewport);
  camera.SetFOV(glm::radians(45.0f));
  camera.SetZNear(0.1f);
  camera.SetZFar(100.0f);
  camera.SetPosition(cameraPosition);
  camera.LookAt(Newtonic::Vector3(0.0, 0.0, 0.0));

  Newtonic::Transform quadTransform;
  float quadRotationSpeed = 0.1f;

  Newtonic::Timestep time;
  do
  {
    float dt = time.DeltaTime();
    quadTransform.Rotate(glm::angleAxis(quadRotationSpeed * dt, Newtonic::Vector3(0,1,0)));
    Newtonic::Renderer::SetViewport(window.GetViewport());
    camera.SetPosition(cameraPosition);
    camera.SetAspectRatio(window.GetViewport());

    Newtonic::Renderer::Clear();

    if (Newtonic::Input::IsKeyDown(NW_KEY_W)) cameraPosition += Newtonic::Vector3(0.0, 0.0, -1.0) * cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_S)) cameraPosition += Newtonic::Vector3(0.0, 0.0, 1.0) * cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_A)) cameraPosition += Newtonic::Vector3(1.0, 0.0, 0.0) * cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_D)) cameraPosition += Newtonic::Vector3(-1.0, 0.0, 0.0) * cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_Q)) cameraPosition += Newtonic::Vector3(0.0, 1.0, 0.0) * cameraSpeed * dt;
    else if (Newtonic::Input::IsKeyDown(NW_KEY_E)) cameraPosition += Newtonic::Vector3(0.0, -1.0, 0.0) * cameraSpeed * dt;

    shader.Bind();
    shader.LoadMatrix4("u_transform", quadTransform.GetMatrix());
    shader.LoadMatrix4("u_view", camera.GetViewMatrix());
    shader.LoadMatrix4("u_proj", camera.GetProjectionMatrix());
    tex.Bind();
    shader.LoadUniform1i("u_texture", 0);
    Newtonic::Renderer::Render(va, ib);

    window.Update();
    Newtonic::EventBus::DispatchAll();
  } while(!window.ShouldClose());

  return 0;
}
