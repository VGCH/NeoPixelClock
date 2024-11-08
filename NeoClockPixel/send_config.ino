void send_config(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Конфигурация приема данных</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html += "</head><body>";
  html += "<h2>Конфигурация обмена (MQTT)</h2>";
  html += "<form>";
  html += "<input type=\"checkbox\" id=\"switch\" "+mqtt_act()+"><text> Активировать сбор данных</text><br>";
 // html += "<input type=\"checkbox\" id=\"switchjson\" "+json_act()+" ><text> Использовать формат JSON </text>";
  html += "<div id=\"response2\">"+status_mqtt_en()+"</div><br>";
  html += "<div class=\"spoiler\"><input type=\"checkbox\" id=\"spoiler1\">";
  html += "<label for=\"spoiler1\">Посмотреть текущую конфигурацию</label>";
  html += "<div id=\"response21\">"+full_cong()+"</div></div>";
  html +=" </form>";
  html += "<form id=\"config-form\" >";
  html += "<div id=\"response\">";
  html += "<label for=\"ip\">IP адрес сервера MQTT:</label>";
  html += "<input type=\"text\" id=\"ip\" name=\"IPMQTT\" placeholder=\"192.168.1.2:1883\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5]):(\\d{1,5})$\" value=\""+String(settings.mqtt_serv)+"\" required><br>";
  html += "<label for=\"login\">Логин:</label>";
  html += "<input type=\"text\" id=\"login\" name=\"USERNAME\" placeholder=\"Логин MQTT\" value=\""+String(settings.mqtt_user)+"\" required><br>";
  html += "<label for=\"password\">Пароль:</label>";
  html += "<input type=\"password\" id=\"password\" name=\"PASSWORD\" placeholder=\"Пароль MQTT\" required><br>";
 // html += "<label for=\"id\">Идентификатор устройства:</label>";
 // html += "<input type=\"text\" id=\"id\" name=\"ID\" placeholder=\"Идентификатор устройства\" value=\""+settings.mqtt_id+"\" required><br>";
  html += "<label for=\"topic\">Топик температуры:</label>";
  html += "<input type=\"text\" id=\"topic\" name=\"topicname\" placeholder=\"Пример: root/temp\"  value=\""+String(settings.mqtt_topic)+"\" required><br>";
  html += "<label for=\"topic_h\">Топик влажности воздуха:</label>";
  html += "<input type=\"text\" id=\"topic_h\" name=\"topic_h\" placeholder=\"Пример: root/hum\"  value=\""+String(settings.mqtt_topic_h)+"\" required><br>";
  html += "<label for=\"topic_p\">Топик атм. давления:</label>";
  html += "<input type=\"text\" id=\"topic_p\" name=\"topic_p\" placeholder=\"Пример: root/prs\"  value=\""+String(settings.mqtt_topic_p)+"\" required><br>";
  html += "<text>Если данные предоставляются в формате JSON, то через символ \":\" укажите ключ параметра, например:<br><i>meteo/data:temp</i></text><br><br>";
 // html += "<input type=\"number\" id=\"number\" name=\"times\" placeholder=\"Пример: 60\" pattern=\"[0-9]{4,}\" value=\""+String(settings.mqtt_time)+"\" required><br><br>";
  html += "<input type=\"submit\" value=\"Сохранить\">";
  html += "</div>";
  html += "</form><br>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2024. Версия микро ПО <b>"+version_code+"</b>. </footer>";
  html += FPSTR(config_js);
  html += "</body></html>";
  server.send(200, "text/html", html);
}

String mqtt_act(){
String rt ="";
  if(settings.mqtt_en){
    rt = "checked";
  }
  return rt;
}

String full_cong(){
    String data = "";
    data += "<text> IP адрес сервера MQTT: <b>"+String(settings.mqtt_serv)+"</b></text><br>";
    data += "<text> Логин: <b>"+String(settings.mqtt_user)+"</b></text><br>";
    data += "<text> Идентификатор устройства: <b>"+String(ESP.getChipId())+"</b></text><br>";
    data += "<text> Топик температуры: <b>"+String(settings.mqtt_topic)+"</b></text><br>";
    data += "<text> Топик влажности воздуха: <b>"+String(settings.mqtt_topic_h)+"</b></text><br>";
    data += "<text> Топик атм. давления: <b>"+String(settings.mqtt_topic_p)+"</b></text><br>";
    //data += "<text> Периодичность обмена(с): <b>"+String(settings.mqtt_time)+"</b></text><br>";
    return data;
}
String status_mqtt_en(){
  String data = "<text>Прием данных отключен.</text>";
  if(settings.mqtt_en){
    data = "<text>Прием данных включен.</text>";
  }
  return data;
}
