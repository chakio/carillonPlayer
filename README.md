[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
carillonPlayer
====
* arduinoで鉄琴演奏ロボット  
![result](https://github.com/chakio/carillonPlayer/blob/master/media/carillonPlayer.gif) 
## Description
音データの可視化の一つとして、鉄琴演奏ロボットを作成しました。  
自作の円弧状に並ぶ鉄琴をサーボモータとソレノイドを駆使して演奏します。
音付きの映像は[youtube](https://www.youtube.com/watch?v=UpVMlNcHM6o&feature=em-share_video_user)に公開しています。  
制作 2017年10月下旬〜12月初旬
## Composition
* マイコン: arduino mega
* ソレノイド: タカハ機工株式会社 CB1037×2
* サーボモータ（腕,腰）:GWSサーボ　S03T×3
## Detail
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9826.JPG)  
筐体はシームレスで真っ黒になるように設計しました。  
真っ黒なのに光るのがポイントです。  
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9836.JPG)  
[フロントパネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.stl)はクリアブラックの3mm厚のアクリル板と乳白色のの2mm厚のアクリル板を重ねることで、程よいLED明かりを拡散させることと、内側が透けないようにする工夫をしています。  
[dxf](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.dxf)で書き出して、レーザカッター切り出しました.  

メインの筐体の[モデル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/body.stl)を、3Dプリンタで制作しました。  
上面には、明るさ調整用のボリューム、
側面には、arduinoの書き込み用のmicroUSBの先込み口、
背面には、DC電源と音声入力用のイヤホンジャック、モード切り替え用のスイッチ用の穴が開いています。

![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9833.JPG)   
内側にはLEDアレイが並んでいます。
3Dプリンタで作成した[固定パネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/ledHolder.stl)にプラスチック
リベットを用いて固定しています。  

![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9834.JPG)   
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9835.JPG)   
回路周りはユニバーサル基板に手半田で作成しています。
