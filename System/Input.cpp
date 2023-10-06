#include "Input.h"
#include "../main.h"
#include <iostream>

using namespace std;

KEYSTATE Input::mKeyStateList[]{};
KEYSTATE Input::mKeyStateBufList[]{};
bool Input::InputActive = true;
bool Input::IsSetCursorCenter = false;
DirectX::SimpleMath::Vector2 Input::MousePoint = { 0, 0 };
DirectX::SimpleMath::Vector2 Input::LastMousePoint = { 0, 0 };
DirectX::SimpleMath::Vector2 Input::NormalizedMouseMove = { 0, 0 };
DirectX::SimpleMath::Vector2 Input::ScreenCenter = { 0, 0 };
DirectX::SimpleMath::Vector2 Input::MouseSub = { 0, 0 };
float Input::MouseWheel = 0.0f;
HWND Input::mhWnd = nullptr;
POINT Input::Cursor = { 0, 0 };

void Input::Init()
{
    // �o�t�̏�����
    for (int i = 0; i < KEY_TYPENUM; i++)
    {
        mKeyStateList[i] = KEYSTATE::KEY_WHILE_UP;
        mKeyStateBufList[i] = KEYSTATE::KEY_WHILE_UP;
    }
    // �X�N���[����̃E�C���h�E�̈�̍��W���擾
    RECT winRect;
    GetWindowRect(mhWnd, &winRect);

    // �E�B���h�E�̒��S�ʒu��ݒ�
    POINT mousePos{};
    mousePos.x = winRect.left + (winRect.right - winRect.left) / 2;
    mousePos.y = winRect.top + (winRect.bottom - winRect.top) / 2;

    SetCursorPos(mousePos.x, mousePos.y);
    ScreenCenter.x = (float)mousePos.x;
    ScreenCenter.y = (float)mousePos.y;
    SetMousePoint((float)mousePos.x, (float)mousePos.y);
}

void Input::Update()
{
    GetCursorPos(&Cursor);

    MouseSub.x = Cursor.x - ScreenCenter.x;
    MouseSub.y = Cursor.y - ScreenCenter.y;
    UpdateKeyState();
    if (LastMousePoint.x == MousePoint.x)
    {
        NormalizedMouseMove.x = 0;
    }
    else if (LastMousePoint.x < MousePoint.x)
    {
        NormalizedMouseMove.x = 1;
    }
    else
    {
        NormalizedMouseMove.x = -1;
    }

    if (LastMousePoint.y == MousePoint.y)
    {
        NormalizedMouseMove.y = 0;
    }
    else if (LastMousePoint.y < MousePoint.y)
    {
        NormalizedMouseMove.y = -1;
    }
    else
    {
        NormalizedMouseMove.y = 1;
    }
}

void Input::RefreshMouse()
{
    if (IsSetCursorCenter)
    {
        // �J�[�\���𒆐S�ɂ���
        // ���j���[��J�[�\��������Ȃ����Ɏg��
        SetCursorPosition(ScreenCenter);
    }
    MouseWheel = 0.0f;
    NormalizedMouseMove = { 0, 0 };
    LastMousePoint = MousePoint;
}

KEYSTATE Input::GetKeyState(int _Key)
{
    if (InputActive == false)
    {
        return KEYSTATE::KEY_NONE;
    }
    return mKeyStateList[_Key];
}

void Input::SetKeyDownState(unsigned int _KeyCode)
{
    mKeyStateBufList[_KeyCode] = KEYSTATE::KEY_DOWN;
}

void Input::SetKeyUpState(unsigned int _KeyCode)
{
    mKeyStateBufList[_KeyCode] = KEYSTATE::KEY_UP;
}

void Input::SetMousePoint(unsigned int Param)
{
    int x = Param & 0x0000ffff;
    int y = (Param & 0xffff0000) >> 16;

    MousePoint = DirectX::SimpleMath::Vector2((float)x, (float)y);
}

void Input::SetMousePoint(float _x, float _y)
{
    MousePoint.x = _x;
    MousePoint.y = _y;
}

