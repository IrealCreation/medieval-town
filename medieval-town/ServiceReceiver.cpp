#include "ServiceReceiver.h"
#include "Building.h"


namespace Models
{
	ServiceReceiver::ServiceReceiver() {}

	Building* ServiceReceiver::getServiceBuilding(Service service) const
	{
		if (serviceBuildings.find(service) != serviceBuildings.end())
			return serviceBuildings.at(service);
		else
			return nullptr;
	}
	std::map<Service, Building*> ServiceReceiver::getAllServiceBuildings() const
	{
		return serviceBuildings;
	}

	void ServiceReceiver::addService(Service service, Building* building)
	{
		serviceBuildings[service] = building;
	}
	void ServiceReceiver::removeService(Service service)
	{
		serviceBuildings.erase(service);
	}

}
