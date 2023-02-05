#include "../LatentActions/UpdateSizeLatentAction.h"
#include "../Pawns/PlayerCharacter.h"
#include "../UI/PlayerHUD.h"
UpdatePlayerSizeLatentAction::UpdatePlayerSizeLatentAction(int id, APlayerCharacter* player, float dTime, float time, float sizeIncrease) :
	playerCharacter(player),
	deltaTime(dTime),
	totalTime(time),
	size(sizeIncrease),
	timeCounter(0.0f)
{
	if (sizeIncrease < 0)
		UE_LOG(LogTemp, Warning, TEXT("Player losing size"));
}
void UpdatePlayerSizeLatentAction::UpdateOperation(FLatentResponse& Response)
{
	if (!playerCharacter)
		Response.DoneIf(true);
	timeCounter += deltaTime;
	float dSize = size * deltaTime;
	playerCharacter->OnObjectEatten(playerCharacter->size + dSize);
	if (playerCharacter->size < 10.0f)
	{
		//Kill Player
		playerCharacter->playerHUD->OnGameOver();
		if (!playerCharacter->IsPendingKill())
			playerCharacter->Destroy();
		Response.DoneIf(true);
	}
	if (timeCounter >= totalTime)
	{
		Response.DoneIf(true);
	}
}