#pragma once
#include <Engine/World/WorldFunction.h>
#include <Engine/Containers/Array.h>

namespace Engine
{
	class ObserverComponent;
	class ForwardPointLight;
	class ForwardSpotLight;
	class ForwardRenderable;
	class ENGINE_API ForwardRendererFunction : public WorldFunction
	{
		GENERATE_WORLD_FUNCTION(ForwardRendererFunction)
	public:
		ForwardRendererFunction() : Observer(nullptr) {}
		~ForwardRendererFunction() = default;

		FORCEINLINE void register_renderable(ForwardRenderable* renderable);
		FORCEINLINE void remove_renderable(ForwardRenderable* renderable);

		FORCEINLINE void set_observer(ObserverComponent* observer);

		FORCEINLINE void register_point_light(ForwardPointLight* pointLight);
		FORCEINLINE void remove_point_light(ForwardPointLight* pointLight);

		FORCEINLINE void register_spot_light(ForwardSpotLight* spotLight);
		FORCEINLINE void remove_spot_light(ForwardSpotLight* spotLight);

		virtual void initialize() override;
		virtual void execute() override;
		virtual void finalize() override;
	private:
		Array<ForwardRenderable*> Renderables;
		Array<ForwardPointLight*> PointLights;
		Array<ForwardSpotLight*> SpotLights;
		ObserverComponent* Observer;
	};


}