# buttonswitch
スイッチ部品の押下状態を取得する（AVR/ポーリング方式）

## 概要
AVR(ATmega328P等、ATtiny2313等)のIOピンに接続したスイッチ（ボタンスイッチやスライドスイッチなど）の押下状態を取得します。  
複数ボタンに対応しています。  
ボタンスイッチの場合、
- SwIdle: ボタンが押されていない状態（ボタンスイッチとして何もされていない状態）
- SwPressed: ボタンを押した瞬間
- SwShortHold: SwPressedの後、ボタンを押し続けている状態（長押し判定されるまでの間）
- SwLongHold: SwPressedの後、ボタンを押し続け、長押し判定された状態
- SwReleased: ボタンを放した瞬間

の状態を取得できます。  
詳細はソースコードおよび、ソースコード中のコメントを見てください。

## 前提
ここで公開している成果物はATmega328Pで動作確認済みです。

## 開発環境
Windows10, Microchip Studio 7, ATmega328P, ATtiny2313
