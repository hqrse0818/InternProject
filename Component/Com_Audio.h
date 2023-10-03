#pragma once
#include <xaudio2.h>
#include <x3daudio.h>
#include "Component.h"
#pragma comment(lib, "xaudio2.lib")

class Com_Audio :
    public Component
{
private:

    // static
    static IXAudio2* s_p_mXAudio;
    static IXAudio2MasteringVoice* s_p_mMasteringVoice;
    static float s_fMasterVolume;
    // �I�[�f�B�I�^�[�Q�b�g
    static GameObject* s_p_mTarget;

    // �e�C���X�^���X�̕ϐ�
    IXAudio2SourceVoice* p_mSourceVoice{};
    BYTE* p_mSoundData{};
    X3DAUDIO_EMITTER emitter{};
    X3DAUDIO_LISTENER listener{};

    int iLength{};
    int iPlayLength{};

    // ���ۂɗ��������̃{�����[��
    float fVolume;
    // �������傫���قǉ����ł��傫��������������
    float fSoundScaleRatio = 10.0f;

    bool bBGM;
    bool bUseTarget = false;
    bool bPlayAtLocation = false;
    
public:

    // static
    static void InitMaster();
    static void UninitMaster();
    static void SetTarget(GameObject* target);

    // �e�C���X�^���X�̊֐�
    void Init();
    void Uninit();
    void Update();

    void Load(const char* _FileName);
    void Play(bool Loop = false);
    void Stop();

    void SetSoundRatio(float _val)
    {
        fSoundScaleRatio = _val;
    };

    void SetVolume(float _volume);
    void SetPlayAtLocation(bool _val);
    void SetUseTarget(bool _val)
    {
        bUseTarget = _val;
    };

    static void SetMasterVolume(float _volume);
};

