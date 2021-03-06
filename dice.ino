#define col1 2                                // Колонки
#define col2 3
#define col3 4
#define col4 5
#define col5 6
#define col6 7
#define col7 8
#define col8 9

#define row1 10                                // Ряды
#define row2 11
#define row3 12
#define row4 13
#define row5 A0
#define row6 A1
#define row7 A2
#define row8 A3

#define vibration A5                          // Контакт датчика наклона

uint8_t rows[8] {row1, row2, row3, row4, row5, row6, row7, row8};    // Пины строк
uint8_t cols[8] {col1, col2, col3, col4, col5, col6, col7, col8};    // Пины колонок
uint8_t randomValue = 0;                                             // Переменная случайного значения
uint8_t readSensor = 0;                                              // Временное состояние считанного значения датчика угла
int valCrash = 0;                                                    // Счётчик изменений датчика угла
unsigned long resetTime;                                             // Переменные времени для сброса датчика угла
unsigned long shakeTime;                                             // Время для задания эффектов
unsigned long eventTime;                                             // Время для задания действия кубика
uint8_t a;                                                           // Переменная для задания эффектов
uint8_t event;                                                       // Флаг для определения начала действия кубика

char indication[8][8];                                                // Массив для динамической индикации

const char one[8][8] = {
  {'0', '0', '0', '0', '0', '0', '0', '0'},                          // Единица
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'}
};

const char two[8][8] = {
  {'0', '0', '0', '0', '0', '0', '0', '0'},                          // Два
  {'0', '1', '1', '0', '0', '0', '0', '0'},
  {'0', '1', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '1', '0'},
  {'0', '0', '0', '0', '0', '1', '1', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'}
};

const char three[8][8] = {
  {'1', '1', '0', '0', '0', '0', '0', '0'},                          // Три
  {'1', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '1'},
  {'0', '0', '0', '0', '0', '0', '1', '1'}
};

const char four[8][8] = {
  {'0', '0', '0', '0', '0', '0', '0', '0'},                          // Четыре
  {'0', '1', '1', '0', '0', '1', '1', '0'},
  {'0', '1', '1', '0', '0', '1', '1', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '1', '1', '0', '0', '1', '1', '0'},
  {'0', '1', '1', '0', '0', '1', '1', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'}
};

const char five[8][8] = {
  {'1', '1', '0', '0', '0', '0', '1', '1'},                          // Пять
  {'1', '1', '0', '0', '0', '0', '1', '1'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'1', '1', '0', '0', '0', '0', '1', '1'},
  {'1', '1', '0', '0', '0', '0', '1', '1'}
};

const char six[8][8] = {
  {'0', '0', '0', '0', '0', '0', '0', '0'},                          // Шесть
  {'1', '1', '0', '1', '1', '0', '1', '1'},
  {'1', '1', '0', '1', '1', '0', '1', '1'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'1', '1', '0', '1', '1', '0', '1', '1'},
  {'1', '1', '0', '1', '1', '0', '1', '1'},
  {'0', '0', '0', '0', '0', '0', '0', '0'}
};

const char frame1[8][8] = {
  {'0', '0', '0', '0', '0', '0', '0', '1'},                          // Кадр 1
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'}
};

const char frame2[8][8] = {
  {'0', '0', '0', '0', '0', '0', '1', '0'},                          // Кадр 2
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'}
};

const char frame3[8][8] = {
  {'0', '0', '0', '0', '0', '1', '0', '0'},                          // Кадр 3
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'}
};

const char frame4[8][8] = {
  {'0', '0', '0', '0', '1', '0', '0', '0'},                          // Кадр 4
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'}
};

const char frame5[8][8] = {
  {'0', '0', '0', '1', '0', '0', '0', '0'},                          // Кадр 5
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '1', '0', '0', '0'}
};

const char frame6[8][8] = {
  {'0', '0', '1', '0', '0', '0', '0', '0'},                          // Кадр 6
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'},
  {'0', '0', '1', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '1', '0', '0'}
};

const char frame7[8][8] = {
  {'0', '1', '0', '0', '0', '0', '0', '0'},                          // Кадр 7
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'},
  {'0', '1', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '1', '0'}
};

const char frame8[8][8] = {
  {'1', '0', '0', '0', '0', '0', '0', '0'},                          // Кадр 8
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'},
  {'1', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '1'}
};

void setup()
{
  for (int i = 0; i < 8; ++i) {
    pinMode(rows[i], OUTPUT);                 // Инициализируем пины строк на выход
    pinMode(cols[i], OUTPUT);                 // Инициализируем пины колонок на выход
  }
  pinMode(vibration, INPUT);                  // Вход датчика угла на вход
  digitalWrite (vibration, HIGH);
  reset_display();                            // Сбрасываем дисплей
}

void random_value ()
{
  randomSeed(analogRead(4));                  // Случайное значение с аналогового входа
  randomValue = random(1, 7);                 // Принимаем значение от 1 до 7
  for (int i = 0; i < 8; i++)                 // Цикл, который значения одного массива передаёт другому
  {
    for (int j = 0; j < 8; j++)
    {
      switch (randomValue) {
        case 1:
          indication[i][j] = one[i][j];       // В случае рандомного значения = 1, назначаем циклу indication значение массива one
          break;
        case 2:
          indication[i][j] = two[i][j];       // И т.д. для остальных значений
          break;
        case 3:
          indication[i][j] = three[i][j];
          break;
        case 4:
          indication[i][j] = four[i][j];
          break;
        case 5:
          indication[i][j] = five[i][j];
          break;
        case 6:
          indication[i][j] = six[i][j];
          break;
      }
    }
  }
}

void dynamic_indi()                                      // Функция динамической индикации
{
  for (uint8_t c = 0; c < 8; c++)                        // Перебираем ряды
  {
    for (uint8_t z = 0; z < 8; z++)                      // Перебираем колонки
    {
      digitalWrite(cols[z], indication[c][z] - 48);      // Теперь назначаем колонкам значения из массива, для этой строки и колонки
    }
    digitalWrite(rows[c], HIGH);                         // Устанавливаем строку в активное состояние
    delay(1);                                            // Пауза
    digitalWrite(rows[c], LOW);                          // Переводим строку в неактивное состояние
  }
}

void crash()
{
  if (digitalRead(vibration) == readSensor && event == 0)    // Если состояние датчика равно переменной состояния
  {
    readSensor = !readSensor;                                // Меняем переменную состояния на противоположное значение
    valCrash++;                                              // Инкрементируем счётчик трясок
    resetTime = millis();
    if (valCrash > 16)                                       // Если количество трясок более 20, то делаем действие
    {
      reset_display();
      eventTime = millis();
      resetTime = millis();
      event = 1;
      valCrash = 0;                                          // Обнуляем счётчик трясок
      delay(30);
    }
  }
}

void resetCrash()
{
  if (millis() - resetTime > 7000)                          // Сбрасываем дисплей, если время простоя более 7 секунд
  {
    resetTime = millis();                                   // Приравниваем переменную сброса к времени контроллера
    valCrash = 0;
    reset_display();                                        // Функция сброса
  }
}

void reset_display()                                        // Функция сброса информации на экране
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      indication[i][j] = 48;                                // Заполняем нулями все 64 значения
    }
  }
}

