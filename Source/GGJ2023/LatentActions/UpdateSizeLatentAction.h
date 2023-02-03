#pragma 
#include <LatentActions.h>

class APlayerCharacter;
class UpdatePlayerSizeLatentAction : public FPendingLatentAction
{
public:
	UpdatePlayerSizeLatentAction(int id, APlayerCharacter* player, float deltaTime, float time, float sizeIncrease);
	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	APlayerCharacter* playerCharacter;
	float totalTime;
	float size;
	float timeCounter;
	float deltaTime;
};