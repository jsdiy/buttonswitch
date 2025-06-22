//	�{�^���X�C�b�`�̓ǂݎ��
//	�w����t�]�x�H�쎺	https://github.com/jsdiy
//	2022/05

#include <avr/io.h>
#include "buttonswitch.h"


//�e�{�^���̏��
//bit	:7 6 5 4  :3      :2 1 0       :
//		:holdCount:prevPin:ESwitchState:
#define	BITPOS_HOLDCOUNT	4	//bit[7:4]
#define	BITPOS_PREVPIN		3	//bit[3]
#define	BITPOS_ESWSTATE		0	//bit[2:0]
//
#define	MASK_HOLDCOUNT	0x0F
#define	MASK_PREVPIN	0x01
#define	MASK_ESWSTATE	0x07

//�X�C�b�`���̔z��
static	uint8_t	swInfos[BTNSW_ARRAY_SIZE];

//����Ăяo����邲�ƂɃs����ǂނ��i�`���^�����O�΍�j
static	uint8_t	MaxCallCount, callCount;

//����Ăяo���ꂽ�璷�����Ɣ��f���邩(0-15)
static	uint8_t	MaxHoldCount;

//������
//����	readTiming:	����Ăяo����邲�ƂɃs����ǂނ��i�`���^�����O�΍�j
//		holdTiming:	����Ăяo���ꂽ�璷�����Ɣ��f���邩(0-15)
//�E�ǂ���������ȌĂяo���񐔂ł͂Ȃ��A���o�I�Ɍ��߂�l�B
void	BTNSW_Initialize(uint8_t readTiming, uint8_t holdTiming)
{
	//�|�[�g��ݒ肷��
	uint8_t pinBv = 0x00;
	uint8_t swArray[] = BTNSW_ARRAY;
	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++) { pinBv |= swArray[i]; }
	BTNSW_DDR	&= ~pinBv;	//���͕���
	BTNSW_PORT	|= pinBv;	//�v���A�b�v

	//�ϐ�������
	MaxCallCount = readTiming;	callCount = 0;
	MaxHoldCount = holdTiming;
	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++) { swInfos[i] = 0x00; }
}

//�X�C�b�`�̉�����Ԃ𔻒肷��
//�E���̊Ԋu�ŌĂяo���Ē��O�̃{�^��������ԂƔ�r���邱�ƂŌ��݂̏�Ԃ𔻒肷��B
uint8_t	BTNSW_ReadSwitch(void)
{
	if (callCount++ < MaxCallCount) { return 0; }	//false
	callCount = 0;

	uint8_t swArray[] = BTNSW_ARRAY;

	//���W�X�^��ǂݍ��ށi�����X�C�b�`�̓��͏�Ԃ��擾����j
	uint8_t	pinAllSwitch = ~BTNSW_PIN;	//�������ꂽ�X�C�b�`�̃r�b�g��'1'�A����ȊO��'0'

	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++)
	{
		uint8_t swInfo = swInfos[i];
		uint8_t distSwitch = swArray[i];
	
		//�O��̃{�^�����
		uint8_t holdCount = (swInfo >> BITPOS_HOLDCOUNT) & MASK_HOLDCOUNT;
		uint8_t	prevPin = (swInfo >> BITPOS_PREVPIN) & MASK_PREVPIN;

		//���݂̃X�C�b�`������Ԃ��擾����
		uint8_t	currentPin = (pinAllSwitch & distSwitch) ? 1 : 0;
	
		//�X�C�b�`�̉�����Ԃ��X�V����
		ESwitchState eState;
		if (prevPin == 0 && currentPin == 1)
		{
			eState = SwPressed;
		}
		else if (prevPin == 1 && currentPin == 1)
		{
			if (holdCount == MaxHoldCount)
			{
				eState = SwLongHold;
			}
			else
			{
				eState = SwShortHold;
				holdCount++;
			}
		}
		else if (prevPin == 1 && currentPin == 0)
		{
			eState = SwReleased;
			holdCount = 0;
		}
		else
		{
			eState = SwIdle;
		}
		
		//�X�C�b�`�̏����X�V����
		swInfo = (holdCount << BITPOS_HOLDCOUNT) | (currentPin << BITPOS_PREVPIN) | (eState << BITPOS_ESWSTATE);
		swInfos[i] = swInfo;
	}
	
	return 1;	//true
}

//�{�^���̉�����Ԃ��擾����
//�EBTNSW_ReadSwitch()�̌�ɌĂяo���B
ESwitchState	BTNSW_GetState(uint8_t swIndex)
{
	return (swInfos[swIndex] & MASK_ESWSTATE);
}
