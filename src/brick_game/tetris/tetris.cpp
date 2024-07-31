#include "tetris.h"

/**
 * @brief Поворот фигуры
 *
 * Сначало во временном массиве создается перевернутая фигура
 *
 * Затем проверяется коллизия рядом с повернутой фигурой
 *
 * если коллизия есть, то flag = 1 и фигура не поворачивается
 *
 * если коллизии нет то flag = 0 и фигура переворачивается после отображается на
 * поле
 *
 * @param argc 2
 * @param argv figure, info
 */
int RotateFigure(Figure *figure, GameInfo info) {
  int flag = 0;
  int temp[4][4] = {0};
  if (figure->matrix[0][0] == 1 && figure->matrix[0][1] == 1 &&
      figure->matrix[1][0] == 1 && figure->matrix[1][1] == 1)
    flag = 1;
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      temp[i][j] = figure->matrix[j][i];
    }
  }
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      if (temp[i][j] == 1 && info.array[info.y + i][info.x + j] == 1) flag = 1;
    }
  }
  if (!flag) {
    for (int i = 0; i < figure->size; i++) {
      for (int j = 0; j < figure->size; j++) {
        figure->matrix[i][j] = temp[i][figure->size - 1 - j];
      }
    }
  }
  return flag;
}
/**
 * @brief Инициализация поля
 *
 * сначала проверяем выделилась ли память под массив
 *
 * после заполняем края поля единицами чтобы создать стенки
 *
 * @param argc 1
 * @param argv info
 *
 * @return 0 если не выделилась память, 1 если все ОК
 */
int InitField(GameInfo info) {
  if (info.array == NULL) {
    return 0;
  }
  for (int i = 0; i < HEIGHT; i++) {
    info.array[i][WIDTH - 1] = 1;
  }
  for (int i = 0; i < HEIGHT; i++) {
    info.array[i][0] = 1;
  }
  for (int j = 0; j < WIDTH; j++) {
    info.array[HEIGHT - 1][j] = 1;
  }
  return 1;
}
/**
 * @brief Проверка коллизии при перемещении фигур
 *
 * проверяем при различных значениях state коллизию фигуры с полем
 *
 * state нужен для 3 ситуаций передвижение влево, вправо и вниз
 *
 * проверяется всегда следующая координата поля от каждого пикселя фигуры
 *
 * @param argc 3
 * @param argv info figure state
 *
 * @return 1 если есть коллизия, 0 если все ОК
 */
int ControllCollision(GameInfo info, Figure figure, int state) {
  int flag = 0;
  for (int i = 0; i < figure.size; i++) {
    for (int j = 0; j < figure.size; j++) {
      if (figure.matrix[i][j] == 1) {
        if ((info.array[info.y + i][info.x + j + 1] == 1 && !state) ||
            (info.array[info.y + i][info.x + j - 1] == 1 && state) ||
            (info.array[info.y + i + 1][info.x + j] == 1 && state == 2))
          flag = 1;
      }
    }
  }
  return flag;
}

/**
 * @brief Сохранение состояния поля
 *
 * Вызываем при каком либо изменении поля тем самым записываем единички
 * в ячейки массива если произошло столкновение фигуры с фигурой или с полем
 *
 * @param argc 2
 * @param argv info figure
 *
 */

void SaveField(GameInfo *info, Figure figure) {
  for (int i = 0; i < figure.size; i++) {
    for (int j = 0; j < figure.size; j++) {
      if (figure.matrix[i][j] == 1) info->array[info->y + i][info->x + j] = 1;
    }
  }
}
/**
 * @brief Проверка коллизии фигуры с полем или фигурой по оси y
 *
 * проверяем если под писелем фигуры есть преграда то flag = 1
 *
 * @param argc 2
 * @param argv info figure
 *
 * @return 1 если есть коллизия, 0 если все ОК
 */

int FigureCollision(GameInfo info, Figure figure) {
  int flag = 0;
  for (int i = 0; i < figure.size; i++) {
    for (int j = 0; j < figure.size; j++) {
      if (figure.matrix[i][j] == 1) {
        if (info.array[info.y + i + 1][info.x + j] == 1) flag = 1;
      }
    }
  }
  return flag;
}
/**
 * @brief Очистка заполненной строки
 *
 * сначало прверяем поле и ищем заполненные строки
 *
 * если нашли то берем строку которая выше на единицу заполненной строки
 * и ставим ее на место заполненой после чего очищаем верхнюю строку
 *
 * так же подсчитываем кол-во очищенных строк для получения очков
 *
 * @param argc 1
 * @param argv info
 *
 * @return кол-во заполненныx строк
 */
