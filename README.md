# モジュラー電装


# バス

バスの物理規格は，2.54mmピッチのカードエッジコネクタとする．片面15ピンずつ．

CANを用いた通信プロトコルは [WCCP](https://github.com/wasa-rockoon/WCCP)を参照．

表
1. Vpp
2. Vcc 5V
3. Vdd 3.3V
4. VBAT 3V
5. GND
6. CAN Low
7. CAN High
8. GND
9. キー
10. JTMS, SWDIO
11. JTCK, SWCLK
12. JTDI
13. JTDO, TRACESWO
14. /JNTRST
15. /RESET
裏

16 ~ 23, 25 ~ 30. テスト用プローブ 1 ~ 8, 9 ~ 14

24. キー

## Vpp, Vcc, Vdd, GND

電源モジュールから供給される．バスからのVpp供給は小電流に限る．大電流が必要なモジュールには電源モジュールまたは外部から直接供給すること．

## CAN High, CAN Low

5V CANバス, Normal CAN 1Mbps

## SWCLK, SWDIO, RST

STM32書き込み・デバッグ用


# モジュール一覧

## ベース基板

6個のモジュールを搭載できるベース基板．
カードエッジコネクタのうち1つを書き込み・デバッグ用とする．

- カードエッジコネクタ x6
- CANバスコネクタ x2
- STLink 書き込み・デバッグ用コネクタ x1
- テスト用カードエッジ

### CANバスコネクタ

ベース基板に取り付けないモジュールとの中距離接続に用いる．

1. Vpp
2. CAN Low
3. CAN High
4. GND

Vcc, Vddはモジュール側で自給する．

接続しない場合は，CAN Low と CAN High との間に終端抵抗（120 Ω）を必ず接続すること．

## Battery Power

- 5Vおよび3.3Vの電源を供給
- 各系統の電圧および電流を測定

### 接続

- 電源供給（6V~18V）：XH (1: V+, 2: GND)

### インターフェース

- 主電源スイッチ
- バックアップ電源スイッチ

### 出力パケット

#### B （Battery）

| Type | Data | Description |
| --- | --- | --- |
| P | float16 | 供給電源電圧 [V] |
| C | float16 | 5V系電圧 [V] |
| D | float16 | 3.3V系電圧 [V] |
| c | float16 | 5V系電圧 [A] |
| d | float16 | 3.3V系電流 [A] |

## Battery Power V2

- 5Vおよび3.3Vの電源を供給
- 各系統の電圧および電流を測定
- 外部に5Vまたは3.3Vの電源を供給
- バッテリー温度を測定し，ヒーターを駆動

### 接続

- 電源供給1（6V~18V）：XH (1: V+, 2: GND)
- 電源供給2（6V~18V）：XH (1: V+, 2: GND)
- ヒーター：PH (1: Heater+, 2: GND, 3: temperature)
- 外部供給出力（5V or 3.3V）：PH (1: V+, 2: GND, 3: flight pin)
- 外部電源スイッチ：PH

### インターフェース

- 5V・3.3V系電源スイッチ（外部スイッチとどちらかがONならば供給）

### 出力パケット

#### B （Battery）

| Type | Data | Description |
| --- | --- | --- |
| P | float16 | 供給電源電圧 [V] |
| C | float16 | 5V系電圧 [V] |
| D | float16 | 3.3V系電圧 [V] |
| c | float16 | 5V系電圧 [A] |
| d | float16 | 3.3V系電流 [A] |

## Comm&Log

- LoRa（ES920LR）通信
- TWELITE 通信
- Micro SD カードにログを記録

### 接続

- LoRa アンテナ：U.FL
- TWELITE アンテナ：U.FL

### インターフェース

- Micro SD カードスロット


## LoRa

- LoRa（ES920LR）通信（2ch）

### 接続

- LoRa アンテナx2：U.FL


## Igniter Driver

- 発射条件を判定しイグナイタを駆動
- 供給電圧，電流，イグナイタ抵抗値を測定

### 接続

- イグナイタ用供給（6V~12V）：XH (1: V+, 2: GND)
- イグナイタ出力：XH (1: V+, 2: GND)

### インターフェース

- 警報ブザー

## Nav

- 9軸センサ（BMX055）
- 気圧センサ（BME280）
- GNSS

### 接続

- GPS パッシブアンテナ：U.FL
- UART （外部GPS用）：PH
- I2C （拡張用）：PH


## INS

- 9軸センサ（BNO055）
- 気圧センサ（BME280）
- GNSS (NEO-M9N-00B)

### 接続

- GPS アクティブアンテナ：U.FL
- サーミスタ：PH
- UART （拡張用）：PH
- I2C （拡張用）：PH


## RCS

- 電磁バルブ制御x4
- バルブ用電源（24V）供給
- 圧力計測（1MPaG）x2
- 推力計測x2
- 温度計測

### 接続

- バルブAB：PH (1: A+, 2: A-, 3: B+, 4: B-)
- バルブCD：PH (1: C+, 2: C-, 3: D+, 4: D-)
- ロードセルX：ZH (1: Vdd, 2: GND, 3: Signal+, 4: Signal-)
- ロードセルY：ZH (1: Vdd, 2: GND, 3: Signal+, 4: Signal-)
- 圧力センサ1：ZH (1: Vcc, 2: GND, 3: Signal)
- 圧力センサ2：ZH (1: Vcc, 2: GND, 3: Signal)
- サーミスタ：ZH
