FreeRTOS port for STM8 micro-controller and IAR compiler

I am uploading the FREERTOS port for STM8 micorcontroller. This ports works for IAR compiler. I have tested it on STM8AF51AA and STM8AF5288 controllers.

You can use it directly on 'STM8/128-EVAL - Evaluation board' 'http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1673/PF202966'
rtosdemo application is tested on this port.

What should work?

1. Serial port

2. COM LEDs blinking [Corutines]

3. PollQ [pollQProducer and pollQconusmer tasks]



What is not implemented?

I have not yet supported the regtest functions



How to use?
1. Add 'STM8_STM8AF5288_IAR' folder under'FreeRTOSv8.0.1\FreeRTOS\Demo'
2. Add 'STM8AF5288'folder under 'FreeRTOSv8.0.1\FreeRTOS\Source\portable\IAR'
3. Open 'rtosdemo.eww' file form IAR embedded workbench for STM8
4. Add following lines to '\FreeRTOS\Source\include\portable.h' file 

	#ifdef IAR_STM8S
		#include "../portable/IAR/STM8AF5288/portmacro.h"
	#endif
   OR 

   Copy and replace 'portable.h' file in '\FreeRTOS\Source\include' folder [This is not recommened ad it can overwrite your changes to the file]



Please see if its useful. Would be happy to help if anyone wants to use the port



Thanks and Regards

Sameer S. Upasnai