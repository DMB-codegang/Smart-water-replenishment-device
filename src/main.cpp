#include <Arduino.h>

/*!
 * uno
 *
 */
#include <DFRobot_DHT.h>
#include <DFRobot_LiquidCrystal_I2C.h>

// 动态变量
volatile float mind_n_temp, mind_n_MuBiaoShiJian, mind_n_KaiGuanRongYu, mind_n_shidu;
// 函数声明
void DF_DuoXianCheng1();

// 创建对象
DFRobot_LiquidCrystal_I2C lcd1602;
DFRobot_DHT               dht22_13;


// 主程序开始
void setup() {
	Serial.begin(9600);
	dht22_13.begin(13, DHT22);
	lcd1602.begin(0x20);
	mind_n_temp = 0;
	mind_n_MuBiaoShiJian = 0;
	mind_n_KaiGuanRongYu = 0;
	lcd1602.printLine(uint32_t(2), (String("Water pump:") + String("OFF")));
}
void loop() {
	DF_DuoXianCheng1();
	if ((millis()>=mind_n_MuBiaoShiJian)) {
		if ((mind_n_shidu<70)) {
			lcd1602.clear();
			lcd1602.printLine(uint32_t(2), (String("Water pump:") + String("ON")));
			digitalWrite(7, HIGH);
			mind_n_MuBiaoShiJian = (millis() + 3000);
			while (!(millis()>=mind_n_MuBiaoShiJian)) {
				DF_DuoXianCheng1();
			}
			digitalWrite(7, LOW);
			lcd1602.printLine(uint32_t(2), (String("Water pump:") + String("OFF")));
			mind_n_MuBiaoShiJian = (millis() + 30000);
		}
	}
}


// 自定义函数
void DF_DuoXianCheng1() {
	mind_n_shidu = dht22_13.getHumidity();
	lcd1602.printLine(uint32_t(1), (String("Humidity:") + String(mind_n_shidu)));
	Serial.println(digitalRead(10));
}
