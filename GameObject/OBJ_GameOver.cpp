#include "OBJ_GameOver.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;

OBJ_GameOver::OBJ_GameOver()
{
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);

	p_mSprite = new Com_Sprite();
	p_mSprite->SetTexture("asset/texture/gameover_mozi.png");
	p_mSprite->SetUpdate(true);
	AddComponent(p_mSprite);
}

OBJ_GameOver::OBJ_GameOver(const char* _name)
	: OBJ_GameOver()
{
}

void OBJ_GameOver::Init()
{
	GameObject::Init();

	mMoveVal.x = mStopPosA.x - p_mTransform->mPosition.x;
	mMoveVal.y = mStopPosA.y - p_mTransform->mPosition.y;

	mMoveVal /= fDuration;
}

void OBJ_GameOver::Update()
{
	GameObject::Update();

	if (bStart)
	{
		switch (mState)
		{
		case OBJ_GameOver::GameOverObjState::None:
			break;
		case OBJ_GameOver::GameOverObjState::Start:
			
			break;
		case OBJ_GameOver::GameOverObjState::Move1:
		{
			fCnt += Time->GetDeltaTime();
			Vector3 trans = Vector3(mMoveVal.x, mMoveVal.y, 0.0f);
			Translate(trans * Time->GetDeltaTime());

			if (fCnt > fDuration)
			{
				fCnt = 0.0f;
				SetPosition(mStopPosA.x, mStopPosA.y, 0.0f);
				mMoveVal.x = mStopPosB.x - p_mTransform->mPosition.x;
				mMoveVal.y = mStopPosB.y - p_mTransform->mPosition.y;
				mMoveVal /= fDuration;
				mState = GameOverObjState::Wait1;
			}
		}
			
			break;
		case OBJ_GameOver::GameOverObjState::Wait1:
			fCnt += Time->GetDeltaTime();
			if (fCnt > fDuration)
			{
				fCnt = 0.0f;
				mState = GameOverObjState::Move2;
			}
			break;
		case OBJ_GameOver::GameOverObjState::Move2:
		{
			fCnt += Time->GetDeltaTime();
			Vector3 trans = Vector3(mMoveVal.x, mMoveVal.y, 0.0f);
			Translate(trans * Time->GetDeltaTime());

			if (fCnt > fDuration)
			{
				fCnt = 0.0f;
				SetPosition(mStopPosB.x, mStopPosB.y, 0.0f);
				mMoveVal.x = mFinalPos.x - p_mTransform->mPosition.x;
				mMoveVal.y = mFinalPos.y - p_mTransform->mPosition.y;
				mMoveVal /= fDuration;
				mState = GameOverObjState::Wait2;
			}
		}
			
			break;
		case OBJ_GameOver::GameOverObjState::Wait2:
			fCnt += Time->GetDeltaTime();
			if (fCnt > fDuration)
			{
				fCnt = 0.0f;
				mState = GameOverObjState::Move3;
			}
			break;
		case OBJ_GameOver::GameOverObjState::Move3:
		{
			fCnt += Time->GetDeltaTime();
			Vector3 trans = Vector3(mMoveVal.x, mMoveVal.y, 0.0f);
			Translate(trans * Time->GetDeltaTime());

			if (fCnt > fDuration)
			{
				fCnt = 0.0f;
				SetPosition(mFinalPos.x, mFinalPos.y, 0.0f);
				mState = GameOverObjState::Finish;
			}
		}
			
			break;
		case OBJ_GameOver::GameOverObjState::Finish:
			break;
		default:
			break;
		}
	}
}
