#include "main.h"
int i,j;
char name[NUM+1] = {'\0'}; 

/* Initial Permutation tablosu */
static char IP[] = {
    58, 50, 42, 34, 26, 18, 10,  2, 
    60, 52, 44, 36, 28, 20, 12,  4, 
    62, 54, 46, 38, 30, 22, 14,  6, 
    64, 56, 48, 40, 32, 24, 16,  8, 
    57, 49, 41, 33, 25, 17,  9,  1, 
    59, 51, 43, 35, 27, 19, 11,  3, 
    61, 53, 45, 37, 29, 21, 13,  5, 
    63, 55, 47, 39, 31, 23, 15,  7
};

/* Inverse Initial Permutation tablosu */
static char PI[] = {
    40,  8, 48, 16, 56, 24, 64, 32, 
    39,  7, 47, 15, 55, 23, 63, 31, 
    38,  6, 46, 14, 54, 22, 62, 30, 
    37,  5, 45, 13, 53, 21, 61, 29, 
    36,  4, 44, 12, 52, 20, 60, 28, 
    35,  3, 43, 11, 51, 19, 59, 27, 
    34,  2, 42, 10, 50, 18, 58, 26, 
    33,  1, 41,  9, 49, 17, 57, 25
};

/*Expansion tablosu */
static char E[] = {
    32,  1,  2,  3,  4,  5,  
     4,  5,  6,  7,  8,  9,  
     8,  9, 10, 11, 12, 13, 
    12, 13, 14, 15, 16, 17, 
    16, 17, 18, 19, 20, 21, 
    20, 21, 22, 23, 24, 25, 
    24, 25, 26, 27, 28, 29, 
    28, 29, 30, 31, 32,  1
};

/* Post S-Box permutation */
static char P[] = {
    16,  7, 20, 21, 
    29, 12, 28, 17, 
     1, 15, 23, 26, 
     5, 18, 31, 10, 
     2,  8, 24, 14, 
    32, 27,  3,  9, 
    19, 13, 30,  6, 
    22, 11,  4, 25
};

/* The S-Box tablosu */
static char S[8][64] = {{
    /* S1 */
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,  
     0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,  
     4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0, 
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
},{
    /* S2 */
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,  
     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,  
     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15, 
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
},{
    /* S3 */
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,  
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,  
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
     1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
},{
    /* S4 */
     7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,  
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,  
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
},{
    /* S5 */
     2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9, 
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6, 
     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14, 
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
},{
    /* S6 */
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
     9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
     4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
},{
    /* S7 */
     4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
     1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
     6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
},{
    /* S8 */
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
     1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
     7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
     2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
}};

/* Permuted Choice 1 tablosu */
static char PC1[] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

/* Permuted Choice 2 tablosu */
static char PC2[] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

/* Iteration Shift Array */
static char iteration_shift[] = {
 /* 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16 */
    1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1
};

