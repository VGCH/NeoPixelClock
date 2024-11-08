void indata(){
     if (captivePortal()) { 
    return;
  }
  if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
    if (server.hasArg("switch")){  
    String msg;   
      if(server.arg("switch")=="on"){
        settings.mqtt_en = true;
        save_config();
        msg +="<text>Передача данных включена!</text>";
         String input   = settings.mqtt_serv;
         int colonIndex = input.indexOf(':');
         String ipAddress;
         String port;

        if (colonIndex != -1) {
             ipAddress = input.substring(0, colonIndex);
             port = input.substring(colonIndex + 1);
          }
        client.setServer(ipAddress.c_str(), port.toInt());
        }else if(server.arg("switch")=="off"){
        settings.mqtt_en = false;
        save_config();
        msg +="<text>Передача данных выключена!</text>";
    } 
    server.send(200, "text/html", msg);
  }
   if (server.hasArg("switch_auto")){  
    String msg;   
      if(server.arg("switch_auto")=="on"){
        settings.auto_on = true;
        save_config();
        msg +="<text>Прием данных активирован!</text>";
        }else if(server.arg("switch_auto")=="off"){
        settings.auto_on = false;
        save_config();
        msg +="<text>Прием данных деактивирован!</text>";
    } 
    server.send(200, "text/html", msg);
    if(settings.mqtt_en){ MQTT_send_data("jsondata", JSON_DATA());}
  }

 

 if(server.hasArg("IPMQTT") && server.hasArg("PASSWORD")){  
    strncpy(settings.mqtt_serv, server.arg("IPMQTT").c_str(), MAX_STRING_LENGTH);
    //settings.mqtt_user     = String(server.arg("USERNAME"));                        // Логин mqtt
    strncpy(settings.mqtt_user, server.arg("USERNAME").c_str(), MAX_STRING_LENGTH);
    //settings.mqtt_passw    = String(server.arg("PASSWORD"));                        // Пароль mqtt
    strncpy(settings.mqtt_passw, server.arg("PASSWORD").c_str(), MAX_STRING_LENGTH);
  //  settings.mqtt_id       = String(server.arg("ID"));                              // Идентификатор mqtt 
    //settings.mqtt_topic    = String(server.arg("topicname"));                       // Корень mqtt 
    strncpy(settings.mqtt_topic, server.arg("topicname").c_str(), MAX_STRING_LENGTH); // Температура
    strncpy(settings.mqtt_topic_h, server.arg("topic_h").c_str(), MAX_STRING_LENGTH); // Влажность
    strncpy(settings.mqtt_topic_p, server.arg("topic_p").c_str(), MAX_STRING_LENGTH); // Атм. Давление
  //  settings.mqtt_time     = server.arg("times").toInt();                           // Переодичность обмена mqtt .toInt();
    save_config();
    
    String data = "";
    data += "<text> IP адрес сервера MQTT: <b>"+String(settings.mqtt_serv)+"</b></text><br>";
    data += "<text> Логин: <b>"+String(settings.mqtt_user)+"</b></text><br>";
    data += "<text> Идентификатор устройства: <b>"+String(ESP.getChipId())+"</b></text><br>";
    data += "<text> Топик температуры: <b>"+String(settings.mqtt_topic)+"</b></text><br>";
    data += "<text> Топик влажности: <b>"+String(settings.mqtt_topic_h)+"</b></text><br>";
    data += "<text> Топик атм. давления: <b>"+String(settings.mqtt_topic_p)+"</b></text><br>";
    //data += "<text> Периодичность обмена(с): <b>"+String(settings.mqtt_time)+"</b></text><br>";
    data += "<text><b>Данные успешно сохранены!</b></text>";
    server.send(200, "text/html", data);
  }
  
   if(server.hasArg("NEWPASSWORD")){  
       if(server.arg("NEWPASSWORD") != ""){
           //settings.passwd = String(server.arg("NEWPASSWORD")); 
           strncpy(settings.passwd, server.arg("NEWPASSWORD").c_str(), MAX_STRING_LENGTH);
           save_config();
    }
   
    String data = "";
    data += "<text><b>Новый пароль успешно сохранён!</b></text>";
    server.send(200, "text/html", data);
  }

 if (server.hasArg("genkey")){     
           strncpy(settings.API_key, generateToken().c_str(), MAX_STRING_LENGTH); // Генерируем и сохраняем новый API ключ
           save_config();                                                         // Сохраняем в EEPROM
     
           server.send(200, "text/html", String(settings.API_key));
  }
 if (server.hasArg("switch_ntp")){  
    String msg;   
      if(server.arg("switch_ntp")=="on"){
        settings.ntp_en = true;
        save_config();
        msg +="<text>Синхронизация времени включена!</text>";
        }else if(server.arg("switch_ntp")=="off"){
        settings.ntp_en = false;
        save_config();
        msg +="<text>Синхронизация времени выключена!</text>";
    } 
    server.send(200, "text/html", msg);
  } 
  
 if(server.hasArg("ntpServer") && server.hasArg("timezone")){  
    strncpy(settings.ntp_serv, server.arg("ntpServer").c_str(), 30);
    settings.time_zone     = server.arg("timezone").toInt();            //Time Zone;
    settings.time_cycle    = server.arg("times_ntp").toInt();           //Переодичность синхронизации;
    save_config();
    
    String data = "";
    data += "<text> Адрес сервера NTP: <b>"+String(settings.ntp_serv)+"</b></text><br>";
    data += "<text> Временная зона: <b>"+String(settings.time_zone)+"</b></text><br>";;
    data += "<text> Периодичность синхронизации(с): <b>"+String(settings.time_cycle)+"</b></text><br>";
    data += "<text><b>Данные успешно сохранены!</b></text>";
    server.send(200, "text/html", data);
  }
  
 if (server.hasArg("flevel")){  
    String msg = server.arg("flevel");   
     int level = msg.toInt();
     settings.led_level = level;
     save_config();
     pixels.setBrightness(map(level, 0, 100, 0, 255));
     server.send(200, "text/html", String(server.arg("flevel").c_str()));
  }
   if (server.hasArg("color")){  
    String msg = server.arg("color");   
     hexToRGB(msg);
     save_config();
    // pixels.setBrightness(map(level, 0, 100, 0, 255));
    server.send(200, "text/html", String(server.arg("color").c_str()));
  }
}
