void callback(char* topic, byte* payload, unsigned int length) {
    String top_temp = get_topic(settings.mqtt_topic,   false);
    String top_hum  = get_topic(settings.mqtt_topic_h, false);
    String top_prs  = get_topic(settings.mqtt_topic_p, false);

        if(String(topic) == top_temp){
          String message;
          for (int i = 0; i < length; i++){
             message = message + (char)payload[i];
           }
           String key = get_topic(settings.mqtt_topic,   true);
           if(key.length() > 0){
              temp_j = json_decode(message, key);
           }else{
              temp_j = message;
           }
        }

        if(String(topic) == top_hum){
          String message;
          for (int i = 0; i < length; i++){
             message = message + (char)payload[i];
           }
           String key = get_topic(settings.mqtt_topic_h,   true);
           if(key.length() > 0){
             hum_j = json_decode(message, key);
           }else{
             hum_j = message;
           }
        }

        if(String(topic) == top_prs){
          String message;
          for (int i = 0; i < length; i++){
             message = message + (char)payload[i];
           }
           String key = get_topic(settings.mqtt_topic_p,   true);
           if(key.length() > 0){
             prs_j =  json_decode(message, key);
           }else{
             prs_j = message;
           }
        }
 }

String json_decode(String text, String key){
       StaticJsonDocument<200> doc;
          deserializeJson(doc, text);
          String data = doc[key];

          return data; 
}