String rgbToHex(const int rgb[3]) {
    // Проверяю, что значения R, G, B находятся в диапазоне 0–255
    int r = constrain(rgb[0], 0, 255);
    int g = constrain(rgb[1], 0, 255);
    int b = constrain(rgb[2], 0, 255);

    // Форматируем строку как шестнадцатеричное значение #RRGGBB
    char hexColor[8];
    snprintf(hexColor, sizeof(hexColor), "#%02X%02X%02X", r, g, b);

    return String(hexColor);
}

void hexToRGB(const String &hexColor) {
    
    if (hexColor[0] == '#') {
        settings.RGB_C[0] = strtol(hexColor.substring(1, 3).c_str(), nullptr, 16); // Красный
        settings.RGB_C[1] = strtol(hexColor.substring(3, 5).c_str(), nullptr, 16); // Зелёный
        settings.RGB_C[2] = strtol(hexColor.substring(5, 7).c_str(), nullptr, 16); // Синий
    } else {
        settings.RGB_C[0] = settings.RGB_C[1] = settings.RGB_C[2] = 0;
    }
    
}
