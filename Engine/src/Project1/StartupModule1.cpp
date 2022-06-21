#include "StartupModule1.h"
#include <Engine/World/World.h>
#include <Engine/Message/Message.h>
#include <Engine/World/Entity.h>
#include <Engine/Application/ApplicationSession.h>
#include <IterativeLogic/LogicComponent.h>
#include <IterativeLogic/IterativeLogicFunction.h>
#include <ForwardRenderer/ForwardRendererFunction.h>
#include <Project1/Components/FirstPersonCameraComponent.h>
#include <ForwardRenderer/SpatialComponent.h>
#include <ForwardRenderer/ForwardRenderable.h>
#include <ForwardRenderer/ObserverComponent.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Shader/ShaderProgram.h>
#include <Engine/Graphics/Mesh/Mesh.h>
#include <Resources/Shaders.h>
#include <Resources/Meshes.h>
#include <Engine/Path/PathUtils.h>
#include <Engine/Graphics/Texture/Texture2D.h>
#include <Engine/Graphics/Material/Material.h>
#include <ForwardRenderer/ForwardPointLight.h>
#include <Project1/Components/OrbitComponent.h>
#include <ForwardRenderer/ForwardSpotLight.h>
#include <GUI/UISwitchButton.h>
#include <GUI/GUIResolverFunction.h>

#define CAMERA_MOVEMENT_SPEED 10.0f
#define CAMERA_ANGULAR_SPEED 5.0f

