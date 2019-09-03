## Description
- Triple DES **(aka 3DES, 3-DES, TDES)** is based on the DES (Data Encryption Standard) algorithm, therefore it is very easy to modify existing software to use Triple DES. It also has the advantage of proven reliability and a longer key length that eliminates many of the attacks that can be used to reduce the amount of time it takes to break **DES.**
- More info links:https://github.com/lbeatu/The-TRIPLE-DES-Algorithm-Illustrated-for-C-code
- A lot of times when you work on some project, you want to display data on computer. This can be done with USART peripheral on MCU. With USART you can connect more than just computer, you can connect with GSM modules, GPRS, bluetooth and so much more. Our discovery board supports up to 8 USART channels. In this tutorial we will use USART1 to show principle how to use USART in our project. But first, we have to initialize our pins and peripheral.
- This example runs on STM32F407xx/417xx, STM32F429xx and STM32F439xx devices on STM32 Standard Peripheral Libraries.

| U(S)ARTx  | TX  | RX | APB |                      
| :------------ |:---------------:| -----:| -----:|
| USART1      | PA9 | PA10 | 2 |
| USART2      | PA2 | PA3 | 1 |
| USART3      | PA10 | PB11 | 1 |
| USART4      | PA0 | PA1 | 1 |
| USART5      | PC12 | PD2 | 1 |
| USART6      | PC6 | PC7 | 1 |
| USART7      | PE8 | PE7 | 1 |
| USART7      | PE1 | PE0 | 1 |
#### Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: None
### USART1 uses pins
- PA9 -TX for transmitting data
- PA10 -RX for receiving data;
![](http://2.bp.blogspot.com/-oaqvBEOZy_g/VTta340i9iI/AAAAAAAAAY0/IX7GS22VwS8/s1600/stm32f4%2Bto%2Bdb9.jpg)
### LED3 & LED4 uses pins
- PG13 green led
- PG14 yellow led

so they must have enabled clock, set for alternating function and set them this alternating function.
```javascript
 GPIO_InitTypeDef    GPIO_InitStructure;
 USART_InitTypeDef   USART_InitStrutcure;
 NVIC_InitTypeDef    NVIC_InitStructure;
 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
 
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOG, ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
```
Enable LED3 AND LED4 from G ports-nopull
```javascript 
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
 
```
Enable UART TX-RX communication on PA10,PA9-Pull Up Mode
```javascript  
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 	
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    
```

Then, when you initialized pins, we have to initialize USART peripheral too
Uart configuration 115200 baudrate serial COM and Enable UART Interrupt Function of **USART1_IRQn()**

```javascript
    USART_InitStrutcure.USART_BaudRate              = 115200;
    USART_InitStrutcure.USART_WordLength            = USART_WordLength_8b;
    USART_InitStrutcure.USART_Parity                = USART_Parity_No;
    USART_InitStrutcure.USART_StopBits              = USART_StopBits_1;
    USART_InitStrutcure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    USART_InitStrutcure.USART_Mode                  = USART_Mode_Tx | USART_Mode_Rx;
    
    USART_Init(USART1, &USART_InitStrutcure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel          = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd       = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 0;
    NVIC_Init(&NVIC_InitStructure);
```
An TIMER2 ınterrupts-for Receive data for Uarts.TIM2 initialization overflow every 500ms
TIM2 by default has clock of 84MHz, Here, we must set value of prescaler and period,so update event is 0.5Hz or 500ms

```javascript
  // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) *(TIM_Period + 1))
  // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
	TIM_TimeBaseInitStruct.TIM_Prescaler = 4199;
	TIM_TimeBaseInitStruct.TIM_Period = 9999;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	 
	TIM_OCInitTypeDef        TIM_OCInitStructure;
	// TIM2 initialize20
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	// Enable TIM2 interrupt2 
   
	TIM_Cmd(TIM2, ENABLE);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
```
## Interrupt Functions
```javascript
void TIM2_IRQHandler(void)//TIM2 interrupt function
void USART1_IRQHandler(void)//USART1 interrupt function
 
``` @Keil uVision5 2.9.19
