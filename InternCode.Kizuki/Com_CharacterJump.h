#pragma once
#include "../Component/Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //�W�����v���Ă��邩�ǂ���
	DirectX::SimpleMath::Vector3 m_Velocity{};
	float gravity = 4.0f; //�d��
	float fallTime = 0.0; //��������
	float jumpPow = 10.0f; //�W�����v��

public:
	Com_CharacterJump();
	void Update();
	void Jump();
};

//�W�����v�̍����Ȃǂ͕ʂŒ�`
//�v�����i�[��csv�ő��삵�₷���悤��