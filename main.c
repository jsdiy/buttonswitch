//	ボタンスイッチの読み取り
//	『昼夜逆転』工作室	https://github.com/jsdiy
//	2022/05 - 2025/06	@jsdiy

#include <avr/io.h>
#include <util/delay.h>
#include "buttonswitch.h"

//スイッチのインデックス
typedef	enum { SwIdxA = 0, SwIdxB }	ESwIndex;

int	main(void)
{
	//初期化
	//・3回の呼び出し毎にポートを読み込む（チャタリング回避）。
	//・ポートを読み込んで5回連続で押下状態だったら長押しと判断する。
	//・どちらの値も実際の動作を見て感覚的に決める。
	BTNSW_Initialize(3, 5);

	while (1)
	{
		//スイッチ入力を監視する
		if (BTNSW_ReadSwitch())
		{
			//スイッチAの状態を取得する
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

			//スイッチBの状態を取得する
			ESwitchState swStateB = BTNSW_GetState(SwIdxB);
			if (swStateA == SwLongHold && swStateB == SwLongHold)
			{
				//ABボタン同時押し中
			}
		}

		//何らかの処理
		_delay_ms(100);		//例として
	}

	return 0;
}
