#include "TerrainFollowSystem.h"

#include "Terrain.h"
#include "Clock.h"

#include <glm\gtx\compatibility.hpp>

TerrainFollowSystem::TerrainFollowSystem(Scene& scene)
	: System(scene)
{
}

void TerrainFollowSystem::update()
{
	for (size_t i = 0; i < m_scene.getEntityCount(); ++i) {
		Entity& entity = m_scene.getEntity(i);

		if (!entity.hasComponents(COMPONENT_TERRAIN_FOLLOW, COMPONENT_TRANSFORM))
			continue;

		float terrainHeight;
		bool success = TerrainUtils::castPosToTerrainHeight(*entity.terrainFollow.terrainToFollow, entity.transform.position, terrainHeight);
		if (success) {
			float yPos = entity.transform.position.y;
			float halfHeight = entity.terrainFollow.followerHalfHeight;
			entity.transform.position.y = glm::lerp(yPos, terrainHeight + halfHeight, Clock::getDeltaTime() * 50.0f);
		}
	}
}

void TerrainFollowSystem::beginFrame()
{
}

void TerrainFollowSystem::endFrame()
{
}
