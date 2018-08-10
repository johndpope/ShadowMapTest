/*
================================================================================
					 �I�u�W�F�N�g�w�������Q�[���v���O���~���O
	     Copyright (c) 2011 Human Academy Sendai. All rights reserved.
================================================================================

 �y�Ώۂn�r�z
     Microsoft WindowsXP�ȍ~

 �y�R���p�C���z
     Microsoft VisualC++ 2008

 �y�v���O�����z
	 SoundVoice.hpp
				�T�E���h�{�C�X�N���X�w�b�_�[�t�@�C��

 �y�o�[�W�����z
	 * Version    2014.03.00      2014/03/14  03:10:03

================================================================================
*/

#pragma once

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include <XAudio2.h>

//------------------------------------------------------------------------------
//	�T�E���h�{�C�X�C���^�t�F�[�X��`
//------------------------------------------------------------------------------
class ISoundVoice {
public:
	virtual ~ISoundVoice() {}
};

//------------------------------------------------------------------------------
//	�T�E���h�{�C�X�N���X��`
//------------------------------------------------------------------------------
class CSoundVoice : public ISoundVoice {
public:
	CSoundVoice(IXAudio2SourceVoice* pXASrcVoice) {}
	virtual ~CSoundVoice() { m_pXASrcVoice->DestroyVoice(); }

private:
	IXAudio2SourceVoice*   m_pXASrcVoice;
};

//------------------------------------------------------------------------------
//	NULL�T�E���h�{�C�X�N���X��`
//------------------------------------------------------------------------------
class CNullSoundVoice : public ISoundVoice {
public:
	CNullSoundVoice() {}
	virtual ~CNullSoundVoice() {}
};