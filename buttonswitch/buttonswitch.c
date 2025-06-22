//	ボタンスイッチの読み取り
//	『昼夜逆転』工作室	https://github.com/jsdiy
//	2022/05

#include <avr/io.h>
#include "buttonswitch.h"


//各ボタンの情報
//bit	:7 6 5 4  :3      :2 1 0       :
//		:holdCount:prevPin:ESwitchState:
#define	BITPOS_HOLDCOUNT	4	//bit[7:4]
#define	BITPOS_PREVPIN		3	//bit[3]
#define	BITPOS_ESWSTATE		0	//bit[2:0]
//
#define	MASK_HOLDCOUNT	0x0F
#define	MASK_PREVPIN	0x01
#define	MASK_ESWSTATE	0x07

//スイッチ情報の配列
static	uint8_t	swInfos[BTNSW_ARRAY_SIZE];

//何回呼び出されるごとにピンを読むか（チャタリング対策）
static	uint8_t	MaxCallCount, callCount;

//何回呼び出されたら長押しと判断するか(0-15)
static	uint8_t	MaxHoldCount;

//初期化
//引数	readTiming:	何回呼び出されるごとにピンを読むか（チャタリング対策）
//		holdTiming:	何回呼び出されたら長押しと判断するか(0-15)
//・どちらも厳密な呼び出し回数ではなく、感覚的に決める値。
void	BTNSW_Initialize(uint8_t readTiming, uint8_t holdTiming)
{
	//ポートを設定する
	uint8_t pinBv = 0x00;
	uint8_t swArray[] = BTNSW_ARRAY;
	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++) { pinBv |= swArray[i]; }
	BTNSW_DDR	&= ~pinBv;	//入力方向
	BTNSW_PORT	|= pinBv;	//プルアップ

	//変数初期化
	MaxCallCount = readTiming;	callCount = 0;
	MaxHoldCount = holdTiming;
	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++) { swInfos[i] = 0x00; }
}

//スイッチの押下状態を判定する
//・一定の間隔で呼び出して直前のボタン押下状態と比較することで現在の状態を判定する。
uint8_t	BTNSW_ReadSwitch(void)
{
	if (callCount++ < MaxCallCount) { return 0; }	//false
	callCount = 0;

	uint8_t swArray[] = BTNSW_ARRAY;

	//レジスタを読み込む（複数スイッチの入力状態を取得する）
	uint8_t	pinAllSwitch = ~BTNSW_PIN;	//押下されたスイッチのビットは'1'、それ以外は'0'

	for (uint8_t i = 0 ; i < BTNSW_ARRAY_SIZE; i++)
	{
		uint8_t swInfo = swInfos[i];
		uint8_t distSwitch = swArray[i];
	
		//前回のボタン情報
		uint8_t holdCount = (swInfo >> BITPOS_HOLDCOUNT) & MASK_HOLDCOUNT;
		uint8_t	prevPin = (swInfo >> BITPOS_PREVPIN) & MASK_PREVPIN;

		//現在のスイッチ押下状態を取得する
		uint8_t	currentPin = (pinAllSwitch & distSwitch) ? 1 : 0;
	
		//スイッチの押下状態を更新する
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
		
		//スイッチの情報を更新する
		swInfo = (holdCount << BITPOS_HOLDCOUNT) | (currentPin << BITPOS_PREVPIN) | (eState << BITPOS_ESWSTATE);
		swInfos[i] = swInfo;
	}
	
	return 1;	//true
}

//ボタンの押下状態を取得する
//・BTNSW_ReadSwitch()の後に呼び出す。
ESwitchState	BTNSW_GetState(uint8_t swIndex)
{
	return (swInfos[swIndex] & MASK_ESWSTATE);
}
