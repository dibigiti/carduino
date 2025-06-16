**Our goal**: turn the `Arduino` to s remote control car.

I think of doing it using with bluetooth. First of all we will create a `service` - `CarduinoRemoteControl` it will have two `Characteristrics`:
1. `Left_Engine`
2. `Right_Engine`
Each can be read, and written to. when the `1` value means that the engine is `on` and `0` means that it is `off`.

## Bluetooth Server
Now, this can help us - [Bluetooth arduino explained](https://wiki.seeedstudio.com/xiao_esp32s3_bluetooth/). it explains what we need to do in order to make the `arduino` a bluetooth server

### Coding Time
Let's code. it's practically coping from the website. Finally, I copied the code and it works! I downloaded the `nRF Connect` apk, which allows you to see the values sent in Bluetooth advertisements.

And it actually worked!
Now, I need to be able to set the `callback` function to when the `Characteristics` values change. Fortunately, when compiling the code, there were some compilation errors which have shown where the `BLE`  code is being saved.

// TODO: add the relative path to the arduino BLE library. There, in the `BLECharacteristics.h` file we found the following function:
![[Pasted image 20250613001341.png]]
We can see the `setCallbacks` which receives a `BLECharacteristicCallbacks` pointer. Fine with me! let's find this object!

After creating a sub-class of `BLECharacteristicCallbacks` named `EngineCallbacks` and creating the `c'tor, d'tor` and `onWrite` function. and then sending a pointer to the `setCallbacks` function. I was able to see the function being called when I sent a `write` operation from the `nRF Connect` apk!
![[Pasted image 20250613010301.png]]
So now, I just need to distinguish between the `Right_Engine` and `Left_Engine` and walla! we have it!
And finally! we were able to distinguish between the two different commands!
![[Pasted image 20250613012007.png]]
![[Pasted image 20250613011952.png]]
I must add a `descriptor` to the `Characteristics`. But that can wait to tomorrow... Let's start and stop the engines depending on the `Characteristic` value.  
Very Nice it works! let's save in `gitlab`
![[Pasted image 20250613012041.png]]

## Actuall engines
Now, we need to open the `pinout` of our `xiao arduino`
Thankfully, the `libreoffice` remembered where it was downloaded. I will add here too
![[XIAO_ESP32S3_Sense_Pinout.xlsx]]

Now, I connected my engines to the second and third pins:
![[Pasted image 20250613012550.png]]
as they supply direct power, because of that, i'll need to power these pins when sending the bluetooth commands.

First, declare your variables:
![[Pasted image 20250613012849.png]]
Then, in the `setup` function, declare these pins as outputs:
![[Pasted image 20250613013017.png]]
And finally, write the code the processes the bluetooth request
![[Pasted image 20250613013727.png]]
## Analog Control
Today I learned I can control the power of the engines by addressing them as `analog` pins. Which means I can "send" them a value between 0-255 and the power levels of the engine will be according to the power level. 
![[Pasted image 20250616171759.png]]
This is a test i've done which shows this!
Now, I know it's not secure - but, I want to create a mechanism that receives the power level for every engine and just changes the power to the engine accordingly. This was actually very easy to implement. 
![[Pasted image 20250616172742.png]]
![[Pasted image 20250616172730.png]]
