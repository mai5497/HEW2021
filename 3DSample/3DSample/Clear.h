#ifndef __CLEAR_H__
#define __CLEAR_H__

//================== �C���N���[�h�� ==================
#include "Scene.h"

//================== �萔��` ==================
enum SCENESTATE
{
	NEXTSTAGE = 0,
	GO_SELECT
};


//================== �v���g�^�C�v�錾 ==================
void	InitClear();	// ������
void	UninitClear();	// �I��
int		UpdateClear();	// �X�V
void	DrawClear();	// �`��



#endif