//	�{�^���X�C�b�`�̓ǂݎ��
//	�w����t�]�x�H�쎺	https://github.com/jsdiy
//	2022/05 - 2025/06	@jsdiy

#include <avr/io.h>
#include <util/delay.h>
#include "buttonswitch.h"

//�X�C�b�`�̃C���f�b�N�X
typedef	enum { SwIdxA = 0, SwIdxB }	ESwIndex;

int	main(void)
{
	//������
	//�E3��̌Ăяo�����Ƀ|�[�g��ǂݍ��ށi�`���^�����O����j�B
	//�E�|�[�g��ǂݍ����5��A���ŉ�����Ԃ������璷�����Ɣ��f����B
	//�E�ǂ���̒l�����ۂ̓�������Ċ��o�I�Ɍ��߂�B
	BTNSW_Initialize(3, 5);

	while (1)
	{
		//�X�C�b�`���͂��Ď�����
		if (BTNSW_ReadSwitch())
		{
			//�X�C�b�`A�̏�Ԃ��擾����
			ESwitchState swStateA = BTNSW_GetState(SwIdxA);
			switch (swStateA)
			{
			case SwIdle:		LCD_PutText("Idle");		break;
			case SwPressed:		LCD_PutText("Pressed");		break;
			case SwShortHold:	LCD_PutText("ShortHold");	break;
			case SwLongHold:	LCD_PutText("LongHold");	break;
			case SwReleased:	LCD_PutText("Released");	break;
			default:	break;
			}

			//�X�C�b�`B�̏�Ԃ��擾����
			ESwitchState swStateB = BTNSW_GetState(SwIdxB);
			if (swStateA == SwLongHold && swStateB == SwLongHold)
			{
				//AB�{�^������������
			}
		}

		//���炩�̏���
		_delay_ms(100);		//��Ƃ���
	}

	return 0;
}
