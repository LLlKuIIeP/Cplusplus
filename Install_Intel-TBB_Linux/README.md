### Установка библиотеки **Intel TBB** на Linux для многопоточного программирования.

Страница [Wikipedia](https://ru.wikipedia.org/wiki/Intel_Threading_Building_Blocks) библиотеки. В конце статьи можно перейти на официальный сайт библиотеки, а также найти презентации и примеры кода.
 
[Страница загрузки](https://www.threadingbuildingblocks.org/download)

####Разделим на этапы
<i class="icon-file"></i> Подготовка

 - Запустить терминал Linux
 - Перейти в директорию, где будет проект, к примеру:

`cd /home/user`

 - Создать папку куда скачаем библиотеку

`mkdir tbb`

<i class="icon-folder-open"></i>Скачивание

 - В браузере перейти на страницу загрузки библиотеки
 - Правой кнопкой мыши по иконке *Linux** *-> Копировать адрес ссылки*
 - В терминале *wget -> правая кнопка мыши -> Вставить*, должно получиться:

`wget https://www.threadingbuildingblocks.org/sites/default/files/software_releases/linux/tbb44_20151115oss_lin.tgz`

 - Распаковываем архив:

`tar zxf tbb44_20151115oss_lin.tgz`

 - В директории с архивом появится папка **tbb44_20151115oss**

<i class="icon-hdd"></i>Установка

 - Нужен скрипт установки (*tbbvars.sh*), он находится в папке *bin*,
   переходим туда

`cd tbb44_20151115oss/bin/`

 - Открыть файл и найти строчку  **export TBBROOT=SUBSTITUTE_INSTALL_DIR_HERE** её нужно изменить, т.е. в параметре **TBBROOT** указать полный путь до распакованной папки, т.е. **export TBBROOT=/home/user/tbb/tbb44_20151115oss**
и сохранить изменения

 - Если просто выполнить скрипт **. ./tbbvars.sh**, то будет ошибка 
**ERROR: Unknown switch ''. Accepted values: ia32, intel64, android**,
т.к. нужен параметр архитектуры

`. ./tbbvars.sh intel64`