int ClearFilledRows(GameInfo *info) {
  int clearedLines = 0;
  for (int i = HEIGHT - 2; i > 0; i--) {
    int row_filled = 1;
    for (int j = 1; j < WIDTH - 1; j++) {
      if (info->array[i][j] == 0) {
        row_filled = 0;
        break;
      }
    }
    if (row_filled) {
      for (int k = i; k > 0; k--) {
        for (int j = 1; j < WIDTH - 1; j++) {
          info->array[k][j] = info->array[k - 1][j];
        }
      }
      for (int j = 1; j < WIDTH - 1; j++) {
        info->array[0][j] = 0;
      }
      i++;
      clearedLines++;
    }
  }
  return clearedLines;
}
/**
 * @brief Получение рандомной фигуры из массива с 7 фигурами
 *
 *
 * @param argc 1
 * @param argv figures
 *
 * @return номер фигуры
 */
Figure getRandomFigure(Figure *figures) {
  int random_index = rand() % 7;
  return figures[random_index];
}
/**
 * @brief Считывние лучшего счета из файла
 *
 * проверяем существует ли файл
 *
 * после открываем его и считываем в переменную лучший счет
 *
 * после возвращем его черeз return
 *
 * @return лучший счет
 */
int readHighScore() {
  int highScore = 0;
  FILE *file = fopen("highscore.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &highScore);
    fclose(file);
  }
  return highScore;
}
/**
 * @brief Запись лучшего счета
 *
 * проверяем существует ли файл
 *
 * если нет то создаем о открываем его
 *
 * после записываем лучший счет в файл
 * @param argc 1
 * @param argv info
 */
void writeHighScore(GameInfo *info) {
  FILE *file = fopen("highscore.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", info->score);
    fclose(file);
  }
}
/**
 * @brief Пользовательсий ввод
 *
 * Проверяем какая была введена клавиша и применяем соответсвующую функцию
 *
 * @param argc 2
 * @param argv info figure
 */
void UserInput(GameInfo *info, Figure *figure) {
  switch (info->inputChar) {
    case Up:
      RotateFigure(figure, *info);
      break;
    case Right:
      if (!ControllCollision(*info, *figure, 0)) info->x++;
      break;
    case Left:
      if (!ControllCollision(*info, *figure, 1)) info->x--;
      break;
    case Down:
      info->hold = 1;
      break;
    case StartKey:
      info->startGame = Start;
      break;
    case PauseKey:
      info->startGame = Pause;
      break;
  }
}
/**
 * @brief Инициализация всех переменных в структуре и не только
 *
 * @param argc 4
 * @param argv info figure nextFigure figures
 */
void InitGameInfo(GameInfo *info, Figure *figure, Figure *nextFigure,
                  Figure *figures) {
  info->x = STARTWIDTH;
  info->y = STARTHEIGHT;
  info->score = 0;
  info->previousScore = 0;
  info->speed = 1000;
  info->inputChar = 0;
  info->highScore = readHighScore();
  info->rowFilled = 0;
  info->hold = 0;
  info->gameOver = 0;
  info->level = 1;
  info->pause = Pause;
  info->startGame = Start;
  *figure = getRandomFigure(figures);
  *nextFigure = getRandomFigure(figures);
}
/**
 * @brief Получение счета в зависимости от кол-во зачищенных строк
 *
 * Здесь происходит запись лучшего счета а так же начисления очков
 *
 * @param argc 1
 * @param argv info
 */
void GetScore(GameInfo *info) {
  info->highScore = readHighScore();
  if (info->score > info->highScore) writeHighScore(info);
  if (info->rowFilled >= 1) {
    switch (info->rowFilled) {
      case 2:
        info->score += 200;
        break;
      case 3:
        info->score += 600;
        break;
      case 4:
        info->score += 1400;
        break;
    }
    info->score += 100;
    info->rowFilled = 0;
  }
}
/**
 * @brief Инициализация времени для таймера
 *
 * получаем текущее время в секундах
 *
 * @param argc 1
 * @param argv time
 */