DirectX::SimpleMath::Vector2 Input::GetMouseMove()
{
    DirectX::SimpleMath::Vector2 move;
    move.x = MousePoint.x - LastMousePoint.x;
    move.y = MousePoint.y - LastMousePoint.y;

    return move;
}

void Input::SetCursorPosition(DirectX::SimpleMath::Vector2 Point)
{
    SetCursorPos((int)Point.x, (int)Point.y);
}

void Input::SetCursorPointCenter()
{
    // �X�N���[����̃E�C���h�E�̈�̍��W���擾
    RECT winRect;
    GetWindowRect(mhWnd, &winRect);

    // �E�C���h�E�̒��S�ʒu���v�Z
    POINT mousePos{};
    mousePos.x = winRect.left + (winRect.right - winRect.left) / 2;
    mousePos.y = winRect.top + (winRect.bottom - winRect.top) / 2;

    DirectX::SimpleMath::Vector2 mouse;
    mouse.x = (float)mousePos.x;
    mouse.y = (float)mousePos.y;

    // �}�E�X�J�[�\�����E�C���h�E�̒��S�Ɉړ�������
    SetCursorPos(mousePos.x, mousePos.y);

    DirectX::SimpleMath::Vector2 Gap = MousePoint - mouse;
    LastMousePoint.x -= Gap.x;
    LastMousePoint.y -= Gap.y;
    ScreenToClient(mhWnd, &mousePos);// �X�N���[�����W���N���C�A���g���W�ɕϊ�
    MousePoint = mouse;// ����Z�b�g�����}�E�X�ʒu�������o�[�ϐ��ɕۑ�
}

void Input::SetMouseWheel(float _value)
{
    MouseWheel = _value;
}

void Input::SetEnable()
{
    InputActive = true;
}

void Input::SetDisable()
{
    InputActive = false;
}

void Input::UpdateKeyState()
{
    // �L�[���̍X�V
    for (int i = 0; i < KEY_TYPENUM; i++)
    {
        // �o�b�t�@���������
        if (mKeyStateBufList[i] == KEYSTATE::KEY_DOWN)
        {
            switch (mKeyStateList[i])
            {
            case KEYSTATE::KEY_DOWN:
                // ���������Ă���
                mKeyStateList[i] = KEYSTATE::KEY_WHILE_DOWN;
                break;

            case KEYSTATE::KEY_WHILE_DOWN:
                // ���������Ă���
                mKeyStateList[i] = KEYSTATE::KEY_WHILE_DOWN;
                break;

            case KEYSTATE::KEY_UP:
                // �������u��
                mKeyStateList[i] = KEYSTATE::KEY_DOWN;
                break;

            case KEYSTATE::KEY_WHILE_UP:
                // �������u��
                mKeyStateList[i] = KEYSTATE::KEY_DOWN;
                break;
            }
        }
        else if (mKeyStateBufList[i] == KEYSTATE::KEY_UP)
        {
            switch (mKeyStateList[i])
            {
            case KEYSTATE::KEY_DOWN:
                // �������u��
                mKeyStateList[i] = KEYSTATE::KEY_UP;
                break;

            case KEYSTATE::KEY_WHILE_DOWN:
                // �������u��
                mKeyStateList[i] = KEYSTATE::KEY_UP;
                break;

            case KEYSTATE::KEY_UP:
                // ���������Ă�
                mKeyStateList[i] = KEYSTATE::KEY_WHILE_UP;
                break;

            case KEYSTATE::KEY_WHILE_UP:
                // ���������Ă�
                mKeyStateList[i] = KEYSTATE::KEY_WHILE_UP;
                break;
            }
        }

    }
}

// �R���g���[���[
XINPUT_STATE Controller_Input::GamePad[];
XINPUT_STATE Controller_Input::LastGamePad[];
UINT Controller_Input::TriggerThreshould = 10;
SHORT Controller_Input::LeftStickDead = 5000;
SHORT Controller_Input::RightStickDead = 5000;

void Controller_Input::UpdateCurrentController()
{
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        // �O������X�V
        LastGamePad[i] = GamePad[i];
        // ���݂̓��͏�Ԃ��擾
        DWORD dResult = XInputGetState(i, &GamePad[i]);
        if (dResult == ERROR_SUCCESS)
        {
            
        }
    }
}

