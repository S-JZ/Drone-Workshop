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
  //Initialize MPU6050
   Serial.begin(115200);
   Serial.println("Initialized MPU6050 successfully");
   // Check if the wirings are connected or not.
    while(!M.begin(MPU6050_SCALE_2000DPS,MPU6050_RANGE2G)){
    Serial.println("Check your connections again, sensor not detected!");
    delay(200);
    }

    //Calibrate my gyroscope
    M.calibrateGyro();
    
    // Set threshold value
    M.setThreshold(3);
   // Check my settings
   checker();    

}

void checker(){
  // Check Sleep Mode
  Serial.println();
  Serial.println("Sleep Mode is :");
  Serial.println(M.getSleepEnabled()?"Enabled":"Disabled");

  // Clock Source
  Serial.println("Clock Source :");
  switch M.getClockSource(){
    case MPU6050_CLOCK_SCALE_RESET:
    Serial.println("Stops the clock and reset it."); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:
    Serial.println("PLL Internal reference 8 MHz");break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ:
    Serial.println("External reference of 32.7 KHz");break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ:
    Serial.println("External reference of 19.2 MHz");break;
    case MPU6050_CLOCK_PLL_XGYRO:
    Serial.println("With reference to X axis");break;
    case MPU6050_CLOCK_PLL_YGYRO:
    Serial.println("With reference to Y axis");break;
    case MPU6050_CLOCK_PLL_ZGYRO:
    Serial.println("With reference to Z axis");break;

    // Check the offsets
    Serial.println("X offset :");
    Serial.println(M.getGyroOffsetX());
    Serial.print("\");
    Serial.println("Y offset :");
    Serial.println(M.getGyroOffsetY());
    Serial.print("\");
    Serial.println("Z offset :");
    Serial.println(M.getGyroOffsetZ());
    Serial.print("\");
    
  }

  // Check DPS
  Serial.println("Gyroscope :");
  switch M.getScale(){
    case MPU6050_SCALE_2000DPS:
    Serial.println("2000 DPS");
    break;
    case MPU6050_SCALE_1000DPS:
    Serial.println("1000 DPS");
    break;
    case MPU6050_SCALE_500DPS:
    Serial.println("500 DPS");
    break;
    case MPU6050_SCALE_250DPS:
    Serial.println("250 DPS");
    break;
  }
  Serial.print(" * Accelerometer:         ");
  switch(M.getRange())
  {
    case MPU6050_RANGE_16G: Serial.println("+/- 16 G"); break;
    case MPU6050_RANGE_8G:  Serial.println("+/- 8 G"); break;
    case MPU6050_RANGE_4G:  Serial.println("+/- 4 G"); break;
    case MPU6050_RANGE_2G:  Serial.println("+/- 2 G"); break;
  }  

  Serial.print("Accelerometer: ");
  Serial.print(M.getAccelOffsetX());Serial.print("\");
  Serial.print(M.getAccelOffsetY());Serial.print("\");
  Serial.println(M.getAccelOffsetZ());
  
  Serial.println();
  
  
}

void loop() {

  //Gyroscope Values
  Vector Raw = M.readRawGyro();
  Vector Normal =M.readNormalizeGyro();
  // Fetching Raw data
  Serial.println("Raw X Axis =");
  Serial.println(Raw.XAxis);
  Serial.println("Raw Y Axis =");
  Serial.println(Raw.YAxis);
  Serial.println("Raw Z Axis =");
  Serial.println(Raw.ZAxis);
  
  // Fetching Normalized Data
  Serial.println("Normalized X Axis =");
  Serial.println(Normal.XAxis);
  Serial.println("Normalized Y Axis =");
  Serial.println(Normal.YAxis);
  Serial.println("Normalized Z Axis =");
  Serial.println(Normal.ZAxis);

  // Accelerometer Values
  Vector rawAccel = M.readRawAccel();
  Vector normAccel = M.readNormalizeAccel();
  //Raw
  Serial.println(" Acc Raw X = ");
  Serial.println(rawAccel.XAxis);
  Serial.println(" Acc Raw Y = ");
  Serial.println(rawAccel.YAxis);
  Serial.println(" Acc Raw Z = ");
  Serial.println(rawAccel.ZAxis);
  // Normalized
  Serial.println(" Acc Normal X = ");
  Serial.println(normAccel.XAxis);
  Serial.println(" Acc Normal Y= ");
  Serial.println(normAccel.YAxis);
  Serial.println(" Acc Normal Z= ");
  Serial.println(normAccel.ZAxis);
  
  delay(100); 
}
