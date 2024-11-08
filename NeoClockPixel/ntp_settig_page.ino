void send_ntp_config(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Настройка NTP</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html += "</head><body>";
  html += "<h2>Кофигурация NTP </h2>";
  html += "<form>";
  html += "<input type=\"checkbox\" id=\"switch_ntp\" "+ntp_act()+"><text> Активировать синхронизацию времени по NTP </text><br>";
  html += "<div id=\"response2\">"+status_ntp_en()+"</div><br>";
  html += "<div class=\"spoiler\"><input type=\"checkbox\" id=\"spoiler1\">";
  html += "<label for=\"spoiler1\">Посмотреть текущую конфигурацию</label>";
  html += "<div id=\"response21\">"+full_cong_ntp()+"</div></div>";
  html +=" </form>";
  html += "<form id=\"config-form\" >";
  html += "<div id=\"response\">";
  html += "<label for=\"ip\">IP адрес сервера MQTT:</label>";
  html += "<input type=\"text\" id=\"ntpServer\" name=\"ntpServer\" placeholder=\"pool.ntp.org\" value=\""+String(settings.ntp_serv)+"\" required><br>";
  html += " <label for=\"timezone\">Часовой пояс:</label>";
  html += "      <select id=\"timezone\" name=\"timezone\" required>";
  html += "          <option value=\"\" disabled selected>Выберите часовой пояс</option>";
  html += "          <option value = '1'> UTC/GMT+1 (Центральная Европа)</option>";
  html += "          <option value = '2'> UTC/GMT+2 (Калининград)</option>";
  html += "          <option value = '3'> UTC/GMT+3 (Москва)</option>";
  html += "          <option value = '4'> UTC/GMT+4 (Самара, Ижевск)</option>";
  html += "          <option value = '5'> UTC/GMT+5 (Екатеринбург)</option>";
  html += "          <option value = '6'> UTC/GMT+6 (Омск)</option>";
  html += "          <option value = '7'> UTC/GMT+7 (Красноярск)</option>";
  html += "          <option value = '8'> UTC/GMT+8 (Иркутск)</option>";
  html += "          <option value = '9'> UTC/GMT+9 (Якутск)</option>";
  html += "          <option value = '10'> UTC/GMT+10 (Владивосток)</option>";
  html += "          <option value = '11'> UTC/GMT+11 (Камчатка)</option>";
  html += "          <option value = '0'> UTC/GMT-0 (Гринвич)</option>";
  html += "          <option value = '-2'> UTC/GMT-2 (Среднеатлантическое время)</option>";
  html += "          <option value = '-3'> UTC/GMT-3 (Аргентина)</option>";
  html += "          <option value = '-4'> UTC/GMT-4 (Канада)</option>";
  html += "          <option value = '-5'> UTC/GMT-5 (Нью-Йорк)</option>";
  html += "          <option value = '-6'> UTC/GMT-6 (Чикаго)</option>";
  html += "          <option value = '-7'> UTC/GMT-7 (Денвер)</option>";
  html += "          <option value = '-8'> UTC/GMT-8 (Лос-Анджелес)</option>";
  html += "      </select>";
  html += "<label for=\"number\">Периодичность синхронизации времени (с):</label>";
  html += "<input type=\"number\" id=\"number\" name=\"times_ntp\" placeholder=\"Пример: 60\" pattern=\"[0-9]{4,}\" value=\""+String(settings.time_cycle)+"\" required><br><br>";
  html += "<input type=\"submit\" value=\"Сохранить\">";
  html += "</div>";
  html += "</form><br>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2024. Версия микро ПО <b>"+version_code+"</b>. </footer>";
  html +="<script>";
  html +="const form = document.getElementById('config-form');";
// Добавляем обработчик события отправки формы
  html +="form.addEventListener('submit', (event) => {";
  html +="  event.preventDefault();"; // Отменяем стандартное поведение формы
  html +="  const formData = new FormData(form);"; // Получаем данные формы
  html +="  const xhr = new XMLHttpRequest();"; // Создаем объект XMLHttpRequest
  html +="  xhr.open('POST', '?page=indata');"; // Указываем метод и URL для отправки данных
  html +="  xhr.addEventListener('load', () => {";
  html +="    if (xhr.status === 200) {"; // Проверяем статус ответа
  html +="      document.getElementById('response').innerHTML = xhr.responseText;"; // Выводим ответ сервера в консоль
  html +="    } else {";
  html +="      document.getElementById('response').innerHTML = 'Ошибка отправки';"; // Выводим сообщение об ошибке в консоль
  html +="    }";
  html +="  });";
  html +="  xhr.send(formData);"; // Отправляем данные формы
  html +="});";
  html +="</script>";
  html += "  <script>";
      // при изменении состояния переключателя отправляем данные на сервер
  html += "    document.getElementById('switch_ntp').addEventListener('change', function() {";
  html += "      var status = this.checked ? 'on' : 'off';";
  html += "      var xhr = new XMLHttpRequest();";
  html += "      xhr.open('POST', '?page=indata', true);";
  html += "      xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
  html += "      xhr.onreadystatechange = function() {";
  html += "        if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {";
  html += "          console.log(this.responseText);";
  html += "            document.getElementById('response2').innerHTML = xhr.responseText;";
  html += "       }else{";
  html += "          console.log(\"error\");";
  html += "        }";
  html += "      };";
  html += "      xhr.send('switch_ntp=' + status);";
  html += "    });";
  html += "  </script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
String ntp_act(){
String rt ="";
  if(settings.ntp_en){
    rt = "checked";
  }
  return rt;
}

String full_cong_ntp(){
    String data = "";
    data += "<text> Адрес сервера NTP: <b>"+String(settings.ntp_serv)+"</b></text><br>";
    data += "<text> Часовой пояс: <b>"+String(settings.time_zone)+"</b></text><br>";
    data += "<text> Периодичность синхронизации(с): <b>"+String(settings.time_cycle)+"</b></text><br>";
    return data;
}
String status_ntp_en(){
  String data = "<text>Синхронизация по NTP отключена.</text>";
  if(settings.ntp_en){
    data = "<text>Синхронизация по NTP включена</text>";
  }
  return data;
}
