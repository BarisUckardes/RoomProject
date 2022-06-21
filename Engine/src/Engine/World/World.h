#pragma once
#include <Engine/Containers/String.h>
#include <Engine/Containers/Array.h>
#include <Engine/World/WorldFunction.h>

namespace Engine
{
	class ApplicationSession;
	class Entity;
	class WorldFunction;

	/// <summary>
	/// Represents a collection of entities, components and world functions.
	/// </summary>
	class ENGINE_API World
	{
	public:
		World(ApplicationSession* ownerSession, const String& name);
		~World();

		FORCEINLINE const Array<Entity*>& get_entities() const;
		FORCEINLINE const Array<WorldFunction*> get_functions() const;
		FORCEINLINE ApplicationSession* get_owner_session() const;
		FORCEINLINE String get_name() const;

		Entity* create_entity(const String& name);
		void delete_entity(Entity* entity);

		template<typename TFunction,typename... TParameters>
		void create_function(TParameters... parameters);

		template<typename TFunction>
		TFunction* get_function() const;
	private:
		Array<Entity*> Entities;
		Array<WorldFunction*> Functions;
		ApplicationSession* OwnerSession;
		String Name;
	};

	template<typename TFunction, typename ...TParameters>
	inline void World::create_function(TParameters ...parameters)
	{
		TFunction* function = new TFunction(parameters...);

		function->_set_owner_world(this);

		function->initialize();

		Functions.add(function);
	}

	template<typename TFunction>
	inline TFunction* World::get_function() const
	{
		const String staticName = TFunction::get_static_class_name();

		for (unsigned int i = 0; i < Functions.get_cursor(); i++)
		{
			WorldFunction* function = Functions[i];

			if (function->get_class_name() == staticName)
				return (TFunction*)function;
		}

		return nullptr;
	}

}