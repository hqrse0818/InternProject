#pragma once
#include "../Component/Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //�W�����v�t���O
	bool hipDropFlg = false; //�q�b�v�h���b�v�t���O
	DirectX::SimpleMath::Vector3 m_Velocity{}; //���x
	float gravity = 4.0f; //�d��
	float fallTime = 0.0; //��������
	float jumpPow = 0.6; //�W�����v��

public:
	Com_CharacterJump();
	void Update();
	void Jump(); //�W�����v�֐�
	void HipDrop(); //�q�b�v�h���b�v�֐�
};

//�W�����v�̍����Ȃǂ͕ʂŒ�`
//�v�����i�[��csv�ő��삵�₷���悤��