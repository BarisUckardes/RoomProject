#pragma once
#include <Engine/Containers/String.h>

namespace Engine
{
	class Entity;
	class ENGINE_API Component
	{
		friend class Entity;
	public:
		Component() : OwnerEntity(nullptr),Name("Default Component Name") {}
		~Component() = default;

		FORCEINLINE Entity* get_owner_entity() const;
		FORCEINLINE String get_name() const;

		FORCEINLINE void set_name(const String& name);

		FORCEINLINE virtual String get_class_name() const = 0;
		FORCEINLINE virtual void initialize() = 0;
		FORCEINLINE virtual void finalize() = 0;
	private:
		void _set_owner_entity(Entity* ownerEntity);
	private:
		Entity* OwnerEntity;
		String Name;
	};
#define GENERATE_COMPONENT(name) public: FORCEINLINE static Engine::String get_static_class_name() { return #name;} virtual Engine::String get_class_name() const override { return #name;}
}