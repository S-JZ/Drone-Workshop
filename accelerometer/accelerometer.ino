#include <MPU6050.h>
#include <Wire.h>

MPU6050 M;

/* Imported the libraries
 *  Initialize MPU6050
 *  Check my sensor is connected or not
 *  Calibrate my gyroscope
 *  Threshold Value 
 *  Check my settings --- DPS, Sleep Mode, References
 *  Check offsets
 *  Raw and Normalized Readings 
 */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Initializing the MPU6050");

  //To detect the sensor
  while (!M.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Not detected, connect the wirings again!");
    delay(200);
  }
  //Calibrate my gyroscope
  M.calibrateGryro();

 // Setting threshold value
 M.setThreshold(3);
// Check my settings
 checker();
 
}


void checker(){
  //Checking if sleep Mode is enabled or not
  Serial.println();
  Serial.println("Sleep Mode is :");
  Serial.println(M.getSleepEnabled()?"Enabled":"Disabled");

 // Check clock
  Serial.println("Clock Source Check :");
  switch (M.getClockSource()){
    case MPU6050_CLOCK_KEEP_RESET:
    Serial.println("Stop the clock & reset");break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ:
    Serial.println("External Reference is 32.7 KHz");break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ:
    Serial.println("External Reference is 19 MHz");break;
    case MPU6050_CLOCK_PLL_XGYRO:
    Serial.println("PLL with reference to X axis"); break;
    case MPU6050_CLOCK_PLL_YGYRO:
    Serial.println("PLL with reference to Y axis"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:
    Serial.println("PLL with reference to Z axis"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:
    Serial.println("PLL internal reference 8Mhz"); break;
  }
 
  Serial.println("Gyroscope DPS :");
// Finding the dps
  switch (M.getScale()){
    case MPU6050_SCALE_2000DPS:
    Serial.println("2000 DPS");
    break;
    case MPU6050_SCALE_1000DPS:
    Serial.println("1000 DPS");
    break;
    case MPU6050_SCALE_500DPS:
    Serial.println("500 DPS");
    break;
    case MPU6050_SCALE_200DPS:
    Serial.println("200 DPS");
    break;
  }
  // Check the offset 
  Serial.println("Checking the gyroscope offset");
  Serial.println(M.getGyroOffsetX());
  Serial.print("\");
  Serial.println(M.getGyroOffsetY());
  Serial.print("\");
  Serial.println(M.getGyroOffsetZ()); 
  Serial.println()
  
  
}

void loop() {
  Vector Raw=M.readRawGyro();
  Vector Normal=M.readNormalizeGyro();
   // Raw Value feed
   Serial.println("Raw X Axis=");
   Serial.println(Raw.XAxis);
   Serial.println("Raw Y Axis=");
   Serial.println(Raw.YAxis);
   Serial.println("Raw Z Axis=");
   Serial.println(Raw.ZAxis);
    // Normalized Value Feed
   Serial.println("Normalized X Axis=");
   Serial.println(Normal.XAxis);
   Serial.println("Normalized Y Axis=");
   Serial.println(Normal.YAxis);
   Serial.println("Normalized Z Axis=");
   Serial.println(Normal.ZAxis);
   
  delay(1500);
}
