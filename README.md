# transcriby

<p align="center">
    <img src="/promo/promo.gif">
</p>

Приложение для расшифровки (генерации субтитров) аудио-файлов. На базовом уровне умеет: работать с файловой системой, воспроизводить аудио-файлы и расшифровывать их. Последнее реализовано через взаимодействие с сервером, на котором запушен transcriby-server.

Написано все на C++ с использованием библиотек [SFML](https://github.com/SFML/SFML), [ImGui](https://github.com/ocornut/imgui), [ImGui-SFML](https://github.com/SFML/imgui-sfml), [cpr](https://github.com/libcpr/cpr), [irrKlang](https://www.ambiera.com/irrklang/) и [whisper](https://github.com/openai/whisper), для работы с аудио-файлами используется утилита [ffmpeg](https://ffmpeg.org/).

### Сборка и запуск

Рекомендую использовать новейшие версии Visual Studio: не знаю как все будет работать в других системах(((

Для начала клонируем репозиторий 
```
git clone https://github.com/Shpana/text-editor
```
для генерации vs-решения или make-файла запускаем соответсвующую строчку
```
vendor/premake5/premake5.exe {gmake, vs2019, vs2022...}
```

Для корректной работы расшифровки нужно (пока) запустить python-проект transcriby-server: расшифрока производится локально. В дальнейшем планируется дать пользователю изменять сервер для генерации расшифровки.
