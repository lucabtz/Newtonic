
#include "Newtonic.h"
#include <fstream>

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
    {
      Newtonic::GameObject root;
      root.SetName("Scene");
      std::unique_ptr<Newtonic::GameObject> child = std::make_unique<Newtonic::GameObject>();
      child->SetName("Quad");
      child->AddComponent(std::make_unique<Newtonic::TransformComponent>());
      root.AddChild(std::move(child));

      std::ofstream stream("scene.nw");
      cereal::JSONOutputArchive archive(stream);
      archive(root);
      ASSERT_TRUE(root.GetChildrenCount() == 1);
      ASSERT_TRUE(root.GetChild(0)->GetParent() == &root);
    }

    std::ifstream in("scene.nw");
    cereal::JSONInputArchive inarchive(in);
    Newtonic::GameObject scene;
    inarchive(scene);

    std::cout << scene.GetName() << std::endl;
    ASSERT_TRUE(scene.GetChildrenCount() == 1);
    ASSERT_TRUE(scene.GetChild(0)->GetParent() == &scene);
  }

  void Update(float dt) override
  {

  }

  void Render() override
  {

  }
};

int main()
{
  Newtonic::Core::Init();
  PlaygroundApplication app(std::string("Newtonic playground"), Newtonic::Viewport(1032, 558));
  app.Start();
  return 0;
}
