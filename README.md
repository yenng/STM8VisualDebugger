Developed STM32F103C8T6 By using CoIDE
======================================

##Problem 
>In the CoIDE V1.7.8 version, I have faced the problem which is the default linker-script can't be changed. It is due to some bug in CoIDE that doesn't update properly the changes that was made to the selection of linker-script. Now, I have a solution to solve this problem. To overcome this problem need to follow 2 step:

1. Close The CoIDE. Note: If you still open the CoIDE, However you change the linker-script that is always set by defualt.

2. Open .coproj file,
   1. The "UseMemoryLayout" value must be set to 0.
   2. The "nostartfiles" value must be set to 0.
   3. The "LocateLinkFile path" msut be set to the path to the linker-script you want.

The image was shown in below.
![Alt text](https://github.com/Twinkle0613/BlinkLED_CoIDE/blob/master/Image/coproj.png "blink.coproj")

##STM32F10x standard peripheral library

**stm32f10x_stdperiph_lib** has to provide the all of the periheral driver for **STM32F10X** to make users to easily configure the periherals. I will show the way to configure the periheral by using **stm32f10x_stdperiph_lib**.
     
 Step 1 :
      Download the **stm32f10x_stdperiph_lib**.
      
 Step 2 :
      Included the driver ( .h file) you want into the **Project** bar of CoIDE.
      
 Step 3 :
      View->Configuration->Compile
      Add the **USE_STDPERIPH_DRIVER** into 'Defined Symbols'
      

##Auto Compile Before Download and Debugging 

>By default, the CoIDE debugger will force download or debugging no matter there is any change or not. This can slow down the debugging process when the program is big. Also it can decrease the lifetime of the Flash Momory. All these are not desirable.

To disable auto download:
   view->configuration->download: disable 'auto download before download'
   
To disable auto debugging:
   view->configuration->user: disable 'auto download before debugging'



