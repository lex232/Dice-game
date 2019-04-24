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
#define row5 14
#define row6 15
#define row7 16
#define row8 17

uint8_t rows[8] {row1, row2, row3, row4, row5, row6, row7, row8};    // Пины строк
uint8_t cols[8] {col1, col2, col3, col4, col5, col6, col7, col8};    // Пины колонок

int indication[8][8] = {
  {'1', '1', '0', '0', '0', '0', '1', '1'},                          // Пустой экран
  {'1', '1', '0', '0', '0', '0', '1', '1'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '1', '1', '0', '0', '0'},
  {'0', '0', '0', '0', '0', '0', '0', '0'},
  {'1', '1', '0', '0', '0', '0', '1', '1'},
  {'1', '1', '0', '0', '0', '0', '1', '1'}
};


void setup()
{
  for (int i = 0; i < 8; ++i) {
    pinMode(rows[i], OUTPUT);                 // Инициализируем пины строк на выход
    pinMode(cols[i], OUTPUT);                 // Инициализируем пины колонок на выход
  }
}


void dynamic_indi()
{
  for (uint8_t c = 0; c < 8; c++)                        // Функция динамической индикации
  {
    for (uint8_t z = 0; z < 8; z++)
    {
      digitalWrite(cols[z], indication[c][z] - 48);      // Теперь назначаем колонкам значения из массива, для это строки и колонки
    }
    digitalWrite(rows[c], HIGH);                         // Устанавливаем строку в активное состояние   
    delay(1);                                            // Пауза
    digitalWrite(rows[c], LOW);                          // Переводим строку в неактивное состояние
  }
}

void loop()
{
  dynamic_indi();                                     // Динамическая индикация всегда должна быть активна
}
