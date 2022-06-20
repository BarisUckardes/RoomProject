#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	class ApplicationSession;
	class WindowEvent;

	/// <summary>
	/// Represents a single responsibility of the entire application(input,rendering,ui and physics etc.)
	/// </summary>
	class ENGINE_API ApplicationModule
	{
		friend class Application;
	public:
		ApplicationModule() : OwnerSession(nullptr) {}
		~ApplicationModule() = default;

		/// <summary>
		/// Called upon first initialization
		/// </summary>
		FORCEINLINE virtual void initialize() = 0;

		/// <summary>
		/// Called upon every new frame
		/// </summary>
		FORCEINLINE virtual void tick() = 0;

		/// <summary>
		/// Called upon shut-down
		/// </summary>
		FORCEINLINE virtual void finalize() = 0;

		/// <summary>
		/// Called upon new window event receive
		/// </summary>
		/// <param name="event"></param>
		FORCEINLINE virtual void received_event(WindowEvent* event) = 0;
	protected:
		FORCEINLINE ApplicationSession* get_owner_session() const;

	private:
		void _set_owner_session(ApplicationSession* ownerSession);
	private:
		ApplicationSession* OwnerSession;
	};


}