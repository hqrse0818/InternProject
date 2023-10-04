#include "Com_CharacterJump.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

Com_CharacterJump::Com_CharacterJump()
{
}

void Com_CharacterJump::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN)
	{
		Jump();
	}
}

void Com_CharacterJump::Jump()
{
    while (jumpTimer < jumpDuration)
    {
        // キャラクターを上方向に移動
        p_mObject->p_mTransform->Translate(0.0f, jumpSpeed * Time->GetDeltaTime(), 0.0f);

        // ジャンプタイマーを更新
        jumpTimer += Time->GetDeltaTime();

        // 地面の判定

        // フレームを更新
        Update();
    }
}
