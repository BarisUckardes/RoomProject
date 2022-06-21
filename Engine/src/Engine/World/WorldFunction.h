#pragma once
#include <Engine/Containers/String.h>

namespace Engine
{
	class World;

	/// <summary>
	/// Represents a single function of the world.(Rendering,logic,physics or ui)
	/// <para>Functions behaves as a bridge between components and target funcionts.It binds them together</para>
	/// </summary>
	class ENGINE_API WorldFunction
	{
		friend class World;
	public:
		WorldFunction() : OwnerWorld(nullptr) {}

		FORCEINLINE World* get_owner_world() const;

		FORCEINLINE virtual String get_class_name() const = 0;
		FORCEINLINE virtual void initialize() = 0;
		FORCEINLINE virtual void execute() = 0;
		FORCEINLINE virtual void finalize() = 0;
	private:
		void _set_owner_world(World* world);
	private:
		World* OwnerWorld;
	};

#define GENERATE_WORLD_FUNCTION(name) public: FORCEINLINE static Engine::String get_static_class_name() { return #name;} virtual Engine::String get_class_name() const { return #name;}

}