void shaking()                                              // Функция анимации перед генерацией числа
{
  if (millis() - shakeTime > 80 && event == 1)
  {
    if (a > 7)
    {
      a = 0;
    }
    for (int i = 0; i < 8; i++)                             // Цикл, который значения одного массива передаёт другому
    {
      for (int j = 0; j < 8; j++)
      {
        switch (a) {
          case 0:
            indication[i][j] = frame1[i][j];                // В случае рандомного значения = 1, назначаем циклу indication значение массива one
            break;
          case 1:
            indication[i][j] = frame2[i][j];                // И т.д. для остальных значений
            break;
          case 2:
            indication[i][j] = frame3[i][j];
            break;
          case 3:
            indication[i][j] = frame4[i][j];
            break;
          case 4:
            indication[i][j] = frame5[i][j];
            break;
          case 5:
            indication[i][j] = frame6[i][j];
            break;
          case 6:
            indication[i][j] = frame7[i][j];
            break;
          case 7:
            indication[i][j] = frame8[i][j];
            break;
        }
      }
    }
    a++;
    shakeTime = millis();
  }
}

void action ()                                       // Проверка условий для запуска отображения случайного числа
{
  if (millis() - eventTime >= 1500 && event == 1)
  {
    event = 0;                                       // Сбрасываем флаг действия
    reset_display();                                 // Очищаем экран
    random_value();                                  // Задаём массиву случайное значение
    eventTime = millis();                            // Сбрасываем переменную времени действия
  }
}

void loop()
{
  shaking();                                          // Функция анимации
  action();                                           // Вызов проверки функции действия
  resetCrash();                                       // Вызов функции сброса экрана и действия
  crash();                                            // Вызов функции проверки тряски датчика наклона
  dynamic_indi();                                     // Динамическая индикация всегда должна быть активна
}
