void main_process(){
  unsigned long ctm = millis();
    if(ctm - tpm  > 1000) {
      if(settings.auto_on){ pixels.setBrightness(BRReadData()); }
      if(millis() > 20000){
            unsigned long cM = millis();
            if(cM - tpm2 > 100 && cM - tpm2 < 20000 ) {                  
                    digitset(second()%10, 0);
                    digitset(second()/10, 1);
                    digitset(minute()%10, 2);
                    digitset(minute()/10, 3);
                    digitset(hour()%10,   4);
                    digitset(hour()/10,   5);
                    if(!settings.mqtt_en){
                         tpm2 = cM;
                    }

          }
            if(cM - tpm2 > 20000 && cM - tpm2 < 20500 && settings.mqtt_en) {
                for (int i = 0; i < LEDs; ++i) {  
                    pixels.setPixelColor(i, pixels.Color(0,0,0)); 
                    pixels.show();
                     delay(10);
                    }
               for (int i = 0; i < LEDs; ++i) {  
                    pixels.setPixelColor(i, pixels.Color(settings.RGB_C[0],settings.RGB_C[1],i*2)); 
                    pixels.show();
                    delay(10);
                   }
               } 

            if(cM - tpm2  > 20500 && cM - tpm2  < 30000 ) {

                    digitset(15, 0);
                    digitset(14, 1);
                    int temp = temp_j.toInt();
                    int tempint = int(abs(temp));

                    digitset(tempint % 10, 2);
                    if (temp < 0 and (tempint /10) == 0) { digitset(16, 3);}
                    if (temp >= 0 and (tempint /10) == 0) { digitset(10, 3);}
                    if ((tempint /10) > 0){ digitset(tempint /10, 3); }
                    if (temp < 0 and (tempint /10) > 0) { digitset(16, 4); }
                    else { digitset(10, 4);}
                    digitset(11, 5);
                }
            if(cM - tpm2  > 30000 && cM - tpm2  < 30500) {
                   for (int i = 0; i < LEDs; ++i) {  
                        pixels.setPixelColor(i, pixels.Color(0,0,0)); 
                        pixels.show();
                        delay(10);
                 }
                   for (int i = 0; i < LEDs; ++i) {  
                        pixels.setPixelColor(i, pixels.Color(settings.RGB_C[0],0,i*2)); 
                        pixels.show();
                        delay(10);
                         }
                }
            
            if(cM - tpm2  > 30500 && cM - tpm2 < 40000) {
                    int hum = hum_j.toInt();
                     digitset(10, 0);
                     digitset(10, 1);
                     digitset(hum % 10, 2);
                     digitset(hum /10, 3);
                     digitset(10, 4);
                     digitset(12, 5);
               }
            if(cM - tpm2  > 45000 && cM - tpm2 < 45500) {
                    for (int i = 0; i < LEDs; ++i) {  
                         pixels.setPixelColor(i, pixels.Color(0,0,0)); 
                         pixels.show();
                         delay(10);
                       }
                    for (int i = 0; i < LEDs; ++i) {  
                         pixels.setPixelColor(i, pixels.Color(i*2,settings.RGB_C[1],0)); 
                         pixels.show();
                         delay(10);
                      }
      
            }

            if(cM - tpm2   > 45500 && cM - tpm2  < 50500) {
                    int presss = prs_j.toInt();
                    digitset(10, 0);
                    digitset(presss % 10, 1);
                    digitset((presss / 10) % 10, 2);
                    digitset(presss /100, 3);
                    digitset(10, 4);
                    digitset(13, 5);
               }
            if(cM - tpm2 > 50500 && cM - tpm2 < 51800) {
                    for (int i = 0; i < LEDs; ++i) {  
                          pixels.setPixelColor(i, pixels.Color(0,0,0)); 
                          pixels.show();
                          delay(10);
               }
                   for (int i = 0; i < LEDs; ++i) {  
                         pixels.setPixelColor(i, pixels.Color(0,i*2,settings.RGB_C[2])); 
                         pixels.show();
                         delay(10);
                    }
             }
  
              if(cM - tpm2  > 50800) {
                     tpm2 = cM;
                }   
       }else{
           digitset(12,   5);  // H
           digitset(17,   4);  // E
           digitset(18,   3);  // L
           digitset(18,   2);  // L
           digitset(19,   1);  // O
           digitset(10,   0);  // Oчистка первой цифры
       }
       tpm = ctm;
    }
}


void digitset(int digit, int queue){
   int gu = 7 * queue;
   for (int j = 0; j < 7; j++) {
            int val = pgm_read_word(&(digits_pix[digit][j]));    // Чтение значения из PROGMEM
            if( val == 1){
              pixels.setPixelColor(j+gu, pixels.Color(settings.RGB_C[0],settings.RGB_C[1],settings.RGB_C[2]));
            }else{
              pixels.setPixelColor(j+gu, pixels.Color(0,0,0));
            }
        }
  pixels.show();
}
