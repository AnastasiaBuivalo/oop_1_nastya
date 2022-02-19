using namespace std;

// Решения задачи а)
void task_01();       

// Решение задачи б)
void task_02();

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  task_01();
  //task_02();

  return 0;
}

// a. Дан текстовый файл. Преобразовать его, удалив из каждой строки слова, встречающиеся более двух раз.
void task_01()
{
  try
  {
    cout << "Введите названия файла, откуда будут считаны символы: ";
    char finName[256];
    cin >> finName;
    FILE* fin;
    fopen_s(&fin, finName, "r+b");


    int count[100] = {0};
    char arr_words[100][100];

    char str[256];
    string strUniqueCharFile;
    char readChar;
    long file_pos;
    fseek(fin, 0, SEEK_END);
    long file_end = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    int i = 0;
    long file_pos_write = ftell(fin);
    long file_pos_read = ftell(fin);
    while(ftell(fin) != file_end && fread(&readChar, sizeof(char), 1, fin) != EOF){
      while (ftell(fin) != file_end && readChar != EOF && readChar != '\n') {
        fseek(fin, file_pos_read, SEEK_SET);
        int j = 0;
        while (ftell(fin) != file_end && fread(&readChar, sizeof(char), 1, fin) != EOF && readChar != '\n' && readChar != ' ') {
          str[j] = readChar;
          j++;
        }
        str[j] = '\0';
        file_pos_read = ftell(fin);
        int index_search = 0;
        while (index_search < 100 && strcmp(str, arr_words[index_search]) != 0)
          index_search++;
        if (index_search == 100 || count[index_search] == 1) {//если слово встречалось до этого 1 или 0 раз
          fseek(fin, file_pos_write, SEEK_SET);//передвигаем указатель на позицию для записи
          fwrite(&str, sizeof(char*), 1, fin);//запись слова в файл
          file_pos_write = ftell(fin);//изменение позиции для записи
          if (index_search == 100) {
            strcpy_s(arr_words[i], str);
            count[i] = 1;
            i++;
          }
          else
            count[index_search]++;
        }
        fseek(fin, file_pos_read, SEEK_SET);
        fread(&readChar, sizeof(char), 1, fin);
      }
    }
    _chsize(_fileno(fin), file_pos_write);
    fclose(fin);
    cout << "Всё прошло успешно!" << endl;
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(-1);
  }
}

// Функция 2-ого задания для создания и ввода значений в бинарный файл
void CreateBinFile();

// Функция 2-ого задания для обработки бинарного файла
void ProcessBinFile();

// Функция 2-ого задания для вывода значений бинарного 
void WriteBinFIle();

void task_02()
{
  while (true)
  {
    cout << "Выберите команду:" << endl;
    cout << "1 - создать бинарный файл;" << endl;
    cout << "2 - обработать бинарный файл;" << endl;
    cout << "3 - вывести элементы бинарного файла;" << endl;
    cout << "4 - выход из программы;" << endl;
    int select;
    cin >> select;

    cout << endl << "#####################################################" << endl;
    switch (select)
    {
    case 1:
      CreateBinFile();
      break;
    case 2:
      ProcessBinFile();
      break;
    case 3:
      WriteBinFIle();
      break;
    case 4:
      cout << "Выход из программы..." << endl;
      return;
    default:
      cout << "Не существует данной команды!" << endl;
      break;
    }

    cout << "#####################################################" << endl << endl;
  }
}

// Функция для создания файла
void CreateBinFile()
{
  try
  {
    cout << "Введите названия файла, куда будут введены числа: ";
    string foutName;
    cin >> foutName;
    ofstream fout(foutName, ios::binary | ios::out);
    if (!fout.is_open())
      throw "Файл для ввода чисел не открыт!";

    cout << "Введите число n: ";
    int n;
    cin >> n;

cout << "Введите значения для бинарного файла:" << endl;
    cout << "Введите количество 2n положительных + 2n отрицательных последовательностей" << endl;
    int k;
    cin >> k;
    for (size_t i = 0; i < k; i++)
    {
      cout << "Введите 2n положительных чисел" << endl;
      for (int i = 0; i < 2 * n; i++)
      {
        int value;
        cin >> value;
        fout.write((char*)&value, sizeof(value));
      }
      cout << "Введите 2n отрицательных чисел" << endl;
      for (int i = 0; i < 2 * n; i++)
      {
        int value;
        cin >> value;
        fout.write((char*)&value, sizeof(value));
      }
    }
    
    fout.close();

    cout << "Всё прошло успешно!" << endl;
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(-1);
  }
}

// Функция для вывода файла
void WriteBinFIle()
{
  try
  {
    cout << "Введите названия файла, куда будут введены числа: ";
    string finName;
    cin >> finName;

    ifstream fin(finName, ios::binary | ios::out);
    if (!fin.is_open())
      throw "Файл для ввода чисел не открыт!";

    int value;
    fin.read((char*)&value, sizeof(value));
    while (!fin.eof())
    {
      cout << value << ' ';
      fin.read((char*)&value, sizeof(value));
    }
    cout << endl;

    fin.close();

    cout << "Всё прошло успешно!" << endl;
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(-1);
  }
}

// б. Дан файл из ненулевых целых чисел и целое n. Числа в файле идут в следующем порядке: 2n положительных, 2n отрицательных.
// Преобразовать файл так, чтобы числа в файле шли в cледующем порядке: n положительных, n отрицательных и так далее
void ProcessBinFile()
{
  try
  {
    cout << "Введите названия файла, откуда будут считаны числа: ";
    string fName;
    cin >> fName;
    fstream f(fName, ios::binary | ios::in | ios::out);
    if (!f.is_open())
      throw "Файл для считывания чисел не открыт!";

    cout << "Введите число n: ";
    int n;
    cin >> n;

    streampos pos = n * sizeof(int);
    streampos t_pos = (n - 1) * sizeof(int);
    streampos pos_cur = pos * 2;

    f.seekg(0, ios::end);
    streampos pos_end = f.tellg();

    f.seekg(pos_cur, ios::beg);
    pos_cur = pos * 6;
    int k = 0;
    while (f.tellg() < pos_end)
    {
      int x;
      int y;
      for (int i = 0; i < n; i++) { //обмен символов(на расстоянии n)
        f.seekp(-pos, ios::cur);
        streampos pos_x = f.tellp();
        f.read((char*)&x, sizeof(x));
        f.seekp(t_pos, ios::cur);
        streampos pos_y = f.tellp();
        f.read((char*)&y, sizeof(y));
        f.seekg(pos_x, ios::beg);
        f.write((char*)&y, sizeof(y));
        f.seekg(pos_y, ios::beg);
        f.write((char*)&x, sizeof(x));
        
      }
      k++;
      f.seekg(0, ios::beg);
      f.seekp(0, ios::beg);
      streampos pos_k = pos_cur * k;
      f.seekg(pos_k, ios::beg);
    }

    f.close();

    cout << "Всё прошло успешно!" << endl;
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(-1);
  }
}
