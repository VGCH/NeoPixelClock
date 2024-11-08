 String millis2time(){ // преобразование миллисекунд в вид д/ч/м/с
  
         int times =(millis()/1000);
         int days =  (times/3600)/24;
         int timehour =(((times)  % 86400L) / 3600); // часы
        if ( ((times % 3600) / 60) < 10 ) {
         int timehour = 0;
               }
         int timeminuts=((times  % 3600) / 60); // минуты
         if ( (times % 60) < 10 ) {
         int timeminuts = 0;
             }
         int timeseconds=(times % 60); // секунды
       String Time= String(days)+":"+String(twoDigits(timehour))+":"+String(twoDigits(timeminuts))+":"+String(twoDigits(timeseconds));
       return Time;
     }

 String twoDigits(int digits){
             if(digits < 10) {
          String i = '0'+String(digits);
          return i;
         }
          else {
        return String(digits);
         }
      }

void time_work(){
   if (captivePortal()) {  
    return;
  }
  if (validateToken()){
       String json = JSON_DATA();
                
     server.send(200, "text", json);   
  }   
}



String JSON_DATA(){
       DynamicJsonDocument doc(1024);
       doc["time"]    = millis2time();
       doc["MQTT"]    = MQTT_status();
       doc["DTM"]     = formatUnixTime(epoch);
       doc["bright"]  = String(BRReadData());        // Автоматическая яркость
       doc["br"]      = String(settings.led_level);  // Ручная яркость
       doc["con"]     = String(settings.auto_on);    // Статус автоматического режима
       doc["temp"]    = temp_j;                      // Температура
       doc["hum"]     = hum_j;                       // Влажность
       doc["prs"]     = prs_j;                       // Давление
       
    JsonArray rgb = doc.createNestedArray("rgb");  // Добавляем RGB как массив
              rgb.add(settings.RGB_C[0]);          // Красный
              rgb.add(settings.RGB_C[1]);          // Зеленый
              rgb.add(settings.RGB_C[2]);          // Синий
              
       String json;
       serializeJson(doc, json);
     return json;
}

int BRReadData(){
     int AN = analogRead(A0);
  return map(AN, 0, 1023, 50, 255);
}
