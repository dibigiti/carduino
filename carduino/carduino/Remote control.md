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

