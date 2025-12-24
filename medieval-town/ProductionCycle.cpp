#include "ProductionCycle.h"

namespace Models {
	ProductionCycle::ProductionCycle(int32 queue,
		const std::map<Resource, int32>& resourceInputs,
		const std::map<Resource, int32>& resourceOutputs)
		: queue(queue), resourceInputs(resourceInputs), resourceOutputs(resourceOutputs) {}

	int32 ProductionCycle::getQueue() const {
		return queue;
	}

	const std::map<Resource, int32>& ProductionCycle::getResourceInputs() const {
		return resourceInputs;
	}

	const std::map<Resource, int32>& ProductionCycle::getResourceOutputs() const {
		return resourceOutputs;
	}
}