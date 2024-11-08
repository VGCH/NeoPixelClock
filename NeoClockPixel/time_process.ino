void get_TIME_data(){
  unsigned long currentMillis = millis();
         if((currentMillis - NTP_t) > settings.time_cycle*1000 && settings.ntp_en && settings.time_cycle > 60 || epoch == 0 && settings.ntp_en && settings.time_cycle > 60){ // Get ntp time
               ntp_process(); 
            NTP_t = currentMillis;
        }
  }

void ntp_process(){
    WiFi.hostByName(settings.ntp_serv, timeServerIP);
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
     int cb = udp.parsePacket();
  if (!cb) {
    //Serial.println("no packet yet");
  } else {
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    epoch = secsSince1900 - seventyYears + settings.time_zone * SECS_PER_HOUR - (millis()/1000);
    }
  }   
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address) {
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}


String formatUnixTime(unsigned long epoch) {
  // Устанавливаем временную зону (в данном случае UTC)
   //setTime(settings.time_zone);
  
  // Преобразуем Unix timestamp в структуру времени
    tmElements_t timeInfo;
    breakTime(epoch+(millis()/1000), timeInfo);
  
  // Создаем строку с форматированным временем
  String formattedTime = String(timeInfo.Day) + "." + String(twoDigits(timeInfo.Month)) + "." + String(timeInfo.Year + 1970) + " " +
                         String(twoDigits(timeInfo.Hour)) + ":" + String(twoDigits(timeInfo.Minute)) + ":" + String(twoDigits(timeInfo.Second));
  
   return formattedTime;
 }
