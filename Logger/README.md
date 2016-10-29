<h1 align="center">Библиотека логирования</h1>

Библиотека потокобезопасная. По умолчанию файл логирования имеет формат `log_HHMMSS_ddmmYYYY.log`.
</br>Функции:
+ `int set_file_name(const std::string name)` - установить имя файла
+ `void set_max_file_size(uint64_t size)` - задать максимальный размер файла
+ `int write(const Types&... param)` - записать в файл, функция имеет неограниченное число параметров
+ `operator<<(const T &arg)` - перегруженный оператор
