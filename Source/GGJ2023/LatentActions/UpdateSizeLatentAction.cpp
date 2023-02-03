#include "../LatentActions/UpdateSizeLatentAction.h"
#include "../Pawns/PlayerCharacter.h"

UpdatePlayerSizeLatentAction::UpdatePlayerSizeLatentAction(int id, APlayerCharacter* player, float dTime, float time, float sizeIncrease) :
	playerCharacter(player),
	deltaTime(dTime),
	totalTime(time),
	size(sizeIncrease),
	timeCounter(0.0f)
{}
void UpdatePlayerSizeLatentAction::UpdateOperation(FLatentResponse& Response)
{
	timeCounter += deltaTime;
	playerCharacter->OnObjectEatten(playerCharacter->size + size * deltaTime);
	if (timeCounter >= totalTime)
	{
		Response.DoneIf(true);
	}
}