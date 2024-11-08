// Функция отправки данных по протоколу MQTT
void MQTT_send(){
   client.loop();
   uint32_t nows = millis();
  if (nows - lastMsg > 30000 && settings.mqtt_en) {
    if(WiFi.status() == WL_CONNECTED) {
        MQTT_send_data("jsondata", JSON_DATA());
     }
   lastMsg = nows; 
  }
 }
void MQTT_send_data(String topic, String data){
         String root = settings.mqtt_topic;
         String top  = root +"/"+ topic;
         String subscr = root +"/control";
         String input = settings.mqtt_serv;
         int colonIndex = input.indexOf(':');
         String ipAddress;
         String port;
         IPAddress Remote_MQTT_IP;

        if (colonIndex != -1) {
             ipAddress = input.substring(0, colonIndex);
             port = input.substring(colonIndex + 1);
             WiFi.hostByName(ipAddress.c_str(), Remote_MQTT_IP);
          }
      
      client.setServer(Remote_MQTT_IP, port.toInt());
      client.setCallback(callback);
           if(client.connected()){                                                                                    // Вторичная отправка данных при подключенном брокере 
          count_rf = 0;
          send_mqtt(top, data, subscr);
           }else{
              count_rf++;
              String ch_id = String(ESP.getChipId());
              if (client.connect(ch_id.c_str(), settings.mqtt_user, settings.mqtt_passw)){                             // Первичная отправка данных, выполняестя попытка подключения к брокеру 
                    send_mqtt(top, data, subscr);          
                }else{
                  if(count_rf > 2){                                                                                    // Если были неудачные попытки подключения, то переподключаем Wi-fi
                     WiFi.disconnect();
                     WiFi.begin(settings.mySSID, settings.myPW);
                     count_rf = 0;
                }
            }
        }
     
}

void send_mqtt(String tops, String data, String subscr){

    String top_temp = get_topic(settings.mqtt_topic, false);
    String top_hum  = get_topic(settings.mqtt_topic_h, false);
    String top_prs  = get_topic(settings.mqtt_topic_p, false);

    client.subscribe(top_temp.c_str());
    client.subscribe(top_hum.c_str());
    client.subscribe(top_prs.c_str());
}

String get_topic(String indata, boolean json){

         int colonIndex = indata.indexOf(':');
         String topic;
         String jsonkey;
         String out;

        if (colonIndex != -1) {
             topic   = indata.substring(0, colonIndex);
             jsonkey = indata.substring(colonIndex + 1);
          }else{
             topic = indata;
          }
         if(json){
            out = jsonkey;
         }else{
            out = topic;
         }
  return out;
}


String MQTT_status(){
    String response_message = "";
    if(client.connected()){
         response_message = "подключен";
      }else{
         response_message = "отключен";
    }
    return response_message;
} 
