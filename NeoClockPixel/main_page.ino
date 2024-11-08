void handleRoot() {
   if (captivePortal()) {  
    return;
  }
  String header;
  if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html lang=\"ru\"><head><meta charset=\"UTF-8\"><title>Управление часами</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  //html +=  js;
  html += "</head><body>";
  html += FPSTR(divcode);
  html += "<h2>Управление часами</h2>";
  html += "<div class =\"frame\">";
  String content ="";
  if (server.hasHeader("User-Agent")) {
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  html += "<text>Время работы устройства:</text> <div class =\"live\" id=\"timew\">00:00:00:00</div>";
  html += "<text>Время сети (NTP): <div class =\"live\" id=\"DTM\">00:00:00:00</div></text>";
  html += "<text>Статус MQTT </text> <div class =\"live\" id=\"MQTT\">"+MQTT_status()+"</div>";
  html += "<text>Активировать регулировку яркости по датчику </text><div class =\"live\"><label class=\"switch\"><input onclick=\"switch_b(this.checked ? 'on' : 'off')\" type=\"checkbox\" id=\"switch_auto\" "+get_switch()+"><span class=\"slider round\"></span></label></div>";
  html += "<text>Уровень датчика освещенности: <div class =\"live\" id=\"bright\">0</div></text>";
  html += "<text>Ручная регулировка уровня яркости:</text><br><br>";
  html += "<input name=\"flevel\" id=\"flying\" type=\"range\" min=\"1\" max=\"100\" value=\""+String(settings.led_level)+"\" step=\"1\">";
  html += "<div class =\"live\" id=\"response\">"+String(settings.led_level)+"</div>";
  html += "<text>Цвет отображения:</text><br><br>";
  html += "<div class =\"live\"><input type=\"color\" name=\"bg\" id=\"colorPicker\" value=\""+rgbToHex(settings.RGB_C)+"\"></div>";
  html += "<br></div></body>";
  html += "<center><br><a href=\"/?page=wlan_config\">Wi-Fi конфигурация</a><br>";
  html += "<a href=\"/?page=send_config\">Настройка MQTT</a><br>";
  html += "<a href=\"/?page=time_config\">Настройка NTP</a><br>";
  html += "<a href=\"/?page=changelp\">Изменение пароля устройства</a><br>";
  html += "<a href=\"/?page=update_fw\">Обновление прошивки</a><br>";
  html += "<a href=\"#\" onclick=\"rebootdev()\">Перезагрузить устройство</a><br>";
  html += "<a href=\"/login?DISCONNECT=YES\">Выход</a></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2024. Версия микро ПО <b>"+version_code+"</b>.</footer>";
  html += "<script src=\"script.js\"></script>"; 
  html +=  FPSTR(js);
  html += "</html>";
  server.send(200, "text/html", html);
}


String get_switch(){
  String status_s; 
  if(settings.auto_on){
    status_s = "checked";
  }
  return status_s; 
}
