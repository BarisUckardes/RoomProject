#include "ApplicationModule.h"


namespace Engine
{
	ApplicationSession* ApplicationModule::get_owner_session() const
	{
		return OwnerSession;
	}
	void ApplicationModule::_set_owner_session(ApplicationSession* ownerSession)
	{
		OwnerSession = ownerSession;
	}
}