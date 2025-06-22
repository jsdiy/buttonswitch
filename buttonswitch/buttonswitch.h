//	�{�^���X�C�b�`�̓ǂݎ��
//	�w����t�]�x�H�쎺	https://github.com/jsdiy
//	2022/05 - 2025/06	@jsdiy


#ifndef BUTTONSWITCH_H_
#define BUTTONSWITCH_H_


//�X�C�b�`�̌�	���K�X����������
#define BTNSW_ARRAY_SIZE	2

//�s���A�T�C��	���K�X����������
#if (1)	//ATmega328P�Ȃ�
#define BTNSW_PORT	PORTC
#define BTNSW_DDR	DDRC
#define BTNSW_PIN	PINC
#define BTNSW_A		(1 << PINC5)
#define BTNSW_B		(1 << PINC4)
//#define BTNSW_C	...
#define BTNSW_ARRAY	{ BTNSW_A, BTNSW_B }

#else	//ATtiny2313�Ȃ�
#define BTNSW_PORT	PORTD
#define BTNSW_DDR	DDRD
#define BTNSW_PIN	PIND
#define BTNSW_A		(1 << PD2)
#define BTNSW_B		(1 << PD3)
//#define BTNSW_C	...
#define BTNSW_ARRAY	{ BTNSW_A, BTNSW_B }
#endif

//�X�C�b�`�̉������
typedef	enum
{
	SwIdle,			//������Ă��Ȃ��i�ҋ@��ԁj
	SwPressed,		//�����ꂽ�u��
	SwShortHold,	//�Z�����i��莞�Ԗ����j
	SwLongHold,		//�������i��莞�Ԉȏ�o�߁j
	SwReleased		//�������u��
}
ESwitchState;

//�֐�
void	BTNSW_Initialize(uint8_t readTiming, uint8_t holdTiming);
uint8_t	BTNSW_ReadSwitch(void);
ESwitchState	BTNSW_GetState(uint8_t swIndex);	//������BTNSW_ARRAY�z��̃C���f�b�N�X

#endif	//BUTTONSWITCH_H_
