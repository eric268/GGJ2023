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
	float dSize = size * deltaTime;
	playerCharacter->OnObjectEatten(playerCharacter->size + dSize);
	if (playerCharacter->size < 10.0f)
	{
		//Kill Player
		Response.DoneIf(true);
	}
	if (timeCounter >= totalTime)
	{
		Response.DoneIf(true);
	}
}