namespace Engine
{
	World* gameWorld = nullptr;
	void StartupModule1::initialize()
	{
		/*
		* Load resource
		*/
		Shader* litTextureVertexShader = new Shader(g_LitTextureVertexShader,ShaderStage::Vertex);
		Shader* litTextureFragmentShader = new Shader(g_LitTextureFragmentShader,ShaderStage::Fragment);
		ShaderProgram* litTextureProgram = new ShaderProgram({ litTextureVertexShader,litTextureFragmentShader });

		Shader* uiVertexShader = new Shader(g_UIVertexShader, ShaderStage::Vertex);
		Shader* uiFragmentShader = new Shader(g_UIFragmentShader, ShaderStage::Fragment);
		ShaderProgram* uiProgram = new ShaderProgram({ uiVertexShader,uiFragmentShader });

		Array<MeshVertexElementDesc> meshVertexElements;
		meshVertexElements.add(MeshVertexElementDesc("Position", MeshVertexElementType::Float3, false));
		meshVertexElements.add(MeshVertexElementDesc("Normal", MeshVertexElementType::Float3, false));
		meshVertexElements.add(MeshVertexElementDesc("Uv", MeshVertexElementType::Float2, false));

		MeshVertexLayout vertexLayout(meshVertexElements);

		Mesh* mesh = new Mesh(vertexLayout);
		
		const Array<MeshVertex> planeVertexes = get_plane_vertexes();
		const Array<unsigned int> planeIndexes = get_plane_indexes();

		mesh->allocate_vertex_data(sizeof(MeshVertex) * planeVertexes.get_cursor());
		mesh->allocate_index_data(sizeof(unsigned int) * planeIndexes.get_cursor(), planeIndexes.get_cursor());

		mesh->update_vertex_data(planeVertexes.get_data());
		mesh->update_index_data(planeIndexes.get_data());

		Array<MeshVertexElementDesc> uiMeshVertexElements;
		uiMeshVertexElements.add(MeshVertexElementDesc("Position", MeshVertexElementType::Float2, false));

		Mesh* uiRectMesh = new Mesh(uiMeshVertexElements);
		
		Array<UIVertex> uiVertexes = get_ui_rect_vertexes();
		Array<unsigned int> uiIndexes = get_ui_rect_indexes();
		uiRectMesh->allocate_vertex_data(sizeof(UIVertex) * uiVertexes.get_cursor());
		uiRectMesh->allocate_index_data(sizeof(unsigned int) * uiIndexes.get_cursor(), uiIndexes.get_cursor());

		uiRectMesh->update_vertex_data(uiVertexes.get_data());
		uiRectMesh->update_index_data(uiIndexes.get_data());

		Texture2D* floorTexture0 = new Texture2D(PathUtils::get_relative_path("\\floor0_color.jpg"));
		Texture2D* wallTexture0 = new Texture2D(PathUtils::get_relative_path("\\wall0_color.jpg"));
		Texture2D* roofTexture0 = new Texture2D(PathUtils::get_relative_path("\\roof0_color.jpg"));

		Material* floorMaterial = new Material(litTextureProgram);
		floorMaterial->set_texture_parameter("f_Texture", floorTexture0);
		floorMaterial->set_float_parameter("f_Tiling", 15.0f);

		Material* wallMaterial = new Material(litTextureProgram);
		wallMaterial->set_texture_parameter("f_Texture", wallTexture0);
		wallMaterial->set_float_parameter("f_Tiling", 3.0f);

		Material* roofMaterial = new Material(litTextureProgram);
		roofMaterial->set_texture_parameter("f_Texture", roofTexture0);
		roofMaterial->set_float_parameter("f_Tiling", 3.0f);

		Material* uiMaterial = new Material(uiProgram);
		uiMaterial->set_vec3_parameter("f_Color", {1.0f,0.0f,0.0f});

		/*
		* Create world and functions
		*/
		gameWorld = get_owner_session()->create_world("Project1 World");
		gameWorld->create_function<IterativeLogicFunction>();
		gameWorld->create_function<ForwardRendererFunction>();
		gameWorld->create_function<GUIResolverFunction>();

		/*
		* Create floor
		*/
		Entity* floorEntity = gameWorld->create_entity("Floor Entity");
		SpatialComponent* floorSpatial = floorEntity->create_component<SpatialComponent>();
		floorSpatial->set_scale({ 50,50,50 });
		
		ForwardRenderable* floorRenderable = floorEntity->create_component<ForwardRenderable>();
		floorRenderable->set_material(floorMaterial);
		floorRenderable->set_static_mesh(mesh);

		/*
		* Create walls
		*/
		Entity* wallEntity0 = gameWorld->create_entity("Wall entity");
		SpatialComponent* wallSpatial = wallEntity0->create_component<SpatialComponent>();
		wallSpatial->set_scale({ 50, 50, 50 });
		wallSpatial->set_position({ 50,-20,0 });
		wallSpatial->set_rotation({ 0,0,90 });

		ForwardRenderable* wallRenderable0 = wallEntity0->create_component<ForwardRenderable>();
		wallRenderable0->set_material(wallMaterial);
		wallRenderable0->set_static_mesh(mesh);

		Entity* wallEntity1 = gameWorld->create_entity("Wall entity");
		SpatialComponent* wallSpatial1 = wallEntity1->create_component<SpatialComponent>();
		wallSpatial1->set_scale({ 50, 50, 50 });
		wallSpatial1->set_position({-50,-20,0 });
		wallSpatial1->set_rotation({ 0,0,-90 });

		ForwardRenderable* wallRenderable1 = wallEntity1->create_component<ForwardRenderable>();
		wallRenderable1->set_material(wallMaterial);
		wallRenderable1->set_static_mesh(mesh);

		Entity* wallEntity2 = gameWorld->create_entity("Wall entity");
		SpatialComponent* wallSpatial2 = wallEntity2->create_component<SpatialComponent>();
		wallSpatial2->set_scale({ 50, 50, 50 });
		wallSpatial2->set_position({ 0,-20,50 });
		wallSpatial2->set_rotation({ -90,0,0 });

		ForwardRenderable* wallRenderable2 = wallEntity2->create_component<ForwardRenderable>();
		wallRenderable2->set_material(wallMaterial);
		wallRenderable2->set_static_mesh(mesh);

		Entity* wallEntity3 = gameWorld->create_entity("Wall entity");
		SpatialComponent* wallSpatial3 = wallEntity3->create_component<SpatialComponent>();
		wallSpatial3->set_scale({ 50, 50, 50 });
		wallSpatial3->set_position({ 0,-20,-50 });
		wallSpatial3->set_rotation({ 90,0,0 });

		ForwardRenderable* wallRenderable3 = wallEntity3->create_component<ForwardRenderable>();
		wallRenderable3->set_material(wallMaterial);
		wallRenderable3->set_static_mesh(mesh);

		/*
		* Create roof
		*/
		Entity* roofEntity = gameWorld->create_entity("Wall entity");
		SpatialComponent* roofSpatial = roofEntity->create_component<SpatialComponent>();
		roofSpatial->set_scale({ 50, 50, 50 });
		roofSpatial->set_position({ 0,30,0 });
		roofSpatial->set_rotation({ 0,0,180 });

		ForwardRenderable* roofRenderable = roofEntity->create_component<ForwardRenderable>();
		roofRenderable->set_material(roofMaterial);
		roofRenderable->set_static_mesh(mesh);

		/*
		* Create point lights
		*/
		Entity* pointLightEntity0 = gameWorld->create_entity("Point light 0");
		SpatialComponent* pointLightSpatial = pointLightEntity0->create_component<SpatialComponent>();
		pointLightSpatial->set_position({ 0,5,0 });

		ForwardPointLight* pointLight0 = pointLightEntity0->create_component<ForwardPointLight>();
		pointLight0->set_range(35);
		pointLight0->set_color({ 0.94f,0.82f,0.88f });
		pointLightEntity0->create_component<OrbitComponent>();

		Entity* pointLightEntity1 = gameWorld->create_entity("Point light 0");
		SpatialComponent* pointLightSpatial1 = pointLightEntity1->create_component<SpatialComponent>();
		pointLightSpatial1->set_position({ 45,5,0 });

		ForwardPointLight* pointLight1 = pointLightEntity1->create_component<ForwardPointLight>();
		pointLight1->set_range(35);
		pointLight1->set_color({ 0.94f,0.82f,0.88f });

		Entity* pointLightEntity2 = gameWorld->create_entity("Point light 0");
		SpatialComponent* pointLightSpatial2 = pointLightEntity2->create_component<SpatialComponent>();
		pointLightSpatial2->set_position({ 45,5,30 });

		ForwardPointLight* pointLight2 = pointLightEntity2->create_component<ForwardPointLight>();
		pointLight2->set_range(35);
		pointLight2->set_color({ 0.0f,0.0f,0.88f });

		/*
		* Create spot light
		*/
		Entity* spotLightEntity0 = gameWorld->create_entity("SpotLight 0");
		SpatialComponent* spotLightSpatial0 = spotLightEntity0->create_component<SpatialComponent>();
		spotLightSpatial0->set_position({ 25,10,-25 });
		spotLightSpatial0->set_rotation({ -90,0,0 });

		ForwardSpotLight* spotLight0 = spotLightEntity0->create_component<ForwardSpotLight>();
		spotLight0->set_radius(50);
		spotLight0->set_range(90);
		spotLight0->set_color({ 0,0,1.0f });

		Entity* spotLightEntity1 = gameWorld->create_entity("SpotLight 0");
		SpatialComponent* spotLightSpatial1 = spotLightEntity1->create_component<SpatialComponent>();
		spotLightSpatial1->set_position({ -25,10,-25 });
		spotLightSpatial1->set_rotation({ -90,0,0 });

		ForwardSpotLight* spotLight1 = spotLightEntity1->create_component<ForwardSpotLight>();
		spotLight1->set_radius(50);
		spotLight1->set_range(90);
		spotLight1->set_color({ 0,0,1.0f });

		Entity* spotLightEntity2 = gameWorld->create_entity("SpotLight 0");
		SpatialComponent* spotLightSpatial2 = spotLightEntity2->create_component<SpatialComponent>();
		spotLightSpatial2->set_position({ 0,10,25 });
		spotLightSpatial2->set_rotation({ -90,0,0 });

		ForwardSpotLight* spotLight2 = spotLightEntity2->create_component<ForwardSpotLight>();
		spotLight2->set_radius(50);
		spotLight2->set_range(90);
		spotLight2->set_color({ 0,0,1.0f });

		/*
		* Create camera
		*/
		Entity* cameraEntity = gameWorld->create_entity("Camera Entity");
		SpatialComponent* cameraSpatialComponent = cameraEntity->create_component<SpatialComponent>();
		cameraSpatialComponent->set_position({ 0,2,-5 });
		
		ObserverComponent* cameraObserverComponent = cameraEntity->create_component<ObserverComponent>();

		FirstPersonCameraComponent* cameraFPSControllerComponent = cameraEntity->create_component<FirstPersonCameraComponent>();

		/*
		* Create ui
		*/
		Entity* uiRectEntity0 = gameWorld->create_entity("Ui rect 0");
		SpatialComponent* uiRectSpatial = uiRectEntity0->create_component<SpatialComponent>();
		uiRectSpatial->set_position({0.0f,0.95f,0.0f});

		UISwitchButton* uiRectButton0 = uiRectEntity0->create_component<UISwitchButton>(pointLight0);
		uiRectButton0->set_color({ 0.0f,0.0f,1.0f });
		uiRectButton0->set_material(uiMaterial);
		uiRectButton0->set_mesh(uiRectMesh);

		Entity* uiRectEntity1 = gameWorld->create_entity("Ui rect 0");
		SpatialComponent* uiRectSpatial1 = uiRectEntity1->create_component<SpatialComponent>();
		uiRectSpatial1->set_position({ 0.25f,0.95f,0.0f });

		UISwitchButton* uiRectButton1 = uiRectEntity1->create_component<UISwitchButton>(spotLight0);
		uiRectButton1->set_color({ 0.2f,0.3f,0.4f });
		uiRectButton1->set_material(uiMaterial);
		uiRectButton1->set_mesh(uiRectMesh);


		Entity* uiRectEntity2 = gameWorld->create_entity("Ui rect 0");
		SpatialComponent* uiRectSpatial2 = uiRectEntity2->create_component<SpatialComponent>();
		uiRectSpatial2->set_position({ 0.5f,0.95f,0.0f });

		UISwitchButton* uiRectButton2 = uiRectEntity2->create_component<UISwitchButton>(spotLight1);
		uiRectButton2->set_color({ 0.4f,0.1f,0.7f });
		uiRectButton2->set_material(uiMaterial);
		uiRectButton2->set_mesh(uiRectMesh);

		Entity* uiRectEntity3 = gameWorld->create_entity("Ui rect 0");
		SpatialComponent* uiRectSpatial3 = uiRectEntity3->create_component<SpatialComponent>();
		uiRectSpatial3->set_position({ 0.75f,0.95f,0.0f });

		UISwitchButton* uiRectButton3 = uiRectEntity3->create_component<UISwitchButton>(spotLight2);
		uiRectButton3->set_color({ 0.2f,0.4f,0.6f });
		uiRectButton3->set_material(uiMaterial);
		uiRectButton3->set_mesh(uiRectMesh);

		MESSAGE("StartupModule", "Startup module initialized");
	}

	void StartupModule1::tick()
	{

	}

	void StartupModule1::finalize()
	{
		MESSAGE("StartupModule", "Startup module finalized");
	}

	void StartupModule1::received_event(Engine::WindowEvent* event)
	{

	}

	void StartupModule1::post_tick()
	{
	}

}