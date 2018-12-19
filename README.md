[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
carillonPlayer
====
* arduinoで鉄琴演奏ロボット  
![result](https://github.com/chakio/carillonPlayer/blob/master/media/carillonPlayer.gif) 
## Description
音データの可視化の一つとして、鉄琴演奏ロボットを作成しました。  
自作の円弧状に並ぶ鉄琴をサーボモータとソレノイドを駆使して演奏します。  
音付きの映像は[youtube](https://www.youtube.com/watch?v=UpVMlNcHM6o&feature=em-share_video_user)に公開しています。  
製作時期 2016年10月下旬〜12月初旬
## Composition
* マイコン: arduino mega
* ソレノイド: [タカハ機工株式会社 CB1037](http://www.takaha.co.jp/SHOP/cb1037.html)×2
* サーボモータ（腕,腰）:[GWSサーボ　S03T](http://akizukidenshi.com/catalog/g/gM-01794/)×3
* MIDI_Serial変換:[類似品](https://www.switch-science.com/catalog/2492/)

## Detail
<img src="https://github.com/chakio/carillonPlayer/blob/master/media/entire.png" width="500px">  

* Hardware  

鉄琴を叩く際、重要となるのは叩く際のスナップです。  
叩いた後にすぐに鉄琴からバチを離さないと、響かなくなってしまうためです。  
制作当初、すべてのアクチュエータにサーボモータを使用することを考えていました。  
しかし、プロトタイプの中で、サーボモータでスナップを効かせることは非常に困難であることがわかり、代わりのアクチュエータとしてソレノイドを採用しました。  
ソレノイドは非常に応答性がよく、一瞬だけ鉄琴を叩くという動作に適しているためです。   
以下の画像が、腕部分に着目した画像です。 

<img src="https://github.com/chakio/carillonPlayer/blob/master/media/side.jpg" width="500px">  

腕部分は２つのパーツから構成されています。  
[１つ目](https://github.com/chakio/carillonPlayer/blob/master/model/solenoidHolder.stl)は、サーボモータにソレノイドを固定するパーツです。  
[２つ目](https://github.com/chakio/carillonPlayer/blob/master/model/stickHolder.stl)は、バチを把持するパーツです。  
これらを太めのネジで固定することで、ソレノイドの直動の力を回転に変換しています。  
また、一度下がったバチを元の位置に戻すために、輪ゴムを使用しています。  
このセットを２つ用意し、人と同じように双腕で演奏を行います。  
最後に、これらのパーツを[腰パーツ](https://github.com/chakio/carillonPlayer/blob/master/model/servoHolder.stl)に固定します。  


![result](https://github.com/chakio/carillonPlayer/blob/master/media/prototype.gif)  

上記動画は、これまで説明した腕部分を使用し制作したプロトタイプのモデルです。  
小さな動きでリズミカルに叩く姿は愛らしいのですが、腕の速度に制限があり、演奏できる曲に制限がありました。  
そこで、サーボ自身を良い物に変えるのではなく、人と同様に腰部分に自由度を追加することで、遅い腕の動きを補うことを考えました。

<img src="https://github.com/chakio/carillonPlayer/blob/master/media/front.jpg" width="500px">  

２つの腕を固定する腰パーツに、もうひとつサーボモータを格納できるよう改良しました。   
回転をスムーズにすることと、サーボモータが痛むことを避けることを目的に４つのボールキャスターで支えるにしています。  
一番下の箱には回路などが格納されています。


* Carillon

本制作で最も苦労したのは、鉄琴周りと炒っても過言ではありません。  
まず、多くの音を演奏可能とするために、鉄琴の配置をこだわりました。  
一般的な鉄琴同様に、2列にすることを考えましたが、ハードウエアをより簡素にすることを優先し、すべての音を横に並べることを採用しました。  
更に、ロボットの可動範囲を考慮すると横一直線よりも、円弧状に配置されているほうが可動範囲をより有効活用できるため。鉄琴のプレートを円弧状に並べることとしました。  
プレートが円弧状に並ぶ鉄琴は一般的には入手できないため、入手可能な鉄琴を分解し、円弧状に再配置を行いました。  

次に、プレートの固定方法が非常に重要です。  
ただ板の上に固定するだけでは、全く音が響かなくなってしまいます。  
そこで、以下の２つの工夫を施しました。  
１つ目は、プレートをリジットな状態ではなくフローティングな状態で固定するために、プレートと板の間にフェルト生地をできるだけ細く入れています。  
接地面積が大きくなると音が響かなくなってしまいます。  
２つめは、プレートの板を一枚の板ではなく、板の内側を切り抜く加工を施しました。  
これにより、振動する空気の量がが増大し、比較的大音量かつ響くように改善されました。  



* Circuit

回路については以下の写真のとおりです。

<img src="https://github.com/chakio/carillonPlayer/blob/master/media/inside.jpg" width="500px">  

<img src="https://github.com/chakio/carillonPlayer/blob/master/media/bottom.jpg" width="500px"> 

arduino、サーボモータ用とソレノイド用にそれぞれ別電源を用意しています。  
また、ソレノイドはトランジスタで制御しています。  
ユニバーサル基板に手半田で作成しています。  
（arduinoは安価な互換機を使用しています）


* Program

プログラムの方では、それぞれの音に対しいくつかの腕と腰の姿勢セットを予め割り当てておきその中で最短時間で叩くことが可能な姿勢で叩くような仕組みになっています。  
さらなる性能向上には、予めMIDIデータを読み込み、書く時間に対する最適な姿勢を計画するような最適化問題を解く枠組みが必要だと考えています。  