void InitTime(TimeInfo *time) {
  time->seconds = 0;
  gettimeofday(&time->start_time, NULL);
}
/**
 * @brief Таймер
 *
 * рассчитываем кол-во секунд прошедшее с прошлого перемещения фигуры по оси y
 * на 1 пиксель
 *
 * также в зависимости от command мы можем как рассчитывать время так и
 * присваивать его к нулю
 *
 * @param argc 2
 * @param argv time command
 */
void Timer(TimeInfo *time, int command) {
  if (!command) {
    time->start_time = time->current_time;
    time->seconds = 0;
  } else {
    gettimeofday(&time->current_time, NULL);
    long int microseconds = 0;
    microseconds =
        (time->current_time.tv_sec - time->start_time.tv_sec) * 1000000 +
        (time->current_time.tv_usec - time->start_time.tv_usec);
    time->seconds = microseconds / 1000000.0;
  }
}
/**
 * @brief Изменение уровня и скорости падения фигур
 *
 * Проверяем не достигли ли мы максимального уровня и скорости
 *
 * если нет то считаем наше кол-во очков и устанавливаем соот. уровень
 *
 * затем пропорционально меняем скорость падения фигур
 *
 * @param argc 1
 * @param argv info
 */
void ChangeLevel(GameInfo *info) {
  if (info->hold)
    info->speed = 101;
  else
    info->speed = 1000 - ((info->level - 1) * 100);
  if (info->speed <= 100 || info->level >= 10) {
    info->speed = 100;
    info->level = 10;
  } else {
    if (info->score - info->previousScore >= 600) {
      double level = info->score;
      level = floor(level / 600);
      info->level = level + 1;
      info->speed -= 100;
      info->previousScore = level * 600;
    }
  }
}
/**
 * @brief Обновление текущего состояния
 *
 * Здесь мы вызываем все функции необходимые для изменения игры
 *
 * при соприкосновении фигуры с чем то координаты сбрасываются после
 * записывается следующая фигура для ее отображения в интерфейсе справо
 *
 * а так же считается кол-во зачищенных строк
 *
 * @param argc 4
 * @param argv info figure nextFigure figures
 */
void UpdateCurrentState(GameInfo *info, Figure *figure, Figure *nextFigure,
                        Figure figures[]) {
  SaveField(info, *figure);
  info->rowFilled = ClearFilledRows(info);
  *figure = *nextFigure;
  info->x = STARTWIDTH;
  info->y = STARTHEIGHT;
  *nextFigure = getRandomFigure(figures);
}
/**
 * @brief условие проигрыша
 *
 * Если фигура коснулась самого верха то автоматически закрываем игру
 *
 * @param argc 1
 * @param argv info
 */
void GameOver(GameInfo *info) {
  for (int i = 1; i < WIDTH - 1; i++) {
    if (info->array[0][i]) {
      info->gameOver = 1;
      break;
    }
  }
}
/**
 * @brief пауза игры
 *
 * если нажата клавиша p то игра приостоновлена
 *
 * @param argc 1
 * @param argv info
 */
int PauseGame(GameInfo info) {
  int result = Pause;
  if (info.inputChar == 'P' || info.inputChar == 'p') {
    result = Start;
  }
  return result;
}
/**
 * @brief старт игры
 *
 * если нажата клавиша s значит игра начата
 *
 * @param argc 1
 * @param argv info
 */
int StartGame(GameInfo info) {
  int result = Start;
  if (info.inputChar == 'S' || info.inputChar == 's') {
    result = Pause;
  }
  return result;
}

/**
 * @brief Выделение памяти
 *
 * Сначало проверяем на NULL
 *
 * После выделяем память под двемерный массив
 *
 * @param argc 1
 * @param argv info
 */
int AllocateMemory(GameInfo *info) {
  int result = 1;
  info->array = (int **)calloc(HEIGHT, sizeof(int *));
  if (info->array == NULL) {
    return 0;
  }
  for (int i = 0; i < HEIGHT; i++) {
    info->array[i] = (int *)calloc(WIDTH, sizeof(int));
    if (info->array[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(info->array[j]);
      }
      free(info->array);
      info->array = NULL;
      result = 0;
      break;
    }
  }
  return result;
}
/**
 * @brief Очистка памяти
 *
 * Сначало проверяем на NULL
 *
 * После очищаем память
 *
 * @param argc 1
 * @param argv info
 */
void FreeMemory(GameInfo *info) {
  if (info->array == NULL) {
    return;
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(info->array[i]);
  }
  free(info->array);
  info->array = NULL;
}