uint64_t des(uint64_t input, uint64_t key , char mode) {
      
    int i, j;
    
    /* 8 bit */
    char satir, sutun;
    
    /* 28 bits */
    uint32_t C                  = 0;
    uint32_t D                  = 0;
    
    /* 32 bit */
    uint32_t L                  = 0;
    uint32_t R                  = 0;
    uint32_t s_output           = 0;
    uint32_t f_function_res     = 0;
    uint32_t temp               = 0;
    
    /* 48 bit */
    uint64_t sub_key[16]        = {0};
    uint64_t s_input            = 0;
    
    /* 56 bit */
    uint64_t permuted_choice_1  = 0;
    uint64_t permuted_choice_2  = 0;
    
    /* 64 bit */
    uint64_t init_perm_res      = 0;
    uint64_t inv_init_perm_res  = 0;
    uint64_t pre_output         = 0;
    
    /* initial permutation */
    for (i = 0; i < 64; i++) {
       
        init_perm_res <<= 1;//girilen degeri 1 bit yana kaydirdim.
        init_perm_res |= (input >> (64-IP[i])) & LB64; //Initial Permutation tablosunda bit kaydirma yapip or kapisina sokup 
        //|=islem ile tekrar or kapisina girdi. XOR için
    }

    L = (uint32_t) (init_perm_res >> 32) & L64_MASK;// karistirdik ve 64 biti 32 bit 32 bit ayirdik.
     
    R = (uint32_t) init_perm_res & L64_MASK;  // sag taraf durcak.
     
    /* initial key schedule calculation */
    for (i = 0; i < 56; i++) {
        
        permuted_choice_1 <<= 1;//
        permuted_choice_1 |= (key >> (64-PC1[i])) & LB64;//64 bitten 56 bite anahtari düsürüp XOR yaptik.
		
    }
    
    C = (uint32_t) ((permuted_choice_1 >> 28) & 0x000000000fffffff);//karisan tablodaki bitler 28 satir saga kaydi.
    D = (uint32_t) (permuted_choice_1 & 0x000000000fffffff);//ve xor yaptik.
    

    /* Calculation of the 16 keys */
    for (i = 0; i< 16; i++) 
		{
        /* key schedule */
        // shifting Ci and Di
        for (j = 0; j < iteration_shift[i]; j++) 
				{ //shift tablosundaki index kadar döndürüp bit kaydirip XOR yaptik.
            C = 0x0fffffff & (C << 1) | 0x00000001 & (C >> 27);
            D = 0x0fffffff & (D << 1) | 0x00000001 & (D >> 27);            
        }
    
        /*burasi da, bir üstte üretilen 56 bitlik shifted key içinden 48 bitlik anahtar üretimi içindir. 
		Aslinda burada hem sikistirma hem de karistirma (permutasyon) yapilmis olur. 
		Örnegin, key’in ilk biti 14. sirayla degistirilir. Ikinci biti 17.sirayla, gibi..*/
        permuted_choice_2 = 0;
        permuted_choice_2 = (((uint64_t) C) << 28) | (uint64_t) D ;//karisan tablodaki bitler 28 satir saga kaydi.
       
        sub_key[i] = 0;
        //48 biti 56 bite cikardik.(sikistirma)
        for (j = 0; j < 48; j++) {
            sub_key[i] <<= 1;//32+32
            sub_key[i] |= (permuted_choice_2 >> (56-PC2[j])) & LB64;//anahtarin son hali 64 bit oldu.
        }
        
    }
     
    //16 kere döndürüp 
    for (i = 0; i < 16; i++) {
        
      
        s_input = 0;
        
        for (j = 0; j< 48; j++) {
            
            s_input <<= 1;
            s_input |= (uint64_t) ((R >> (32-E[j])) & LB32);// karistirdigimiz girilen degeri 32 bit kaydirip xor a soktuk.
            
        }
        	 
        /* 
        Burada, 48 bitlik genisletilmis düz text (expanded RPT of 48 bit) ile 48 bitlik anahtar 
		(compressed key of 48 bit) arasinda bitwise XOR islemi yapiliyor. Sonuç olarak yine 48 bitlik bir 
		metin ortaya çikacaktir.
         */
       if (mode == 'd') {
            // decryption
            s_input = s_input ^ sub_key[15-i]; //sifreyi çözmek için
            
        } else {
            // encryption           
            s_input = s_input ^ sub_key[i]; //karistirilan anahtar ve key son halimizi aldi.
        }
        
        /* S-Box tablosu */
       /* Bir önceki islemle XOR’lanmis metin (XORed RPT) ( text ile keyin birlestirilmesi) S box’a verilir. 
	   Burada metin (48 bit), her biri 6 bitten olusan 8 bloga bölünür. Her blok için ayri bir Sbox tablosu bulunur. 
	   Bu sebeple de asagida 8 adet Sbox tablosu göreceksiniz. Sbox’lar 16 sütun, 4 satirdan olusur. 0 ile 15 arasinda deger
	    alir. Ve her SBox 4 bitlik çikis verir. Bütün SBox’larin görevi bittiginde sonuç olarak (4*8) 32 bit dönecektir. 
		(Sbox RPT) Bu 6 bitlik verinin 1. ve 6. verisi satir, 2.3.4.5 bitleri ise Sbox üzerindeki sütünlari gösterir. 
		Bunlarin kesistigi nokta da dönüs degerini olusturacaktir. Böylece her sbox’in 4 bitlik çikisi olacaktir.*/
	
        for (j = 0; j < 8; j++) 
				{          
            satir = (char) ((s_input & (0x0000840000000000 >> 6*j)) >> 42-6*j);
            satir = (satir >> 4) | satir & 0x01;
            
            sutun = (char) ((s_input & (0x0000780000000000 >> 6*j)) >> 43-6*j);
            
            s_output <<= 4;
            s_output |= (uint32_t) (S[j][16*satir + sutun] & 0x0f);            
        }        
        f_function_res = 0;
        
        for (j = 0; j < 32; j++) {            
            f_function_res <<= 1;
            f_function_res |= (s_output >> (32 - P[j])) & LB32;
            
        }        
        temp = R;
        R = L ^ f_function_res;
        L = temp;       
    }    
    pre_output = (((uint64_t) R) << 32) | (uint64_t) L;
        
    /* inverse initial permutation */
    for (i = 0; i < 64; i++) {
        
        inv_init_perm_res <<= 1;
        inv_init_perm_res |= (pre_output >> (64-PI[i])) & LB64;        
    }
   
    return inv_init_perm_res;    
}

