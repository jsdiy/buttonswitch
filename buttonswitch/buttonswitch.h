//	ボタンスイッチの読み取り
//	『昼夜逆転』工作室	https://github.com/jsdiy
//	2022/05 - 2025/06	@jsdiy


#ifndef BUTTONSWITCH_H_
#define BUTTONSWITCH_H_


//スイッチの個数	※適宜書き換える
#define BTNSW_ARRAY_SIZE	2

//ピンアサイン	※適宜書き換える
#if (1)	//ATmega328Pなど
#define BTNSW_PORT	PORTC
#define BTNSW_DDR	DDRC
#define BTNSW_PIN	PINC
#define BTNSW_A		(1 << PINC5)
#define BTNSW_B		(1 << PINC4)
//#define BTNSW_C	...
#define BTNSW_ARRAY	{ BTNSW_A, BTNSW_B }

#else	//ATtiny2313など
#define BTNSW_PORT	PORTD
#define BTNSW_DDR	DDRD
#define BTNSW_PIN	PIND
#define BTNSW_A		(1 << PD2)
#define BTNSW_B		(1 << PD3)
//#define BTNSW_C	...
#define BTNSW_ARRAY	{ BTNSW_A, BTNSW_B }
#endif

//スイッチの押下状態
typedef	enum
{
	SwIdle,			//押されていない（待機状態）
	SwPressed,		//押された瞬間
	SwShortHold,	//短押し（一定時間未満）
	SwLongHold,		//長押し（一定時間以上経過）
	SwReleased		//放した瞬間
}
ESwitchState;

//関数
void	BTNSW_Initialize(uint8_t readTiming, uint8_t holdTiming);
uint8_t	BTNSW_ReadSwitch(void);
ESwitchState	BTNSW_GetState(uint8_t swIndex);	//引数はBTNSW_ARRAY配列のインデックス

#endif	//BUTTONSWITCH_H_
