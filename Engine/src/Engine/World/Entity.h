#pragma once
#include <Engine/Containers/Array.h>
#include <Engine/Containers/String.h>
#include <Engine/World/Component.h>

namespace Engine
{
	class World;
	class ENGINE_API Entity
	{
		friend class World;
	public:
		Entity(const String& name = "Default Entity Name");
		~Entity();

		FORCEINLINE World* get_owner_world() const;

		void destroy_entity();

		template<typename TComponent,typename... TParameters>
		TComponent* create_component(TParameters... parameters);

		template<typename TComponent>
		bool delete_component();

		template<typename TComponent>
		TComponent* get_component() const;
	private:
		void _set_owner_world(World* ownerWorld);
		void _destroy();
	private:
		Array<Component*> Components;
		World* OwnerWorld;
		String Name;
	};


	template<typename TComponent, typename ...TParameters>
	inline TComponent* Entity::create_component(TParameters ...parameters)
	{
		TComponent* component = new TComponent(parameters...);

		component->_set_owner_entity(this);

		component->initialize();

		Components.add(component);

		return component;
	}

	template<typename TComponent>
	inline bool Entity::delete_component()
	{
		const String staticName = TComponent::get_static_class_name();

		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			Component* component = Components[i];

			if (component->get_class_name() == staticName)
			{
				component->finalize();
				delete component;
				Components.remove_index(i);
				return true;
			}
		}

		return false;
	}

	template<typename TComponent>
	inline TComponent* Entity::get_component() const
	{
		const String staticName = TComponent::get_static_class_name();

		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			Component* component = Components[i];

			if (component->get_class_name() == staticName)
			{
				return (TComponent*)component;
			}
		}

		return nullptr;
	}

}