static void USART_SendString(USART_TypeDef* USARTx, char* s);
char giris[256];
int countergiris=0;
int receviekey=0;
int sayici=0;
char out[250]="";
void USART1_IRQHandler(void)
{		
		
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{		
				TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
				char kelime=USART_ReceiveData(USART1);				
				GPIO_SetBits(GPIOG, GPIO_Pin_13);
			
			if( (kelime != '\n') && (sayici < Max_Strlen) ) // kelime degiskenini karakter sayisi boyunca tara.
{			
				giris[sayici]=kelime; // Ekrana girilmis olan kelimeyi alinanString degiskenine ata.
				sayici++; // sayiciyi 1 arttir.				
			}
			else // kelime degiskenindeki karakter bittiyse.
			{
				giris[sayici]='\0'; // alinanString degerini sifirla.
				sayici=0;
				receviekey=1;
				USART_SendString(USART1,giris);// alinanString degiskenini ekrana yazdir.
				TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
				USART_ITConfig(USART1, USART_IT_RXNE,DISABLE);
			}
		}
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		GPIO_ResetBits(GPIOG, GPIO_Pin_13);
		
}

void TIM2_IRQHandler()
	{
	    // Checks whether the TIM2 interrupt has occurred or not

	    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	    {		 GPIO_ToggleBits(GPIOG, GPIO_Pin_13);
				
					 USART_ITConfig(USART1, USART_IT_RXNE,DISABLE);
	        // Toggle orange LED (GPIO13)
	      
	        // Clears the TIM2 interrupt pending bit
	         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
					USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	    }
	}

int main(void)
{		
	  GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStrutcure;
    NVIC_InitTypeDef    NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
 
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
		GPIO_SetBits(GPIOG, GPIO_Pin_14);
		USART_SendString(USART1, "\nLutfen deger giriniz:(Ex:0123456789ABCEDF)\r\n");
		
	  TIM_TimeBaseInitStruct.TIM_Prescaler = 4199;
	  TIM_TimeBaseInitStruct.TIM_Period = 9999;
	  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	 
		TIM_OCInitTypeDef        TIM_OCInitStructure;
	    // TIM2 initialize20
	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	    // Enable TIM2 interrupt2 
	    // Start TIM2
		TIM_Cmd(TIM2, ENABLE);
	  NVIC_InitTypeDef NVIC_InitStruct;
	  NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStruct);
			
		uint64_t girilen=0;//0x9474B8E8C73BCA7D;	
		uint64_t key[3] ={0x9474B8E8C73BCA7D, 0x9474B8E8C73BCA7C, 0x9474B8E8C73BC97D};
		uint64_t sonuc=0;
		int i=0;	
		char out[128]="";
		while(1)
		{	
			if(receviekey==1)
				{
						GPIO_SetBits(GPIOG, GPIO_Pin_14);				
						for(i=0;i<16;i++)
						{
							girilen<<=4;
						
							if(giris[i]<':')
								girilen|=giris[i]-'0';
							else
								girilen|=giris[i]-'7';	
						}
				sprintf (out,"\nGirilen Anahtar)x8: %llx", girilen);//hex kod seklinde yazdirma
				USART_SendString(USART1, out);
				//DES sifreleme
				sonuc = des(girilen, key[0],'e');
				sprintf (out,"\nDES sifre Cozumlemesi(Ecrypt)x: %llx", sonuc);//hex kod seklinde yazdirma
				USART_SendString(USART1, out);
				
				sonuc = des(sonuc, key[1],'d');
				//sprintf (out,"\nDES sifre Cozumlemesi(Decrypt)x16: 		%llx", sonuc);//hex kod seklinde yazdirma
			//	USART_SendString(USART1, out);
				//3-DES sifreleme
				sonuc = des(sonuc, key[2],'e');
				sprintf (out,"\nTriple-DES sifre Cozumlemesi(Ecrypt): %llx", sonuc);//hex kod seklinde yazdirma
				USART_SendString(USART1, out);
						
				//3DES Decrypt
				
				sprintf (out,"\n 3-DES Decrypt\n");//hex kod seklinde yazdirma
				USART_SendString(USART1, out);						
				
				sonuc = des(sonuc, key[2],'d');
				sprintf (out,"\nDES sifre Cozumlemesi(Decrypt)x: %llx", sonuc);//hex kod seklinde yazdirma
				USART_SendString(USART1, out);
				
				sonuc = des(sonuc, key[1],'e');
				//sprintf (out,"\nDES sifre Cozumlemesi(Ecrypt)x16: 		%llx", sonuc);//hex kod seklinde yazdirma
				//USART_SendString(USART1, out);
				
				sonuc = des(sonuc, key[0],'d');
				sprintf (out,"\nTriple-DES sifre Cozumlemesi(Decrypt): %llx", sonuc);//hex kod seklinde yazdirma
				USART_SendString(USART1, out);
				
				receviekey=0;
				}
			GPIO_ResetBits(GPIOG, GPIO_Pin_14);

		}
			
    return (0);
}
 
static void USART_SendString(USART_TypeDef* USARTx, char* s)
{
    while(*s)
    {
        while(!USART_GetFlagStatus(USARTx, USART_FLAG_TC));
        USART_SendData(USARTx, *s);
        s++;
    }
}