KEYSTATE Controller_Input::GetButton(unsigned int index, UINT _State)
{
    if (GamePad[index].Gamepad.wButtons & _State)
    {
        if (LastGamePad[index].Gamepad.wButtons & _State)
        {
            return KEYSTATE::KEY_WHILE_DOWN;
        }
        return KEYSTATE::KEY_DOWN;
    }
    else
    {
        if (LastGamePad[index].Gamepad.wButtons & _State)
        {
            return KEYSTATE::KEY_UP;
        }
        return KEYSTATE::KEY_WHILE_UP;
    }
   
    return KEYSTATE::KEY_NONE;
}

KEYSTATE Controller_Input::GetRightTriggerSimple(unsigned int index)
{
    if (GamePad[index].Gamepad.bRightTrigger > TriggerThreshould)
    {
        if (LastGamePad[index].Gamepad.bRightTrigger > TriggerThreshould)
        {
            return KEYSTATE::KEY_WHILE_DOWN;
        }
        return KEYSTATE::KEY_DOWN;
    }
    else
    {
        if (LastGamePad[index].Gamepad.bRightTrigger > TriggerThreshould)
        {
            return KEYSTATE::KEY_UP;
        }
        return KEYSTATE::KEY_WHILE_UP;
    }

    return KEYSTATE::KEY_NONE;
}

KEYSTATE Controller_Input::GetLeftTriggerSimple(unsigned int index)
{
    if (GamePad[index].Gamepad.bLeftTrigger > TriggerThreshould)
    {
        if (LastGamePad[index].Gamepad.bLeftTrigger > TriggerThreshould)
        {
            return KEYSTATE::KEY_WHILE_DOWN;
        }
        return KEYSTATE::KEY_DOWN;
    }
    else
    {
        if (LastGamePad[index].Gamepad.bLeftTrigger > TriggerThreshould)
        {
            return KEYSTATE::KEY_UP;
        }
        return KEYSTATE::KEY_WHILE_UP;
    }

    return KEYSTATE::KEY_NONE;
}

float Controller_Input::GetRightTriggerValue(unsigned int index)
{
    float Value = GamePad[index].Gamepad.bRightTrigger;

    return Value;
}

float Controller_Input::GetLeftTriggerValue(unsigned int index)
{
    float Value = GamePad[index].Gamepad.bLeftTrigger;
    return Value;
}

DirectX::SimpleMath::Vector2 Controller_Input::GetLeftStick(unsigned int index)
{
    DirectX::SimpleMath::Vector2 Value;
    Value.x = GamePad[index].Gamepad.sThumbLX;
    Value.y = GamePad[index].Gamepad.sThumbLY;

    if (Value.x > LeftStickDead || Value.x < -LeftStickDead)
    {
        Value.x /= 32768;
    }
    else
    {
        Value.x = 0;
    }
    if (Value.y > LeftStickDead || Value.y < -LeftStickDead)
    {
        Value.y /= 32768;
    }
    else
    {
        Value.y = 0;
    }

    return Value;
}

DirectX::SimpleMath::Vector2 Controller_Input::GetRightStick(unsigned int index)
{
    DirectX::SimpleMath::Vector2 Value;
    Value.x = GamePad[index].Gamepad.sThumbRX;
    Value.y = GamePad[index].Gamepad.sThumbRY;

    if (Value.x > RightStickDead || Value.x < -RightStickDead)
    {
        Value.x /= 32768;
    }
    else
    {
        Value.x = 0;
    }
    if (Value.y > RightStickDead || Value.y < -RightStickDead)
    {
        Value.y /= 32768;
    }
    else
    {
        Value.y = 0;
    }

    return Value;
}

bool Controller_Input::GetIsGamePadConnect(unsigned int index)
{
    XINPUT_STATE gp;

    DWORD dResult = XInputGetState(index, &gp);
    if (dResult == ERROR_SUCCESS)
    {
        return true;
    }

    return false;
}

void Controller_Input::ControllerInit()
{
    //XInputEnable(TRUE);
}

void Controller_Input::ControllerUninit()
{
    //XInputEnable(FALSE);
}
